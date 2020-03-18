#include "JsonParser.h"

const char openJsonObjectTag = '{', closeJsonObjectTag = '}';
const char openJsonArrayTag = '{', closeJsonArrayTag = '}';
const char stringLiteralTag = '"';
const char whitespace = ' ';

enum JsonElementType
{
    JsonElementType_Object,
    JsonElementType_Array,
    JsonElementType_Value,
    JsonElementType_singleValue,
    JsonElementType_KeyValuePair,
    JsonElementType_Unknown
};

typedef std::tuple<std::string::size_type, JsonElementType> IndentificationResult;

JsonParser::JsonParser()
{
    //ctor
}

JsonParser::~JsonParser()
{
    //dtor
}

typedef std::tuple<char, char, bool> FlipSwitch;

bool OneSwitchOn(std::vector<FlipSwitch> switches)
{
    for(auto& sw: switches)
    {
        if(std::get<2>(sw))
            return true;
    }

    return false;
}

bool AllSwitchesOff(std::vector<FlipSwitch> switches)
{
    return !OneSwitchOn(switches);
}

bool IsOnSwitch(std::vector<FlipSwitch> switches, char value)
{
    for(auto& sw: switches)
    {
        if(std::get<0>(sw) == value)
            return true;
    }
}

void ToggleSwitchOn(std::vector<FlipSwitch> switches, char switchName)
{
    assert((AllSwitchesOff(switches), "Only one switch can be toggled on." ));

    for(auto& sw: switches)
    {
        if(std::get<0>(sw) == switchName)
        {
            assert((!std::get<2>(sw), "Tried to toggle on an active switch."));
            std::get<2>(sw) = true;
        }
    }
}

void TryToggleSwitchOff(std::vector<FlipSwitch> switches, char attemptingValue)
{
    for(auto& sw: switches)
    {
        if(std::get<1>(sw) == attemptingValue && std::get<2>(sw))
            std::get<2>(sw) = false;
    }
}

//Gesamte Segmentierung auslagern in Klasse JsonSegmenter!!!
template<class TContainer>
void SegmentJsonString(TContainer& target, std::string source)
{
    const char delimiter = ',';

    std::vector<FlipSwitch> radioSwitches = {
        FlipSwitch(openJsonObjectTag, closeJsonObjectTag, false),
        FlipSwitch(openJsonArrayTag, closeJsonArrayTag, false),
        FlipSwitch(stringLiteralTag, stringLiteralTag, false)
    };

    std::stringstream stream(source);
    std::string token;

    bool ignoreDelimiter = false;

    for(std::string::size_type i = 0;i < source.size();++i)
    {
        char current = source[i];

        if(AllSwitchesOff(radioSwitches))
        {
            if(IsOnSwitch(radioSwitches, current))
                ToggleSwitchOn(radioSwitches, current);
            else if(current == delimiter)
            {
                target.push_back(source.substr(0, i));
                source.erase(0, i + 1);
            }
        }
        else
            TryToggleSwitchOff(radioSwitches, current);
    }
}

std::string GetJsonStringDataSegment(const std::string& target, std::string::size_type startPosition, char closingTag)
{
    std::string::size_type lastIndexOfSearchValue = target.find_last_of(closingTag);
    assert((lastIndexOfSearchValue != std::string::npos, "lastIndexOfSearchValue should have found a closing Tag: " + closingTag));

    return target.substr(startPosition, ((closingTag - startPosition) + 1));
}

std::string BuildJsonStringLiteralTagCountOddErrorMessage(std::size_t numOfStringLiteralTags)
{
    std::string errorMessage;
    std::stringstream stream;

    stream << "Invalid Json Data. Number of Stringliteral- Tags: " << numOfStringLiteralTags <<
        "There is somewhere a Stringliteral that is not closed.";

    stream >> errorMessage;
    return errorMessage;
}

std::string BuildJsonOpenCloseTagUnEqualErrorMessage(char openTag, std::size_t openTagOccurences, char closeTag, std::size_t closeTagOccurences)
{
    std::string errorMessage;
    std::stringstream stream;

    stream << "Invalid json Data. Occurences of opening Tags: "
        << openTag << " - " << openTagOccurences
        << " vs. Occurences of closing Tags: "
        << closeTag << " - " << closeTagOccurences;

    stream >> errorMessage;
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
        if(stringliteralOpen)
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

IndentificationResult IdentifyFirstElement(const std::string& value)
{
    std::string::size_type position = std::string::npos;
    JsonElementType elementType = JsonElementType_Unknown;

    for(std::string::size_type i = 0;i < value.size();++i)
    {
        if(value[i] == openJsonObjectTag)
        {
            position = i;
            elementType = JsonElementType_Object;
        }
        else if(value[i] == openJsonArrayTag)
        {
            position = i;
            elementType = JsonElementType_Array;
        }
        else if(value[i] != whitespace)
        {
            position = i;
            elementType = JsonElementType_Value;
        }
    }

    return IndentificationResult(position, elementType);
}

JsonNode* ParseSingleJsonValue(const std::string& objectSegment)
{

}

JsonNode* ParseJsonKeyValuePair(const std::string& objectSegment)
{

}

JsonNode* ParseJsonArray(const std::string& objectSegment)
{

}

JsonNode* ParseJsonObject(const std::string& objectSegment)
{

}

JsonNode* JsonParser::ParseJsonString(const std::string& value)
{
    if(value == "" || value.find_first_not_of(" ") == std::string::npos)
        throw std::invalid_argument("value cannot be empty or whitespace only.");

    ValidateJsonFormat(value);

    IndentificationResult firstElement = IdentifyFirstElement(value);
    JsonElementType firstElementType = std::get<1>(firstElement);

    if(firstElementType == JsonElementType_Unknown)
        throw new std::invalid_argument("no valid Jsonelement found in value");

    std::string jsonRootElementSegment;

    if(firstElementType == JsonElementType_Object)
    {
        jsonRootElementSegment = GetJsonStringDataSegment(value, std::get<0>(firstElement), closeJsonObjectTag);
        return ParseJsonObject(jsonRootElementSegment);
    }


}
