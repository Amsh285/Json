#include "JsonObject.h"

JsonObject::JsonObject(std::string name, JsonObject* parent, JsonObjectType objectType) : JsonNode(name)
{
    this->parent = parent;
    this->objectType = objectType;

    if(parent != nullptr)
        parent->AddChild(this);
}

JsonObject::~JsonObject()
{
    for(auto const& value: this->children)
        delete value;
}

std::string JsonObject::ToJsonString()
{
    std::string result = "";
    std::string openingBracket, closingBracket;

    if(this->objectType == JsonObjectType_Array)
    {
        openingBracket = "[";
        closingBracket = "]";
    }
    else
    {
        openingBracket = "{";
        closingBracket = "}";
    }

    if(name != "")
        result += "\"" + name + "\" : ";

    result += openingBracket + "\n";

    const std::string tab = "\t";
    std::string closingTabs = "";
    std::string tabs = tab;

    for(int i = 0;i < this->depth;++i)
    {
        closingTabs = tabs;
        tabs += tab;
    }

    std::vector<JsonNode*>::size_type childrenCount = this->children.size();

    for(std::vector<JsonNode*>::size_type i = 0;i < childrenCount;++i)
    {
        auto const& value = this->children[i];

        if(i < childrenCount - 1)
            result += tabs + value->ToJsonString() + "," + "\n";
        else
            result += tabs + value->ToJsonString() + "\n";
    }

    result += closingTabs + closingBracket;

    return result;
}

void JsonObject::AddChild(JsonNode *child)
{
    if(child == nullptr)
        throw std::invalid_argument("child cannot be null.");

    child->IncreaseDepth();
    this->children.push_back(child);
}
