#ifndef JSONOBJECTIDENTIFIER_H
#define JSONOBJECTIDENTIFIER_H

#include <string>

#include "InsideStringLiteralState.h"
#include "JsonObjectIdentficationException.h"
#include "JsonUtilities.h"

class IdentificationResult
{
    public:
        IdentificationResult(std::string::size_type position, GlobalJsonDefinitions::JsonElementType elementType);
        virtual ~IdentificationResult();

        std::string::size_type GetPosition() const { return position; };
        GlobalJsonDefinitions::JsonElementType GetElementType() const { return elementType; };
    private:
        std::string::size_type position;
        GlobalJsonDefinitions::JsonElementType elementType;
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
