#pragma once

#include "exception.h"
#include "network.h"

class Lamp {
public:
    Lamp();
    bool applyCommand(CommandType type, const std::string &data);
private:
    void enableLamp();
    void disableLamp();
    void changeColor(const std::string &data);

    void outHex(std::stringstream &stream, uint8_t symbol);
    std::string colorToString(const std::string &color);
private:
    bool enabled;
    std::string currentColor;
};

struct LampControlException: public BaseException
{
    LampControlException();
};

struct ColorException: public BaseException
{
    ColorException();
};
