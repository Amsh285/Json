#include "JsonObjectSegmenterInsideStringLiteralState.h"

JsonObjectSegmenterInsideStringLiteralState::JsonObjectSegmenterInsideStringLiteralState()
{
    this->isActive = false;
}

JsonObjectSegmenterInsideStringLiteralState::~JsonObjectSegmenterInsideStringLiteralState()
{
    //dtor
}

bool JsonObjectSegmenterInsideStringLiteralState::HandleState(const char& currentValue)
{
    bool canExecute = !this->isActive;
    bool isOnToken = currentValue == IdentificationToken;

    if(isOnToken)
        this->isActive = !this->isActive;

    return canExecute && !isOnToken;
}
