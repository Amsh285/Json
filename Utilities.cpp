#include "Utilities.h"

namespace Create
{
    ObjectBuilderContainer A;
    ObjectBuilderContainer An;

    JsonValueBuilder::JsonValueBuilder()
    {
        this->name = "";
        this->value = "";
        this->parent = nullptr;
    }

    JsonValueBuilder JsonValueBuilder::WithName(std::string name)
    {
        this->name = name;
        return *this;
    }

    JsonValueBuilder JsonValueBuilder::WithValue(std::string value)
    {
        this->value = "\"" + value + "\"";
        return *this;
    }

    JsonValueBuilder JsonValueBuilder::WithValue(int value)
    {
        this->value = std::to_string(value);
        return *this;
    }

    JsonValueBuilder JsonValueBuilder::WithValue(double value)
    {
        this->value = std::to_string(value);
        return *this;
    }

    JsonValueBuilder JsonValueBuilder::WithParent(JsonObject* parent)
    {
        this->parent = parent;
        return *this;
    }

    JsonValue* JsonValueBuilder::Build()
    {
        JsonValue* result = new JsonValue(name, value, parent);
        return result;
    }

    //JsonObjectBuilder
    JsonObjectBuilder::JsonObjectBuilder()
    {
        this->name = "";
        this->parent = nullptr;
    }

    JsonObjectBuilder JsonObjectBuilder::WithName(std::string name)
    {
        this->name = name;
        return *this;
    }

    JsonObjectBuilder JsonObjectBuilder::WithJsonObjectType(JsonObjectType objectType)
    {
        this->objectType = objectType;
        return *this;
    }

    JsonObjectBuilder JsonObjectBuilder::WithParent(JsonObject* parent)
    {
        this->parent = parent;
        return *this;
    }

    JsonObject* JsonObjectBuilder::Build()
    {
        JsonObject* result = new JsonObject(name, parent, objectType);
        return result;
    }
}
