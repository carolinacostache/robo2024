#include "ButtonLEDController.h"

Controls::Controls(const int ledPins[6]) {
    for (int i = 0; i < 6; i++) {
        if (ledPins[i] < 0) continue; // Avoid invalid entries
        this->ledPins[i] = ledPins[i];
        pinMode(ledPins[i], OUTPUT);
        lastDebounceTime[i] = 0;
    }
}


int Controls::readButton() {
    int buttonValuePlayer1 = analogRead(buttonPinPlayer1);
    int buttonValuePlayer2 = analogRead(buttonPinPlayer2);

    for (int i = 0; i < 3; i++) {
        if (buttonValuePlayer1 >= buttonRangesPlayer1[i][0] && buttonValuePlayer1 <= buttonRangesPlayer1[i][1]) {
            if ((millis() - lastDebounceTime[i]) > debounceDelay) {
                lastDebounceTime[i] = millis();
                return i;
            }
        }
    }

    for (int i = 3; i < 6; i++) {
        if (buttonValuePlayer2 >= buttonRangesPlayer2[i][0] && buttonValuePlayer2 <= buttonRangesPlayer2[i][1]) {
            if ((millis() - lastDebounceTime[i]) > debounceDelay) {
                lastDebounceTime[i] = millis();
                return i;
            }
        }
    }

    return -1;
}

void Controls::setLED(int index, bool state) {
    if (index >= 0 && index < 6) {
        digitalWrite(ledPins[index], state ? HIGH : LOW);
    }
}

void Controls::resetLEDS(int index){
    if (index >= 0 && index < 6){
        digitalWrite(ledPins[index], LOW);
    }
}
