#ifndef JSONPARSEREXCEPTION_H
#define JSONPARSEREXCEPTION_H

#include <stdexcept>
#include <string>

class JsonParserException : public std::exception
{
    public:
        JsonParserException(std::string errorMessage);
        virtual ~JsonParserException();

        virtual const char* what() const throw();
    protected:

    private:
        std::string errorMessage;
};

#endif // JSONPARSEREXCEPTION_H
