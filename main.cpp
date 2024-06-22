#include <iostream>

#include "SnakeGame.hpp"

using namespace std;

int main() {
  int boardDimension = 10; // 10x10
  double gameSpeed = 0.2; // Game speed in seconds
  SnakeGame game(boardDimension, gameSpeed);

  while(!game.isGameOver()) {
    game.displayBoard();
    game.getMoveInput();
    game.moveSnake();
  }
}
