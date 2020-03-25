#ifndef INSIDESTRINGLITERALSTATE_H
#define INSIDESTRINGLITERALSTATE_H

#include "FlipSwitch.h"
#include "Utilities.h"

using namespace GlobalJsonDefinitions;

class InsideStringLiteralState
{
    public:
        InsideStringLiteralState();
        virtual ~InsideStringLiteralState();

        bool HandleState(const char& currentValue);
    protected:

    private:
        const char IdentificationToken = stringLiteralTag;
        bool isActive;
};

#endif // INSIDESTRINGLITERALSTATE_H
