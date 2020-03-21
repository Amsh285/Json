#ifndef JSONOBJECTSEGMENTERKEYVALUEPAIRVALIDATIONSTATE_H
#define JSONOBJECTSEGMENTERKEYVALUEPAIRVALIDATIONSTATE_H

#include "FlipSwitch.h"
#include "Utilities.h"

using namespace GlobalJsonDefinitions;

class JsonObjectSegmenterKeyValuePairValidationState
{
    public:
        JsonObjectSegmenterKeyValuePairValidationState();
        virtual ~JsonObjectSegmenterKeyValuePairValidationState();

        bool HandleState(const char& currentValue);
    protected:

    private:
        FlipSwitch locatedInStringLiteralStateSwitch;
};

#endif // JSONOBJECTSEGMENTERKEYVALUEPAIRVALIDATIONSTATE_H
