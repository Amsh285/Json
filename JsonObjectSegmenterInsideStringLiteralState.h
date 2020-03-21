#ifndef JSONOBJECTSEGMENTERKEYVALUEPAIRVALIDATIONSTATE_H
#define JSONOBJECTSEGMENTERKEYVALUEPAIRVALIDATIONSTATE_H

#include "FlipSwitch.h"
#include "Utilities.h"

using namespace GlobalJsonDefinitions;

class JsonObjectSegmenterInsideStringLiteralState
{
    public:
        JsonObjectSegmenterInsideStringLiteralState();
        virtual ~JsonObjectSegmenterInsideStringLiteralState();

        bool HandleState(const char& currentValue);
    protected:

    private:
        const char IdentificationToken = stringLiteralTag;
        bool isActive;
};

#endif // JSONOBJECTSEGMENTERKEYVALUEPAIRVALIDATIONSTATE_H
