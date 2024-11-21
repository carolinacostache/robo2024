#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Arduino.h>
#include <SPICommunication.h>
#include <ButtonLEDController.h>
#include <Game.h>
#include <Display.h>
#include <ServoController.h>

void setupSPI(SPIComms &spi);
void setupControls(Controls &controlsPlayer1, Controls &controlsPlayer2);
void initializeGame(Game &game);
void setRGBColor(const int rgbPinRed, const int rgbPinGreen, const int rgbPinBlue, Color color);
void clearRGBColor(const int rgbPinRed, const int rgbPinGreen, const int rgbPinBlue);

extern bool gameRunning;
extern unsigned long lastDebounceTime;
extern const unsigned long debounceDelay;

extern const int LED_PINS_PLAYER1[3];
extern const int LED_PINS_PLAYER2[3];
extern const int RGB_PIN_PLAYER1_RED;
extern const int RGB_PIN_PLAYER2_RED;
extern const int RGB_PIN_PLAYER1_GREEN;
extern const int RGB_PIN_PLAYER1_BLUE;
extern const int RGB_PIN_PLAYER2_BLUE;
extern const int RGB_PIN_PLAYER2_GREEN;

extern Game game;
extern Controls buttonLEDControllerPlayer1;
extern Controls buttonLEDControllerPlayer2;
extern SPIComms spi;

extern unsigned long welcomeMessageStartTime;
extern const unsigned long welcomeMessageDuration;
extern unsigned long endMessageStartTime;
extern const unsigned long endMessageDuration;
extern unsigned long roundStartTime;
extern const unsigned long roundCountdownDuration;
extern unsigned long reactionStartTime;
extern unsigned long roundTimerStart;                 
extern const unsigned long maxRoundTime;
extern int countdownTime;
extern int currentRound;

extern String player1Name;
extern String player2Name;
extern bool nameEntryComplete;
extern bool isEnteringPlayer1;

extern GameState gameState;
extern Color currentColor;
extern bool player1Starts;
extern int player1Score;
extern int player2Score;
extern int winner;

extern const int maxScore;
extern const int minScore;
extern const unsigned long maxReactionTime;
extern bool gameStarted;
#endif
