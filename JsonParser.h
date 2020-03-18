#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <assert.h>
#include <stdexcept>
#include <string>
#include <tuple>
#include <sstream>

#include "JsonNode.h"
#include "JsonObject.h"
#include "JsonValue.h"

class JsonParser
{
    public:
        JsonParser();
        virtual ~JsonParser();

        JsonNode* ParseJsonString(const std::string& value);
    protected:

    private:
};

#endif // JSONPARSER_H
