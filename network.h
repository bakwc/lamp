#pragma once

#include <functional>

#include "exception.h"

struct Address
{
    Address();
    Address(const std::string& address);
    bool isInitialized() const;
public:
    std::string host;
    unsigned short port;
};

enum CommandType
{
    CT_On = 0x12,
    CT_Off = 0x13,
    CT_Color = 0x20
};

typedef std::function<bool(CommandType, const std::string &)> CommandCallback;

class Network {
public:
    void run(const Address &remoteAddress, CommandCallback commandCallback);
private:
    void processCommands(std::string &buffer, CommandCallback callback, bool &finished);
};


struct BadAddressException: public BaseException
{
    BadAddressException();
};

struct NetworkException: public BaseException
{
    NetworkException(const std::string &error);
};

struct SocketCreateException: public NetworkException
{
    SocketCreateException();
};

struct ConnectException: public NetworkException
{
    ConnectException();
};

struct ConnectDropException: public NetworkException
{
    ConnectDropException();
};

