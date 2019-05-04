#include "stringException.h"

stringException::stringException()
{
    whatStr = std::string("Unkwnown exception thrown");
}

stringException::stringException(std::string _whatStr)
{
    whatStr = _whatStr;
}

const char* stringException::what() const throw()
{
    return whatStr.c_str();
}
