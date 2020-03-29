#ifndef JSONVALUE_H
#define JSONVALUE_H

#include<string>

#include "JsonNode.h"
#include "JsonObject.h"
#include "StringHelper.h"

//class JsonObject;

class JsonValue : public JsonNode
{
    public:
        JsonValue(std::string name, std::string value, JsonObject* parent);

        std::string GetValue() const { return value; };
        std::string GetStringValue() const;

        virtual std::string ToJsonString();
        virtual ~JsonValue();

    protected:

    private:
        std::string value;
        JsonObject* parent;
};

#endif // JSONVALUE_H
