#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <algorithm>
#include <assert.h>
#include <stdexcept>
#include <string>
#include <tuple>
#include <sstream>

#include "Utilities.h"
#include "JsonNode.h"
#include "JsonObject.h"
#include "JsonObjectIdentifier.h"
#include "JsonObjectSegmenter.h"
#include "JsonParserException.h"
#include "JsonValue.h"
#include "StringHelper.h"


using namespace GlobalJsonDefinitions;

class JsonParser
{
    public:
        JsonParser();
        virtual ~JsonParser();

        JsonNode* ParseJsonString(const std::string& value);
    protected:

    private:
        JsonObjectSegmenter objectSegmenter;
        JsonObjectIdentifier objectIdentifier;

        void ParseJsonKeyValuePair(const std::string& objectSegment, JsonObject* parent);
        JsonNode* ParseJsonObject(const std::string& objectSegment, std::string name, JsonObject* parent);
        JsonNode* ParseJsonArray(const std::string& objectSegment, std::string name, JsonObject* parent);
        JsonNode* ProcessSingleJsonValue(const std::string& value, const std::string& name, JsonObject* parent);

        std::string GetNormalizedName(const std::string name);
};

#endif // JSONPARSER_H
