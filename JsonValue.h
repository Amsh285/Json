#ifndef JSONVALUE_H
#define JSONVALUE_H

#include<string>

#include "JsonNode.h"
#include "JsonObject.h"

//class JsonObject;

class JsonValue : public JsonNode
{
    public:
        JsonValue(std::string name, std::string value, JsonObject* parent);

        virtual std::string ToJsonString();
        virtual ~JsonValue();

    protected:

    private:
        std::string value;
        JsonObject* parent;
};

#endif // JSONVALUE_H
