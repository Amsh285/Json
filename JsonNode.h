#ifndef JSONNODE_H
#define JSONNODE_H

#include <string>

class JsonNode
{
    public:
        virtual ~JsonNode();
        virtual std::string ToJsonString() = 0;

        std::string GetName() const { return name; };
        int GetDepth() const { return depth; };
    protected:
        JsonNode();
        JsonNode(std::string name);

        std::string name;
        int depth;
    private:

};

#endif // JSONNODE_H
