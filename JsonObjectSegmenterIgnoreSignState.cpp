#include "JsonObjectSegmenterIgnoreSignState.h"

JsonObjectSegmenterIgnoreSignState::JsonObjectSegmenterIgnoreSignState()
{
    this->switches = {
        FlipSwitch(openJsonObjectTag, closeJsonObjectTag, false),
        FlipSwitch(openJsonArrayTag, closeJsonArrayTag, false),
        FlipSwitch(stringLiteralTag, stringLiteralTag, false)
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
    assert((AllSwitchesOff(), "Only one switch can be toggled on." ));

    for(auto& sw: this->switches)
    {
        if(std::get<0>(sw) == switchName)
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
        if(std::get<1>(sw) == attemptingValue && std::get<2>(sw))
            std::get<2>(sw) = false;
    }
}
