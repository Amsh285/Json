#ifndef JSONOBJECTIDENTIFIER_H
#define JSONOBJECTIDENTIFIER_H

#include <string>

#include "InsideStringLiteralState.h"
#include "JsonObjectIdentficationException.h"
#include "Utilities.h"


using namespace GlobalJsonDefinitions;

//typedef std::tuple<std::string::size_type, JsonElementType> ;

class IdentificationResult
{
    public:
        IdentificationResult(std::string::size_type position, JsonElementType elementType);
        virtual ~IdentificationResult();

        std::string::size_type GetPosition() const { return position; };
        JsonElementType GetElementType() const { return elementType; };
    private:
        std::string::size_type position;
        JsonElementType elementType;
};

class JsonObjectIdentifier
{
    public:
        JsonObjectIdentifier();
        virtual ~JsonObjectIdentifier();

        IdentificationResult IdentifyElement(const std::string& value) const;
        IdentificationResult IdentifyElement(std::string::size_type position, const std::string& value) const;
        IdentificationResult IdentifyJsonValue(std::string::size_type startPosition, std::string value) const;
    protected:

    private:
};

#endif // JSONOBJECTIDENTIFIER_H
