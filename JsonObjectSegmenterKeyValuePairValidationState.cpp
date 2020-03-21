#include "JsonObjectSegmenterKeyValuePairValidationState.h"

JsonObjectSegmenterKeyValuePairValidationState::JsonObjectSegmenterKeyValuePairValidationState()
    : locatedInStringLiteralStateSwitch( stringLiteralTag, stringLiteralTag, false)
{

}

JsonObjectSegmenterKeyValuePairValidationState::~JsonObjectSegmenterKeyValuePairValidationState()
{
    //dtor
}

bool JsonObjectSegmenterKeyValuePairValidationState::HandleState(const char& currentValue)
{
    bool canExecute = !this->locatedInStringLiteralStateSwitch.IsActive();
    bool isOnToken = currentValue == this->locatedInStringLiteralStateSwitch.GetOnToken();

    if(currentValue == this->locatedInStringLiteralStateSwitch.GetOffToken() || isOnToken)
        this->locatedInStringLiteralStateSwitch.Toggle();

    return canExecute && !isOnToken;
}
