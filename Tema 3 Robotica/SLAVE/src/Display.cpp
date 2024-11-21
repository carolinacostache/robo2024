#include "Display.h"
#include "Configuration.h"

extern String player1Name;
extern String player2Name;

Display::Display(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) 
    : lcd(rs, enable, d4, d5, d6, d7) {
    lcd.begin(16, 2);
}

void Display::showWelcomeMessage() {
    lcd.clear();
    lcd.print("Welcome to the game!");
}

void Display::setPlayerNames(const String &name1, const String &name2) {
    player1Name = name1;
    player2Name = name2;
}

void Display::updateScore(int score1, int score2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(player1Name + ": ");
    lcd.print(score1);
    lcd.setCursor(0, 1);
    lcd.print(player2Name + ": ");
    lcd.print(score2);
}

void Display::showWinner(int winner) {
    lcd.clear();
    lcd.print("Winner: ");
    lcd.print(winner == 0 ? player1Name : player2Name);
    
}

void Display::print(const String &message) {
    lcd.clear();
    lcd.print(message);
}

void Display::setCountdown(int countdownTime) {
    lcd.setCursor(0, 1);
    lcd.print("Countdown: ");
    lcd.print(countdownTime);
}

void Display::clearCountdown() {
    lcd.setCursor(0, 1);
    lcd.print("            ");
}