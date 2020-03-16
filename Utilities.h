#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdexcept>
#include <vector>

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
            JsonValueBuilder WithParent(JsonObject* parent);
            virtual JsonValue* Build();

        private:
            JsonObject* parent;
            std::string name;
            std::string value;
    };

    class JsonObjectBuilder : ObjectBuilder<JsonObject*>
    {
        public:
            JsonObjectBuilder();
            JsonObjectBuilder WithName(std::string name);
            JsonObjectBuilder WithJsonObjectType(JsonObjectType objectType);
            JsonObjectBuilder WithParent(JsonObject* parent);
            virtual JsonObject* Build();

        private:
            JsonObjectType objectType;
            JsonObject *parent;
            std::string name;
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
