#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <assert.h>
#include <stdexcept>
#include <string>
#include <tuple>
#include <sstream>

#include "Utilities.h"
#include "JsonNode.h"
#include "JsonObject.h"
#include "JsonValue.h"
#include "JsonObjectSegmenter.h"

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
};

#endif // JSONPARSER_H
