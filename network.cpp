#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "network.h"

using namespace std;

Address::Address()
{}

Address::Address(const string& address)
{
    size_t delim = address.find(':');
    if (delim == string::npos) {
        throw BadAddressException();
    }
    host = address.substr(0, delim);
    try {
        port = stoi(address.substr(delim + 1));
    } catch (...) {
        throw BadAddressException();
    }
}

bool Address::isInitialized() const
{
    return !host.empty() && port;
}

void Network::run(const Address &remoteAddress, CommandCallback commandCallback)
{
    if (!remoteAddress.isInitialized())
        throw BadAddressException();

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        throw SocketCreateException();

    struct hostent* host;
    host = gethostbyname(remoteAddress.host.c_str());

    addr.sin_addr = *(struct in_addr *) host->h_addr_list[0];
    addr.sin_family = AF_INET;
    addr.sin_port = htons(remoteAddress.port);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        throw ConnectException();

    string totalBuffer;
    bool finished = false;
    while (!finished) {
        string currentBuf;
        currentBuf.resize(512);
        int received = recv(sock, &currentBuf[0], currentBuf.size(), 0);
        if (received <= 0) {
            throw ConnectDropException();
        }
        totalBuffer += currentBuf.substr(0, received);

        processCommands(totalBuffer, commandCallback, finished);
    }
    shutdown(sock, SHUT_RDWR);
}

void Network::processCommands(string &buffer, CommandCallback callback, bool &finished)
{
    while (buffer.size() >= 3) {
        CommandType type = static_cast<CommandType>(buffer[0]);
        unsigned short size = ntohs(*(uint16_t*)(&buffer[1]));
        if (buffer.size() < size + 3u)
            return;

        bool result = callback(type, buffer.substr(3, size));
        buffer = buffer.substr(3 + size);
        if (result) {
            finished = true;
            return;
        }
    }
}

BadAddressException::BadAddressException()
    : BaseException("bad address")
{
}

NetworkException::NetworkException(const string &error)
    : BaseException(error)
{
}

SocketCreateException::SocketCreateException()
    : NetworkException("failed to create socket")
{
}

ConnectException::ConnectException()
    : NetworkException("failed to connect to server")
{
}

ConnectDropException::ConnectDropException()
    : NetworkException("connection terminated")
{
}
