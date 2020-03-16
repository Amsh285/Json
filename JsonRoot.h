#ifndef JSONROOT_H
#define JSONROOT_H

#include<stdexcept>

#include "JsonNode.h"

class JsonRoot
{
    public:
        JsonRoot(JsonNode *rootElement);
        virtual ~JsonRoot();

    protected:

    private:
        JsonNode *rootElement;
};

#endif // JSONROOT_H
