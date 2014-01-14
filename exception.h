#pragma once

#include <string>
#include <exception>

struct BaseException: public std::string, public std::exception
{
    BaseException(const std::string &error)
        : std::string(error)
    {
    }
    const char *what() const throw()
    {
        return this->data();
    }
};
