#include "Arduino.h"
#include <Game.h>
#include <Display.h>
#include <Configuration.h>

Game::Game() : currentState(IDLE), player1Name("Player 1"),
      player2Name("Player 2"),
      player1Score(0),
      player2Score(0),
      currentRound(0){}

void Game::startGame() {
    currentRound = 0;
    player1Score = 0;
    player2Score = 0;
    display.print("Enter names or type skip.");
    currentState = ENTER_NAMES;
}

void Game::endGame() {
    if (player1Score > player2Score) {
        winner = 0;
        display.showWinner(winner);
    } else if (player1Score < player2Score) {
        winner = 1;
        display.showWinner(winner);
    } else {
        display.print("It's a tie!");
    }
    gameState = GAME_END_SCREEN;
}

int Game::calculateScore(unsigned long reactionTime) {
    if (reactionTime > maxReactionTime) return minScore;
    return map(reactionTime, 0, maxReactionTime, maxScore, minScore);
}
