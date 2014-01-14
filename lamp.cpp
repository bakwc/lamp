#include <iomanip>
#include <sstream>
#include <iostream>

#include "lamp.h"

using namespace std;

Lamp::Lamp()
    : enabled(false)
    , currentColor("\0\0\0")
{
}

bool Lamp::applyCommand(CommandType type, const string &data)
{
    switch (type) {
    case CT_On:
        enableLamp();
        return false;
    case CT_Off:
        disableLamp();
        return true;
    case CT_Color:
        changeColor(data);
        return false;
    default:
        throw LampControlException();
        break;
    }
}

void Lamp::outHex(stringstream &stream, uint8_t symbol)
{
    stream << hex << setfill('0') << setw(2) << +symbol;
}

string Lamp::colorToString(const string &color)
{
    stringstream colorStream;
    outHex(colorStream, color[0]);
    outHex(colorStream, color[1]);
    outHex(colorStream, color[2]);
    return colorStream.str();
}

void Lamp::enableLamp()
{
    if (!enabled) {
        enabled = true;
        cout << "Lamp turned on!\n";
    }
}

void Lamp::disableLamp() {
    if (enabled) {
        enabled = false;
        cout << "Lamp turned off!\n";
    }
}

void Lamp::changeColor(const string &data)
{
    if (data.size() != 3)
        throw ColorException();

    if (currentColor != data) {
        cout << "Lamp switched color from #" << colorToString(currentColor) << " to #" << colorToString(data) << "\n";
        currentColor = data;
    }
}

LampControlException::LampControlException()
    : BaseException("bad lamp control command")
{
}

ColorException::ColorException()
    : BaseException("bad color")
{
}
