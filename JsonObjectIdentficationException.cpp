#include "JsonObjectIdentficationException.h"

JsonObjectIdentficationException::JsonObjectIdentficationException(std::string errorMessage)
    : errorMessage(errorMessage)
{
    //ctor
}

JsonObjectIdentficationException::~JsonObjectIdentficationException()
{
    //dtor
}

const char* JsonObjectIdentficationException::what () const throw ()
{
	return errorMessage.c_str();
}
