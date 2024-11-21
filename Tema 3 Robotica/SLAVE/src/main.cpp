#include <Arduino.h>
#include "ButtonLEDController.h"
#include "SPICommunication.h"
#include "Configuration.h"

void setup() {
    setupSPI(spi);
    randomSeed(analogRead(0));
}

void loop() {
    int command = spi.receiveData();

    switch (command) {
        case ENTER_NAMES:
            if (Serial.available()) {
                String name = Serial.readStringUntil('\n');
                char buffer[32];
                name.toCharArray(buffer, sizeof(buffer));

                for (int i = 0; i < strlen(buffer); i++) {
                    spi.sendData(buffer[i]);
                }
                spi.sendData('\0');
            }
            break;

        case SELECTING_PLAYER: {
            int button1 = buttonLEDControllerPlayer1.readButton();
            int button2 = buttonLEDControllerPlayer2.readButton();

            if (button1 != -1) {
                spi.sendData(1);
            } else if (button2 != -1) {
                spi.sendData(2);
            }
            break;
        }

        case ROUND_COUNTDOWN:
        
            break;

        default:
            if (command >= RED && command <= BLUE) {
                setRGBColor(RGB_PIN_PLAYER1_RED, RGB_PIN_PLAYER1_GREEN, RGB_PIN_PLAYER1_BLUE, static_cast<Color>(command)); // Set RGB color
                unsigned long reactionStart = millis();
                while (true) {
                    int button = buttonLEDControllerPlayer1.readButton();
                    if (button == command) { // Correct button pressed
                        unsigned long reactionTime = millis() - reactionStart;
                        spi.sendData(reactionTime); // Send reaction time to Master
                        break;
                    }
                }
                clearRGBColor(RGB_PIN_PLAYER1_RED, RGB_PIN_PLAYER1_GREEN, RGB_PIN_PLAYER1_BLUE); // Clear the RGB color
            }
            break;
    }
}
