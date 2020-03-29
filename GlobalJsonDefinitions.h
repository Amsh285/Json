#ifndef GLOBALJSONDEFINITIONS_H
#define GLOBALJSONDEFINITIONS_H

#include <string>

namespace GlobalJsonDefinitions
{
    extern const char openJsonObjectTag;
    extern const char closeJsonObjectTag;
    extern const char openJsonArrayTag;
    extern const char closeJsonArrayTag;
    extern const char stringLiteralTag;
    extern const char whitespace;

    extern const char elementDelimiter;
    extern const char keyValuePairDelimiter;

    extern const std::string JsonElementTypes[];

    enum JsonElementType
    {
        JsonElementType_Object,
        JsonElementType_Array,
        JsonElementType_Value,
        JsonElementType_SingleValue,
        JsonElementType_KeyValuePair,
        JsonElementType_Unknown
    };
}

#endif // GLOBALJSONDEFINITIONS_H
