#include "JsonValue.h"

JsonValue::JsonValue(std::string name, std::string value, JsonObject* parent) : JsonNode(name)
{
    this->value = value;

    this->parent = parent;

    if(parent != nullptr)
    {
        parent->AddChild(this);
        depth = parent->GetDepth() + 1;
    }
}

JsonValue::~JsonValue()
{
    //dtor
}

std::string JsonValue::ToJsonString()
{
    std::string result = "";

    if(name != "")
        result += "\"" + name + "\"" + " : ";

    result += value;

    return result;
}

