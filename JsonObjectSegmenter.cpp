#include "JsonObjectSegmenter.h"

JsonObjectSegmenter::JsonObjectSegmenter()
{
    //ctor
}

JsonObjectSegmenter::~JsonObjectSegmenter()
{
    //dtor
}

void AssertJsonObjectSegmentString(std::string& source, JsonElementType type)
{
    char openTag, closeTag;
    std::string segmentType;

    if(type == JsonElementType_Object)
    {
        openTag = openJsonObjectTag;
        closeTag = closeJsonObjectTag;
        segmentType = "JsonObjectSegmentString";
    }
    else if(type == JsonElementType_Array)
    {
        openTag = openJsonArrayTag;
        closeTag = closeJsonArrayTag;
        segmentType = "JsonArraySegmentString";
    }
    else
        return;

    if(!(stringhelper::StartsWith(source, openTag) && stringhelper::EndsWith(source, closeTag)))
    {
        std::stringstream stream;
        std::string errorMessage;
        stream << "Invalid " << segmentType << ": source must start with: " << openJsonObjectTag
            << " and end with: " << closeJsonObjectTag;
        stream >> errorMessage;

        throw std::invalid_argument(errorMessage);
    }
}

void JsonObjectSegmenter::SegmentJsonString(std::vector<std::string>& target, std::string source, JsonElementType type)
{
    if(type == JsonElementType_singleValue || type == JsonElementType_Unknown)
        throw std::invalid_argument("JsonElementType: " + JsonElementTypes[type] + " is not supported." );

    stringhelper::Trim(source);

    std::string::size_type offset = 0;
    char delimiter;

    if(type == JsonElementType_KeyValuePair)
    {
        // ev stringliteraltag validieren?
        delimiter = ':';
    }
    else if(type == JsonElementType_Array || type == JsonElementType_Object)
    {
        AssertJsonObjectSegmentString(source, type);
        delimiter = ',';
        offset = 1;
    }

    JsonObjectSegmenterIgnoreSignState delimiterState;

    std::string::size_type startposition = 0 + offset;

    for(std::string::size_type i = 0 + offset;i < source.size() - offset;++i)
    {
        char current = source[i];

        // auslagern auf klasse mit CheckAndSwitchOn sowas in der Art.
        if(delimiterState.AllSwitchesOff())
        {
            if(delimiterState.IsOnSwitch(current))
                delimiterState.ToggleSwitchOn(current);
            else if(current == delimiter)
            {
                std::string tmp = source.substr(startposition, i - startposition);
                target.push_back(tmp);

                source.erase(0, i + 1);
                i = 0;
                startposition = 0;
            }
        }
        else
            delimiterState.TryToggleSwitchOff(current);
    }

    std::string tmp = source.substr(startposition, source.size() - offset);
    target.push_back(tmp);

    assert((delimiterState.AllSwitchesOff(), "All DelimiterState- Switches should be of."));

    //Make them usable remove whitespaces and controlsigns

    for(std::string& segment: target)
    {
        for(std::string::size_type i = 0;i < segment.size();++i)
        {

        }
    }
}

void JsonObjectSegmenter::PrintSegments(std::ostream* targetStream, std::vector<std::string>& source)
{
    for(const auto& segment: source)
        *targetStream << " - " << segment;

    *targetStream << std::endl;
}
