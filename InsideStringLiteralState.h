#ifndef INSIDESTRINGLITERALSTATE_H
#define INSIDESTRINGLITERALSTATE_H

#include "FlipSwitch.h"
#include "JsonUtilities.h"
#include "GlobalJsonDefinitions.h"

class InsideStringLiteralState
{
    public:
        InsideStringLiteralState();
        virtual ~InsideStringLiteralState();

        bool HandleState(const char& currentValue);
    protected:

    private:
        char IdentificationToken;
        bool isActive;
};

#endif // INSIDESTRINGLITERALSTATE_H
