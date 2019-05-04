#pragma once

#include <iostream>
#include <exception>
#include <string>

class stringException : public std::exception
{
public:
    stringException();
    stringException(std::string);
    virtual const char* what() const throw();
private:
    std::string whatStr;
};


