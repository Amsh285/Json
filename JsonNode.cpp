#include "JsonNode.h"

JsonNode::JsonNode()
{
    this->name = "";
    this->depth = 0;
}

JsonNode::JsonNode(std::string name)
{
    this->name = name;
    this->depth = 0;
}

JsonNode::~JsonNode()
{
    //dtor
}
