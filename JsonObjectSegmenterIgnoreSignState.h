#ifndef JSONOBJECTSEGMENTERIGNOREDELIMITERSTATE_H
#define JSONOBJECTSEGMENTERIGNOREDELIMITERSTATE_H

#include <string>
#include <tuple>
#include <vector>
#include <stdexcept>
#include <assert.h>

#include "Utilities.h"

typedef std::tuple<char, char, bool> FlipSwitch;

using namespace GlobalJsonDefinitions;

class JsonObjectSegmenterIgnoreSignState
{
    public:
        JsonObjectSegmenterIgnoreSignState();
        virtual ~JsonObjectSegmenterIgnoreSignState();

        bool OneSwitchOn();
        bool AllSwitchesOff();
        bool StringLiteralSwitchOpen();

        bool IsStringLiteralSwitch(char value);
        bool IsOnSwitch(char value);

        void ToggleSwitchOn(char switchName);
        void TryToggleSwitchOff(char attemptingValue);

    protected:

    private:
        bool CanToggleSwitch(const char& value);

        const FlipSwitch* stringLiteralSwitch;
        std::vector<FlipSwitch> switches;
};

#endif // JSONOBJECTSEGMENTERIGNOREDELIMITERSTATE_H
