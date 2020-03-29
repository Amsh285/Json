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

std::string JsonValue::GetStringValue() const
{
    std::string trimmedName = stringhelper::TrimCopy(value);

    if(trimmedName[0] == '\"')
        trimmedName = trimmedName.substr(1, trimmedName.size() - 1);

    if(trimmedName[trimmedName.size() - 1] == '\"')
        trimmedName = trimmedName.substr(0, trimmedName.size() - 1);

    return trimmedName;
}

std::string JsonValue::ToJsonString()
{
    std::string result = "";

    if(name != "")
        result += "\"" + name + "\"" + " : ";

    result += value;

    return result;
}

