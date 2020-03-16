#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <vector>
#include <stdexcept>

#include "JsonNode.h"

enum JsonObjectType{
    JsonObjectType_Object,
    JsonObjectType_Array
};

class JsonObject : public JsonNode
{
    public:
        JsonObject(std::string name, JsonObject* parent, JsonObjectType type);
        virtual std::string ToJsonString();
        virtual ~JsonObject();

        void AddChild(JsonNode *child);
    protected:

    private:
        JsonObjectType objectType;

        JsonObject* parent;
        std::vector<JsonNode*> children;
};

#endif // JSONOBJECT_H
