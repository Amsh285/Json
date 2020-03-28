#include "JsonParserException.h"

JsonParserException::JsonParserException(std::string errorMessage)
    : errorMessage(errorMessage)
{
    //ctor
}

JsonParserException::~JsonParserException()
{
    //dtor
}

const char* JsonParserException::what() const throw()
{
    return errorMessage.c_str();
}
