#include <Arduino.h>
#include <Game.h>
#include <Display.h>
#include <SPICommunication.h>
#include <Configuration.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <ButtonLEDController.h>

void setup() {
    Serial.begin(115200);
    pinMode(START_STOP_BUTTON_PIN, INPUT_PULLUP);
    setupDisplay(display);
    setupSPI(spi);
    randomSeed(analogRead(0));
    display.showWelcomeMessage();
    welcomeMessageStartTime = millis();

}

void loop() {
    static GameState gameState = IDLE;
    bool currentButtonState = digitalRead(START_STOP_BUTTON_PIN) == LOW;
    static bool lastButtonState = HIGH;

    if (currentButtonState != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (currentButtonState == LOW) {
            if (gameState == IDLE) {
                gameState = ENTER_NAMES;
                gameStarted = true;
            } else {
                gameState = IDLE;
                gameStarted = false;
                display.print("Games stopped!");
                motor.resetPosition();
            }
        }
    }
    lastButtonState = currentButtonState;

    int angle = map( millis() - roundStartTime , 0, roundCountdownDuration, 0, 180);
    motor.setPosition(angle);

    switch (gameState) {
        case IDLE:
            display.print("Press button to start the game!");
            break;

        case ENTER_NAMES:
            if (millis() - welcomeMessageStartTime < welcomeMessageDuration) {
                return;
            }

            if (!nameEntryComplete) {
                if (isEnteringPlayer1) {
                    Serial.println("Enter Player 1 Name (or type 'SKIP' to use default):");
                    isEnteringPlayer1 = false;
                } else if (player1Name == "") {
                    if (Serial.available() > 0) { 
                        player1Name = Serial.readStringUntil('\n');
                        player1Name.trim();
                        if (player1Name.equalsIgnoreCase("SKIP")) {
                            player1Name = "Player 1";
                        }
                        Serial.println("Enter Player 2 Name (or type 'SKIP' to use default):");
                    }
                } else if (player2Name == "") {
                    if (Serial.available() > 0) {
                        player2Name = Serial.readStringUntil('\n');
                        player2Name.trim();
                        if (player2Name.equalsIgnoreCase("SKIP")) {
                            player2Name = "Player 2";
                        }
                        nameEntryComplete = true;
                    }
                }
            }

            if (nameEntryComplete) {
                display.setPlayerNames(player1Name, player2Name);
                display.updateScore(0, 0);
                gameState = SELECTING_PLAYER;
            }

            break;

        case SELECTING_PLAYER:{
            int selectedPlayer = spi.receiveData();
            if (selectedPlayer == 1) {
                player1Starts = true;
                gameState = ROUND_COUNTDOWN;
            } else if (selectedPlayer == 2) {
                player1Starts = false;
                gameState = ROUND_COUNTDOWN;
            }

            break;}
    
        case ROUND_COUNTDOWN: {
            if (millis() - roundStartTime >= roundCountdownDuration) {
                if (countdownTime > 0) {
                    countdownTime--;
                }
                display.setCountdown(countdownTime);
                if (countdownTime == 0) {
                    display.clearCountdown();
                    gameState = player1Starts ? RUNNING_PLAYER1 : RUNNING_PLAYER2;
                    roundStartTime = millis();
                }
            }
            break;
        }


        case RUNNING_PLAYER1:
        case RUNNING_PLAYER2: {
    int currentPlayer = (gameState == RUNNING_PLAYER1) ? 1 : 2;
    
    Color currentColor = static_cast<Color>(random(0, 3));
    spi.sendData(currentColor);
    reactionStartTime = millis();
    unsigned long reactionTime = spi.receiveData();

    if (reactionTime > 0) {
        int score = game.calculateScore(reactionTime);
        if (currentPlayer == 1) {
            player1Score += score;
        } else {
            player2Score += score;
        }

        display.updateScore(player1Score, player2Score);
        gameState = ROUND_OVER;
    }

    if (millis() - roundTimerStart >= maxRoundTime) {
        if(currentPlayer == 1){
        clearRGBColor(RGB_PIN_PLAYER1_RED, RGB_PIN_PLAYER1_GREEN, RGB_PIN_PLAYER1_BLUE);
        gameState = ROUND_OVER;
        } else {
        clearRGBColor(RGB_PIN_PLAYER2_RED, RGB_PIN_PLAYER2_GREEN, RGB_PIN_PLAYER2_BLUE);
        gameState = ROUND_OVER;
        }
    } else {
        if(currentPlayer == 1){
        setRGBColor(RGB_PIN_PLAYER1_RED, RGB_PIN_PLAYER1_GREEN, RGB_PIN_PLAYER1_BLUE, currentColor);
        } else {
        setRGBColor(RGB_PIN_PLAYER2_RED, RGB_PIN_PLAYER2_GREEN, RGB_PIN_PLAYER2_BLUE, currentColor);
    }
    }
    break;
}

        case ROUND_OVER:
            if (currentRound < 3) {
                currentRound++;
                gameState = ROUND_COUNTDOWN;
            } else {
                gameState = GAME_OVER;
            }
            break;

        case GAME_OVER:
            display.showWinner(player1Score > player2Score ? 1 : 2);
            gameState = GAME_END_SCREEN;
            break;

        case GAME_END_SCREEN:
            if (millis() - endMessageStartTime < endMessageDuration){
                display.showWelcomeMessage();
                gameState = IDLE;
            }
            break;
    }
}