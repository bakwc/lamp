#include <iostream>
#include <string>
#include <functional>

#include "exception.h"
#include "network.h"
#include "lamp.h"

using namespace std;
using namespace std::placeholders;

Address getAddress()
{
    string addressStr;
    cout << "Input address: ";
    cin >> addressStr;
    return Address(addressStr);
}

int main()
{
    try {
        Network network;
        Lamp lamp;
        Address address = getAddress();
        network.run(address, bind(&Lamp::applyCommand, &lamp, _1, _2));
    } catch (const BaseException &e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
