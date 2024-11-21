#include "Configuration.h"


bool gameRunning = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;


const int LED_PINS_PLAYER1[3] = {3, 4, 5};
const int LED_PINS_PLAYER2[3] = {6, 7,8};
const int RGB_PIN_PLAYER1_RED = A2;
const int RGB_PIN_PLAYER1_GREEN = A3;
const int RGB_PIN_PLAYER1_BLUE = A4;
const int RGB_PIN_PLAYER2_BLUE = A5;
const int RGB_PIN_PLAYER2_RED = 2;
const int RGB_PIN_PLAYER2_GREEN = 1;

Game game;
Display display(8, 6, 5, 4, 3, 2);
Controls buttonLEDControllerPlayer1(LED_PINS_PLAYER1);
Controls buttonLEDControllerPlayer2(LED_PINS_PLAYER2);
SPIComms spi;
ServoController motor(9);

unsigned long welcomeMessageStartTime = 0;
const unsigned long welcomeMessageDuration = 5000;
unsigned long endMessageStartTime = 0;
const unsigned long endMessageDuration = 5000;
unsigned long roundStartTime = 0;
const unsigned long roundCountdownDuration = 5000;
unsigned long reactionStartTime = 0;
unsigned long roundTimerStart = 0;                 
const unsigned long maxRoundTime = 30000;
int countdownTime = 5;
int currentRound = 0;

String player1Name = "";
String player2Name = "";
bool nameEntryComplete = false;
bool isEnteringPlayer1 = true;

GameState gameState = IDLE;
Color currentColor;
bool player1Starts = true;
int player1Score = 0;
int player2Score = 0;
int winner = 0;

const int maxScore = 100;
const int minScore = 0;
const unsigned long maxReactionTime = 3000;
bool gameStarted = false;

void setupDisplay(Display &display) {
    display.showWelcomeMessage();
    delay(2000);
    display.updateScore(0, 0);
}

void setupSPI(SPIComms &spi) {
    spi.sendData(0);
}

void setupServo(ServoController &motor) {
    motor.resetPosition();
}


void initializeGame(Game &game) {
    game.startGame();
}

void setRGBColor(const int rgbPinRed,const int rgbPinGreen, const int rgbPinBlue, Color color) {

    
    // Ensure the RGB pins are within a valid range for PWM
    if (rgbPinRed >= 0 && rgbPinGreen >= 0 && rgbPinBlue >= 0 && 
        rgbPinRed <= 13 && rgbPinGreen <= 13 && rgbPinBlue <= 13) {
        
        switch (color) {
            case RED:
                analogWrite(rgbPinRed, 255);      // Red channel full intensity
                analogWrite(rgbPinGreen, 0);      // Green off
                analogWrite(rgbPinBlue, 0);       // Blue off
                break;
            case GREEN:
                analogWrite(rgbPinRed, 0);        // Red off
                analogWrite(rgbPinGreen, 255);    // Green full intensity
                analogWrite(rgbPinBlue, 0);       // Blue off
                break;
            case BLUE:
                analogWrite(rgbPinRed, 0);        // Red off
                analogWrite(rgbPinGreen, 0);      // Green off
                analogWrite(rgbPinBlue, 255);     // Blue full intensity
                break;
        }
    }
}

void clearRGBColor(const int rgbPinRed, const int rgbPinGreen, const int rgbPinBlue) {


    // Ensure the RGB pins are within a valid range for PWM
    if (rgbPinRed >= 0 && rgbPinGreen >= 0 && rgbPinBlue >= 0 && 
        rgbPinRed <= 13 && rgbPinGreen <= 13 && rgbPinBlue <= 13) {
        
        analogWrite(rgbPinRed, 0);
        analogWrite(rgbPinGreen, 0);
        analogWrite(rgbPinBlue, 0);
    }
}
