#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class Display {
public:
    Display(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    void showWelcomeMessage();
    void setCountdown(int countdownTime);
    void clearCountdown();
    void setPlayerNames(const String &name1, const String &name2);
    void updateScore(int score1, int score2);
    void showWinner(int winner);
    void print(const String &message);

private:
    LiquidCrystal lcd;
};

#endif
