#ifndef BUTTONLEDCONTROLLER_H
#define BUTTONLEDCONTROLLER_H

#include <Arduino.h>

class Controls {
public:
    Controls(const int ledPins[6]);
    int readButton();
    void setLED(int index, bool state);
    void resetLEDS(int index);

private:
    int ledPins[3];
    const int buttonPinPlayer1 = A0;
    const int buttonPinPlayer2 = A1;


    const int buttonRangesPlayer1[3][2] = {
        //TREBUIE TESTATE SI ADAUGATE VALORILE BUNE PENTRU BUTOANE
        {1009, 1020}, 
        {999, 1007},
        {984, 997}
    };

    const int buttonRangesPlayer2[3][2] = {
    //TREBUIE TESTATE SI ADAUGATE VALORILE BUNE PENTRU BUTOANE
        {953, 982},
        {910, 951},
        {870, 905}
    };

    unsigned long lastDebounceTime[6];
    const unsigned long debounceDelay = 50;
};

#endif
