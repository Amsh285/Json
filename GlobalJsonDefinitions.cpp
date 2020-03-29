#include "GlobalJsonDefinitions.h"

namespace GlobalJsonDefinitions
{
    const char openJsonObjectTag = '{', closeJsonObjectTag = '}';
    const char openJsonArrayTag = '[', closeJsonArrayTag = ']';
    const char stringLiteralTag = '"';
    const char whitespace = ' ';

    const char elementDelimiter = ',';
    const char keyValuePairDelimiter = ':';

    const std::string JsonElementTypes[] = {
        "JsonElementType_Object",
        "JsonElementType_Array",
        "JsonElementType_Value",
        "JsonElementType_SingleValue",
        "JsonElementType_KeyValuePair",
        "JsonElementType_Unknown"
    };
}
