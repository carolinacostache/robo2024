/*for game logic, score and rounds*/

#include "Arduino.h"
#include <Game.h>
#include <Configuration.h>
#include <Display.h>

Game::Game() : currentState(IDLE), player1Name("Player 1"),
      player2Name("Player 2"),
      player1Score(0),
      player2Score(0),
      currentRound(0){}

void Game::startGame() {
    currentRound = 0;
    player1Score = 0;
    player2Score = 0;
    display.print("Before starting, u can enter player names or type skip.");
    currentState = ENTER_NAMES;
}

void Game::endGame() {
    if (player1Score > player2Score){
        winner = 0;
        display.showWinner(winner);
    } else if(player1Score < player2Score) {
        winner = 1;
        display.showWinner(winner);
    } else if(player1Score == player2Score) {
        display.print("It's a tie!");
    }
    gameState = GAME_END_SCREEN;
}

void Game::nextRound() {
    currentRound = currentRound + 1;
    if (currentRound <= 3) {
        startNextRoundCountdown();
    }

}

int Game::calculateScore(unsigned long reactionTime) {
    if (reactionTime > maxReactionTime) return minScore;
    return map(reactionTime, 0, maxReactionTime, maxScore, minScore);
}

void Game::startNextRoundCountdown() {
    display.print("Round " + String(currentRound) + " is starting in 5 seconds...");
    roundStartTime = millis();
    gameState = ROUND_COUNTDOWN;
}