#include "JsonObjectSegmenterIgnoreSignState.h"

JsonObjectSegmenterIgnoreSignState::JsonObjectSegmenterIgnoreSignState()
{
    stringLiteralSwitch = FlipSwitch(stringLiteralTag, stringLiteralTag, false);

    this->switches = {
        FlipSwitch(openJsonObjectTag, closeJsonObjectTag, false),
        FlipSwitch(openJsonArrayTag, closeJsonArrayTag, false),
        stringLiteralSwitch
    };
}

JsonObjectSegmenterIgnoreSignState::~JsonObjectSegmenterIgnoreSignState()
{
    //dtor
}

bool JsonObjectSegmenterIgnoreSignState::OneSwitchOn()
{
    for(auto& sw: this->switches)
    {
        if(std::get<2>(sw))
            return true;
    }

    return false;
}

bool JsonObjectSegmenterIgnoreSignState::AllSwitchesOff()
{
    return !OneSwitchOn();
}

bool JsonObjectSegmenterIgnoreSignState::IsOnSwitch(char value)
{
    for(auto& sw: this->switches)
    {
        if(std::get<0>(sw) == value)
            return true;
    }

    return false;
}

void JsonObjectSegmenterIgnoreSignState::ToggleSwitchOn(char switchName)
{
    for(auto& sw: this->switches)
    {
        if(std::get<0>(sw) == switchName && CanToggleSwitch(switchName))
        {
            assert((!std::get<2>(sw), "Tried to toggle on an active switch."));
            std::get<2>(sw) = true;
        }
    }
}

void JsonObjectSegmenterIgnoreSignState::TryToggleSwitchOff(char attemptingValue)
{
    for(auto& sw: this->switches)
    {
        bool currenSwitchIsOn = std::get<2>(sw);

        if(std::get<1>(sw) == attemptingValue && currenSwitchIsOn && CanToggleSwitch(attemptingValue))
            std::get<2>(sw) = false;
    }
}

bool JsonObjectSegmenterIgnoreSignState::CanToggleSwitch(const char& value)
{
    return value == stringLiteralTag || !StringLiteralSwitchOpen();
}

bool JsonObjectSegmenterIgnoreSignState::StringLiteralSwitchOpen()
{
    return std::get<2>(this->stringLiteralSwitch);
}
