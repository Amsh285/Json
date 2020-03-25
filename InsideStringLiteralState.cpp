#include "InsideStringLiteralState.h"

InsideStringLiteralState::InsideStringLiteralState()
{
    this->isActive = false;
}

InsideStringLiteralState::~InsideStringLiteralState()
{
    //dtor
}

bool InsideStringLiteralState::HandleState(const char& currentValue)
{
    bool canExecute = !this->isActive;
    bool isOnToken = currentValue == IdentificationToken;

    if(isOnToken)
        this->isActive = !this->isActive;

    return canExecute && !isOnToken;
}
