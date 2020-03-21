#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <string>
#include <vector>
#include <sstream>

namespace stringhelper
{
    template<class TContainer>
    void Split(TContainer target, std::string& source, char delimiter);

    std::string TrimCopy(std::string target);

    void Trim(std::string& target);
    void LeftTrim(std::string& target);
    void RightTrim(std::string& target);

    bool StartsWith(const std::string& target, const char value);
    bool StartsWith(const std::string& target, const std::string& value);
    bool EndsWith(const std::string& target, const char value);
    bool EndsWith(const std::string& target, const std::string& value);
}
#endif // STRINGHELPER_H
