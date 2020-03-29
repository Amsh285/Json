#ifndef JSONOBJECTSEGMENTERIGNOREDELIMITERSTATE_H
#define JSONOBJECTSEGMENTERIGNOREDELIMITERSTATE_H

#include <string>
#include <tuple>
#include <vector>
#include <stdexcept>
#include <assert.h>
#include <sstream>

#include "FlipSwitch.h"
#include "JsonUtilities.h"
#include "InsideStringLiteralState.h"

class JsonObjectSegmenterIgnoreSignState
{
    public:
        JsonObjectSegmenterIgnoreSignState();
        virtual ~JsonObjectSegmenterIgnoreSignState();

        bool OneSwitchOn();
        bool AllSwitchesOff();

        bool HandleState(const char& currentValue);

    protected:

    private:
        bool IsOnSwitch(const char& currentValue);
        bool IsOffSwitch(const char& currentValue);
        void HandleOnSwitch(const char& currentValue);
        void HandleOffSwitch(const char& currentValue);

        InsideStringLiteralState insideStringLiteralState;
        FlipSwitch locatedInJsonObjectSwitch;
        FlipSwitch locatedInJsonArraySwitch;

        int openObjectTagsEncountered, openArrayTagsEncountered;
};

#endif // JSONOBJECTSEGMENTERIGNOREDELIMITERSTATE_H
