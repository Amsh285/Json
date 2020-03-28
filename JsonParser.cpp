#include "JsonParser.h"

JsonParser::JsonParser()
{
    //ctor
}

JsonParser::~JsonParser()
{
    //dtor
}

std::string BuildJsonStringLiteralTagCountOddErrorMessage(std::size_t numOfStringLiteralTags)
{
    std::string errorMessage = "Invalid Json Data. Number of Stringliteral- Tags: " +
        std::to_string(numOfStringLiteralTags) + "There is somewhere a Stringliteral that is not closed.";

    return errorMessage;
}

std::string BuildJsonOpenCloseTagUnEqualErrorMessage(char openTag, std::size_t openTagOccurences, char closeTag, std::size_t closeTagOccurences)
{
    std::string errorMessage = "Invalid json Data. Occurences of opening Tags: " +
        std::to_string(openTag) + " - " + std::to_string(openTagOccurences) +
        " vs. Occurences of closing Tags: " + std::to_string(closeTag) + " - " + std::to_string(closeTagOccurences);

    return errorMessage;
}

void ValidateJsonFormat(const std::string& value)
{
    if(value == "")
        throw new std::invalid_argument("value cannot be empty.");

    std::size_t numOfopenJsonObjectTags = 0, numOfcloseJsonObjectTags = 0, numOfopenJsonArrayTags = 0, numOfcloseJsonArrayTags = 0,
        numOfStringLiteralTags = 0;

    bool stringliteralOpen = false;

    for(std::string::size_type i = 0;i < value.size();++i)
    {
        if(value[i] == stringLiteralTag)
        {
            ++numOfStringLiteralTags;
            stringliteralOpen = !stringliteralOpen;
        }

        //Tags in Stringliterals do not count for Object or Array interpretation.
        if(!stringliteralOpen)
        {
            if(value[i] == openJsonObjectTag)
                ++numOfopenJsonObjectTags;
            else if(value[i] == closeJsonObjectTag)
                ++numOfcloseJsonObjectTags;
            else if(value[i] == openJsonArrayTag)
                ++numOfopenJsonArrayTags;
            else if(value[i] == closeJsonArrayTag)
                ++numOfcloseJsonArrayTags;
        }
    }

    if(stringliteralOpen)
        throw std::invalid_argument(BuildJsonStringLiteralTagCountOddErrorMessage(numOfStringLiteralTags));
    if(numOfopenJsonObjectTags != numOfcloseJsonObjectTags)
        throw std::invalid_argument(BuildJsonOpenCloseTagUnEqualErrorMessage(openJsonObjectTag, numOfopenJsonObjectTags, closeJsonObjectTag, numOfcloseJsonObjectTags));
    if(numOfopenJsonArrayTags != numOfcloseJsonArrayTags)
        throw std::invalid_argument(BuildJsonOpenCloseTagUnEqualErrorMessage(openJsonArrayTag, numOfopenJsonArrayTags, closeJsonArrayTag, numOfcloseJsonArrayTags));
}

/* Gültigkeiten
    Object { KeyValuePair },
    Array { Object, Array, singlevalue }
    KeyValuePair { Object, Array, Singlevalue }
*/
void ValidateJsonElementType(JsonElementType parentType, IdentificationResult segmentType, std::vector<JsonElementType> allowedTypes)
{
    std::string errorMessage = "Der Elementtyp: " + JsonElementTypes[segmentType.GetElementType()] +
        " ist nicht erlaubt fuer den Elementtypen: " + JsonElementTypes[parentType];

    if(!(std::find(allowedTypes.begin(), allowedTypes.end(), segmentType.GetElementType()) != allowedTypes.end()))
        throw JsonParserException(errorMessage);
}

void JsonParser::ParseJsonKeyValuePair(const std::string& objectSegment, JsonObject* parent)
{
    if(parent == nullptr)
        throw std::invalid_argument("ParseJsonKeyValuePair: parent cannot be null.");

    std::vector<std::string> keyValuePair;

    objectSegmenter.SegmentJsonString(keyValuePair, objectSegment, JsonElementType_KeyValuePair);

    if(keyValuePair.size() != 2)
        throw JsonParserException("ParseJsonKeyValuePair: expected keyValuePair.size() == 2, but was: " + std::to_string(keyValuePair.size()));

    IdentificationResult result = objectIdentifier.IdentifyElement(keyValuePair[1]);
    JsonElementType elementType = result.GetElementType();

    ValidateJsonElementType(JsonElementType_KeyValuePair, result, {JsonElementType_Object, JsonElementType_Array, JsonElementType_SingleValue});

    if(elementType == JsonElementType_Object)
        ParseJsonObject(keyValuePair[1], keyValuePair[0], parent);
    else if(elementType == JsonElementType_Array)
        ParseJsonArray(keyValuePair[1], keyValuePair[0], parent);
    else if(elementType == JsonElementType_SingleValue)
        ProcessSingleJsonValue(keyValuePair[1], keyValuePair[0], parent);
}

JsonNode* JsonParser::ParseJsonObject(const std::string& objectSegment, std::string name, JsonObject* parent)
{
    std::vector<std::string> segments;

    objectSegmenter.SegmentJsonString(segments, objectSegment, JsonElementType_Object);
    std::string normalizedName = GetNormalizedName(name);

    JsonObject* result = Create::A.JsonObject()
        .WithName(normalizedName)
        .WithJsonObjectType(JsonObjectType_Object)
        .WithParent(parent)
        .Build();

    for(const std::string& segment : segments)
    {
        IdentificationResult identification = objectIdentifier.IdentifyElement(segment);
        ValidateJsonElementType(JsonElementType_Object, identification, {JsonElementType_KeyValuePair} );

        ParseJsonKeyValuePair(segment, result);
    }

    return result;
}

JsonNode* JsonParser::ParseJsonArray(const std::string& objectSegment, std::string name, JsonObject* parent)
{
    std::vector<std::string> segments;

    objectSegmenter.SegmentJsonString(segments, objectSegment, JsonElementType_Array);
    std::string normalizedName = GetNormalizedName(name);

    JsonObject* result = Create::A.JsonObject()
        .WithName(normalizedName)
        .WithJsonObjectType(JsonObjectType_Array)
        .WithParent(parent)
        .Build();

    for(const std::string& segment : segments)
    {
        IdentificationResult identification = objectIdentifier.IdentifyElement(segment);
        JsonElementType elementType = identification.GetElementType();

        ValidateJsonElementType(JsonElementType_Array, identification, {JsonElementType_Object, JsonElementType_Array, JsonElementType_SingleValue} );

        if(elementType == JsonElementType_Object)
            ParseJsonObject(segment, "", result);
        else if(elementType == JsonElementType_Array)
            ParseJsonArray(segment, "", result);
        else if(elementType == JsonElementType_SingleValue)
            ProcessSingleJsonValue(segment, "", result);
    }

    return result;
}

JsonNode* JsonParser::ProcessSingleJsonValue(const std::string& value, const std::string& name, JsonObject* parent)
{
    std::string normalizedName = GetNormalizedName(name);

    return Create::A.JsonValue()
        .WithName(normalizedName)
        .WithRawValue(value)
        .WithParent(parent)
        .Build();
}

JsonNode* JsonParser::ParseJsonString(const std::string& value)
{
    if(value == "" || value.find_first_not_of(" ") == std::string::npos)
        throw std::invalid_argument("value cannot be empty or whitespace only.");

    ValidateJsonFormat(value);

    IdentificationResult firstElement = objectIdentifier.IdentifyElement(value);
    JsonElementType firstElementType = firstElement.GetElementType();

    if(firstElementType == JsonElementType_Unknown)
        throw new std::invalid_argument("no valid Jsonelement found in value");

    if(firstElementType == JsonElementType_Object)
        return ParseJsonObject(value, "", nullptr);
    else if(firstElementType == JsonElementType_Array)
        return ParseJsonArray(value, "", nullptr);
    else if(firstElementType == JsonElementType_SingleValue)
        return ProcessSingleJsonValue(stringhelper::TrimCopy(value), "", nullptr);
}

std::string JsonParser::GetNormalizedName(const std::string name)
{
    std::string trimmedName = stringhelper::TrimCopy(name);

    if(trimmedName[0] == '\"')
        trimmedName = trimmedName.substr(1, trimmedName.size() - 1);

    if(trimmedName[trimmedName.size() - 1] == '\"')
        trimmedName = trimmedName.substr(0, trimmedName.size() - 1);

    return trimmedName;
}
