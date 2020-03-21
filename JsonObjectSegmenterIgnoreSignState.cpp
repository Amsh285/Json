#include "JsonObjectSegmenterIgnoreSignState.h"

JsonObjectSegmenterIgnoreSignState::JsonObjectSegmenterIgnoreSignState()
    : locatedInJsonObjectSwitch (openJsonObjectTag, closeJsonObjectTag, false),
    locatedInJsonArraySwitch (openJsonArrayTag, closeJsonArrayTag, false)
{
    this->openObjectTagsEncountered = 0;
    this->openArrayTagsEncountered = 0;
}

JsonObjectSegmenterIgnoreSignState::~JsonObjectSegmenterIgnoreSignState()
{
    //dtor
}

bool JsonObjectSegmenterIgnoreSignState::OneSwitchOn()
{
    return locatedInJsonObjectSwitch.IsActive()
        || locatedInJsonArraySwitch.IsActive();
}

bool JsonObjectSegmenterIgnoreSignState::AllSwitchesOff()
{
    return !OneSwitchOn();
}

bool JsonObjectSegmenterIgnoreSignState::IsOnSwitch(const char& currentValue)
{
    return currentValue == this->locatedInJsonObjectSwitch.GetOnToken()
        || currentValue == this->locatedInJsonArraySwitch.GetOnToken();
}

bool JsonObjectSegmenterIgnoreSignState::IsOffSwitch(const char& currentValue)
{
    return currentValue == this->locatedInJsonObjectSwitch.GetOffToken()
        || currentValue == this->locatedInJsonArraySwitch.GetOffToken();
}

void JsonObjectSegmenterIgnoreSignState::HandleOnSwitch(const char& currentValue)
{
    assert((IsOnSwitch(currentValue), "currentValue has to be an OnToken."));

    if(currentValue == locatedInJsonObjectSwitch.GetOnToken())
    {
        if(openObjectTagsEncountered == 0)
            locatedInJsonObjectSwitch.Toggle();

        ++openObjectTagsEncountered;
    }
    else
    {
        if(openArrayTagsEncountered == 0)
            locatedInJsonArraySwitch.Toggle();

        ++openArrayTagsEncountered;
    }
}

void JsonObjectSegmenterIgnoreSignState::HandleOffSwitch(const char& currentValue)
{
    assert((IsOffSwitch(currentValue), "currentValue has to be an OffToken."));

    if(currentValue == locatedInJsonObjectSwitch.GetOffToken())
    {
        --openObjectTagsEncountered;

        if(openObjectTagsEncountered == 0)
            locatedInJsonObjectSwitch.Toggle();
    }
    else
    {
        --openArrayTagsEncountered;

        if(openArrayTagsEncountered == 0)
            locatedInJsonArraySwitch.Toggle();
    }
}

bool JsonObjectSegmenterIgnoreSignState::HandleState(const char& currentValue)
{
    bool canExecute = this->insideStringLiteralState.HandleState(currentValue);

    if(canExecute)
    {
        canExecute = AllSwitchesOff();

        if(IsOnSwitch(currentValue))
            HandleOnSwitch(currentValue);
        else if(IsOffSwitch(currentValue))
            HandleOffSwitch(currentValue);
    }

    return canExecute;
}
