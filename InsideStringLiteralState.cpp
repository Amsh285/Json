#include "InsideStringLiteralState.h"

using namespace GlobalJsonDefinitions;

InsideStringLiteralState::InsideStringLiteralState()
{
    this->isActive = false;
    this->IdentificationToken = stringLiteralTag;
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
