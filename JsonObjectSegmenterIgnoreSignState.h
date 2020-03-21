#ifndef JSONOBJECTSEGMENTERIGNOREDELIMITERSTATE_H
#define JSONOBJECTSEGMENTERIGNOREDELIMITERSTATE_H

#include <string>
#include <tuple>
#include <vector>
#include <stdexcept>
#include <assert.h>
#include <sstream>

#include "Utilities.h"

typedef std::tuple<char, char, bool> FlipSwitchTuple;

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

        void ToggleSwitchOn(const char& switchName);
        void ToggleSwitchOff(const char& switchName);

        void TryToggleSwitchOff(char attemptingValue);

    protected:

    private:
        void ToggleSwitch(const char& value, const int mode);
        bool CanToggleSwitch(const char& value);

        const FlipSwitchTuple* stringLiteralSwitch;
        std::vector<FlipSwitchTuple> switches;
};

#endif // JSONOBJECTSEGMENTERIGNOREDELIMITERSTATE_H
