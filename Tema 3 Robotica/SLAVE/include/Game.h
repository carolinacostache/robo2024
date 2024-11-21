#ifndef GAME_H
#define GAME_H

#include "Arduino.h"
#include <Display.h>


enum Color { 
    RED,
    GREEN,
    BLUE 
};

enum GameState {
    IDLE = -1,
    ENTER_NAMES = 1,
    SELECTING_PLAYER = 2,
    ROUND_COUNTDOWN = 3,
    RUNNING_PLAYER1 = 4,
    RUNNING_PLAYER2 = 5,
    ROUND_OVER = 6,
    GAME_OVER = 7,
    GAME_END_SCREEN = 8
};

class Game {
public:
    Game(); 
    
    void startGame();
    void endGame();
    void startNextRoundCountdown();
    void stopRound();
    void nextRound();
    int calculateScore(unsigned long reactionTime);
    void updateScore(int player1Score, int player2Score);

private:
    GameState currentState;
    String player1Name;
    String player2Name;
    int player1Score;
    int player2Score;
    int currentRound;
    Display& display;
};

#endif
