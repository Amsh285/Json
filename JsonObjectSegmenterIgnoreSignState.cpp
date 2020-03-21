#include "JsonObjectSegmenterIgnoreSignState.h"

#define ToggleOff 0
#define ToggleOn 1

JsonObjectSegmenterIgnoreSignState::JsonObjectSegmenterIgnoreSignState()
{
    this->switches = {
        FlipSwitchTuple(openJsonObjectTag, closeJsonObjectTag, false),
        FlipSwitchTuple(openJsonArrayTag, closeJsonArrayTag, false),
        FlipSwitchTuple(stringLiteralTag, stringLiteralTag, false)
    };

    stringLiteralSwitch = &switches[2];
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

bool JsonObjectSegmenterIgnoreSignState::IsStringLiteralSwitch(char value)
{
    return value == stringLiteralTag;
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

void JsonObjectSegmenterIgnoreSignState::ToggleSwitchOn(const char& switchName)
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

void JsonObjectSegmenterIgnoreSignState::ToggleSwitchOff(const char& value)
{
    ToggleSwitch(value, ToggleOff);
}

void JsonObjectSegmenterIgnoreSignState::ToggleSwitch(const char& value, const int mode)
{
    bool switchFound = false;

    for(auto& sw: this->switches)
    {
        char switchToken = mode == ToggleOff ? std::get<1>(sw) : std::get<0>(sw);

        if(switchToken == value)
        {
            assert((std::get<2>(sw), "Tried to toggle off an inactive switch."));
            std::get<2>(sw) = false;
            switchFound = true;
        }
    }

    if(!switchFound)
    {
        std::stringstream stream;
        std::string errorMessage;

        stream << "Es wurde kein Switch für den Suchwert: " << value << " gefunden.";
        stream >> errorMessage;
        throw std::invalid_argument(errorMessage);
    }
}




// ev wieder aus der Klasse ziehen. Sehr spezifische Logik gehört hier nicht her.
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
    return std::get<2>(*this->stringLiteralSwitch);
}
