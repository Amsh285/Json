#ifndef JSONNODE_H
#define JSONNODE_H

#include <string>

class JsonNode
{
    public:
        virtual ~JsonNode();
        virtual std::string ToJsonString() = 0;

        void IncreaseDepth();
    protected:
        JsonNode();
        JsonNode(std::string name);

        std::string name;
        int depth;
    private:

};

#endif // JSONNODE_H
