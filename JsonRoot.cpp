#include "JsonRoot.h"
JsonRoot::JsonRoot(JsonNode *rootElement)
{
    if(rootElement == nullptr)
        throw new std::invalid_argument("rootElement cannot be null.");

    this->rootElement = rootElement;
}


JsonRoot::~JsonRoot()
{
    delete this->rootElement;
}

