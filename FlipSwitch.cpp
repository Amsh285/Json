#include "FlipSwitch.h"

FlipSwitch::FlipSwitch(char onToken, char offToken, bool isActive)
{
    this->onToken = onToken;
    this->offToken = offToken;
    this->isActive = isActive;
}

FlipSwitch::~FlipSwitch()
{
    //dtor
}

void FlipSwitch::Toggle()
{
    this->isActive = !this->isActive;
}
