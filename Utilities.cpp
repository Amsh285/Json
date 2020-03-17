#include "Utilities.h"

namespace Create
{
    ObjectBuilderContainer A;
    ObjectBuilderContainer An;

    //JsonValueBuilder
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

    JsonValueBuilder JsonValueBuilder::WithRawValue(std::string value)
    {
        this->value = value;
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

    //JsonValueListBuilder
    JsonValueListBuider JsonValueListBuider::WithValue(std::string name, std::string value)
    {
        this->values.push_back(CreateJsonValueTuple(name, "\"" + value + "\""));
        return *this;
    }

    JsonValueListBuider JsonValueListBuider::WithValue(std::string name, int value)
    {
        this->values.push_back(CreateJsonValueTuple(name, std::to_string(value)));
        return *this;
    }

    JsonValueListBuider JsonValueListBuider::WithValue(std::string name, double value)
    {
        this->values.push_back(CreateJsonValueTuple(name, std::to_string(value)));
        return *this;
    }

    std::vector<std::tuple<std::string, std::string>> JsonValueListBuider::Build()
    {
        return values;
    }

    std::tuple<std::string, std::string> JsonValueListBuider::CreateJsonValueTuple(std::string name, std::string value)
    {
        return std::tuple<std::string, std::string>(name, value);
    }

    //JsonObjectBuilder
    JsonObjectBuilder::JsonObjectBuilder()
    {
        this->name = "";
        this->parent = nullptr;

        valueFactory = [](JsonValueListBuider builder){ return builder.Build(); };
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

        auto jsonValues = this->valueFactory(JsonValueListBuider());

        for(auto const& jsonValue : jsonValues)
        {
            JsonValue* value = Create::A.JsonValue()
                .WithName(std::get<0>(jsonValue))
                .WithRawValue(std::get<1>(jsonValue))
                .WithParent(result)
                .Build();
        }

        return result;
    }
}
