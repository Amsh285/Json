#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdexcept>
#include <functional>
#include <vector>
#include <tuple>

#include "JsonNode.h"
#include "JsonObject.h"
#include "JsonValue.h"

namespace Create
{
    template<class T>
    class ObjectBuilder
    {
        public:
            virtual T Build() = 0;
    };

    class JsonValueBuilder : ObjectBuilder<JsonValue*>
    {
        public:
            JsonValueBuilder();

            JsonValueBuilder WithName(std::string name);
            JsonValueBuilder WithValue(std::string value);
            JsonValueBuilder WithValue(int value);
            JsonValueBuilder WithValue(double value);
            JsonValueBuilder WithRawValue(std::string value);
            JsonValueBuilder WithParent(JsonObject* parent);
            virtual JsonValue* Build();

        private:
            JsonObject* parent;
            std::string name;
            std::string value;
    };

    class JsonValueListBuider : ObjectBuilder<std::vector<std::tuple<std::string, std::string>>>
    {
        public:
            JsonValueListBuider WithValue(std::string name, std::string value);
            JsonValueListBuider WithValue(std::string name, int value);
            JsonValueListBuider WithValue(std::string name, double value);
            std::vector<std::tuple<std::string, std::string>> Build();

        private:
            std::tuple<std::string, std::string> CreateJsonValueTuple(std::string name, std::string value);
            std::vector<std::tuple<std::string, std::string>> values;
    };

    class JsonObjectBuilder : ObjectBuilder<JsonObject*>
    {
        public:
            JsonObjectBuilder();
            JsonObjectBuilder WithName(std::string name);
            JsonObjectBuilder WithJsonObjectType(JsonObjectType objectType);
            JsonObjectBuilder WithParent(JsonObject* parent);

            JsonObjectBuilder WithValues(std::function<std::vector<std::tuple<std::string, std::string>> (JsonValueListBuider)> valueFactory)
            {
                this->valueFactory = valueFactory;
                return *this;
            }

            virtual JsonObject* Build();

        private:
            JsonObjectType objectType;
            JsonObject *parent;
            std::string name;

            std::function<std::vector<std::tuple<std::string, std::string>> (JsonValueListBuider)> valueFactory;
    };

    class ObjectBuilderContainer
    {
        public:
            JsonValueBuilder JsonValue()
            {
                JsonValueBuilder valueBuilder;
                return valueBuilder;
            }

            JsonObjectBuilder JsonObject()
            {
                JsonObjectBuilder objectBuilder;
                return objectBuilder;
            }

        private:

    };

    extern ObjectBuilderContainer A;
    extern ObjectBuilderContainer An;
}

#endif // UTILITIES_H
