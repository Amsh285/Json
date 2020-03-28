#include "JsonObjectIdentifier.h"

IdentificationResult::IdentificationResult(std::string::size_type position, JsonElementType elementType)
    : position(position), elementType(elementType)
{
}

IdentificationResult::~IdentificationResult()
{
}

JsonObjectIdentifier::JsonObjectIdentifier()
{
    //ctor
}

JsonObjectIdentifier::~JsonObjectIdentifier()
{
    //dtor
}

IdentificationResult JsonObjectIdentifier::IdentifyElement(const std::string& value) const
{
    return IdentifyElement(0, value);
}

IdentificationResult JsonObjectIdentifier::IdentifyElement(std::string::size_type position, const std::string& value) const
{
    for(;position < value.size();++position)
    {
        if(value[position] == openJsonObjectTag)
            return IdentificationResult(position, JsonElementType_Object);
        else if(value[position] == openJsonArrayTag)
            return IdentificationResult(position, JsonElementType_Array);
        else if(value[position] != whitespace)
            return IdentifyJsonValue(position, value);
    }

    return IdentificationResult(std::string::npos, JsonElementType_Unknown);
}

IdentificationResult JsonObjectIdentifier::IdentifyJsonValue(std::string::size_type position, std::string value) const
{
    if(value[position] == keyValuePairDelimiter)
        throw JsonObjectIdentficationException("The first sign of a JsonValue cannot be " + std::to_string(keyValuePairDelimiter));

    std::string::size_type startPosition = position;

    InsideStringLiteralState insideStringState;

    for(;position < value.size();++position)
    {
        if(insideStringState.HandleState(value[position]) && value[position] == keyValuePairDelimiter)
            return IdentificationResult(startPosition, JsonElementType_KeyValuePair);
    }

    return IdentificationResult(startPosition, JsonElementType_SingleValue);
}

