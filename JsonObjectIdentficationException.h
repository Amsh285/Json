#ifndef JSONOBJECTIDENTFICATIONEXCEPTION_H
#define JSONOBJECTIDENTFICATIONEXCEPTION_H

#include <exception>
#include <string>

class JsonObjectIdentficationException : public std::exception
{
    public:
        JsonObjectIdentficationException(std::string errorMessage);
        virtual ~JsonObjectIdentficationException();

        virtual const char * what () const throw ();
    protected:

    private:
        std::string errorMessage;
};

#endif // JSONOBJECTIDENTFICATIONEXCEPTION_H
