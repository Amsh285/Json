#include "StringHelper.h"

namespace stringhelper
{
    template<class TContainer>
    void Split(TContainer target, std::string& source, char delimiter)
    {
        std::stringstream stream(source);
        std::string token;

        while(std::getline(stream, token, delimiter))
            target.push_back(token);
    }

    std::string TrimCopy(std::string target)
    {
        Trim(target);
        return target;
    }

    void Trim(std::string& target)
    {
        LeftTrim(target);
        RightTrim(target);
    }

    void LeftTrim(std::string& target)
    {
        std::string::size_type i = 0;

        while(std::isspace(target[i]) && i < target.size())
            ++i;

        target.erase(0, i);
    }

    void RightTrim(std::string& target)
    {
        int elementsToRemove = 0;
        std::string::size_type i = target.size() - 1;

        while(std::isspace(target[i]) && i >= 0)
        {
            ++elementsToRemove;
            --i;
        }

        target.erase(target.size() - elementsToRemove, elementsToRemove);
    }

    bool StartsWith(const std::string& target, const char value)
    {
        return target.size() > 0 && target[0] == value;
    }

    bool StartsWith(const std::string& target, const std::string& value)
    {
        if(target.size() >= value.size())
        {
            return target.substr(0, value.size()) == value;
        }

        return false;
    }

    bool EndsWith(const std::string& target, const char value)
    {
        return target.size() >= 0 && target[target.size() - 1] == value;
    }

    bool EndsWith(const std::string& target, const std::string& value)
    {
        if(target.size() >= value.size())
        {
            return target.substr(target.size() - value.size(), value.size()) == value;
        }

        return false;
    }
}
