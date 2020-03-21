#ifndef FLIPSWITCH_H
#define FLIPSWITCH_H


class FlipSwitch
{
    public:
        FlipSwitch(char onToken, char offToken, bool isActive);
        virtual ~FlipSwitch();

        char GetOnToken() { return this->onToken; };
        char GetOffToken() { return this->offToken; } ;
        bool IsActive() { return this->isActive; };

        void Toggle();
    protected:

    private:
        char onToken;
        char offToken;
        bool isActive;
};

#endif // FLIPSWITCH_H
