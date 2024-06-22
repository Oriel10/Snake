#include <iostream>
#include <cstdlib> // for rand() 
#include <time.h>
#include <conio.h> // For _kbhit() and _getch() on Windows
#include <assert.h>
#include <chrono>
#include <thread>

#include "SnakeGame.hpp"

using namespace std::chrono;
using namespace std;

Position SnakeGame::getPosition() const {
  // Seed the random number generator
  srand(static_cast<unsigned>(time(nullptr)));

  // Generate and print a random number between 1 and 5
  int row = rand() % boardDimension;
  int col = rand() % boardDimension;
  return Position{row, col};
}

SnakeGame::SnakeGame(int boardDimension, double gameSpeed) : boardDimension(boardDimension), gameSpeed(gameSpeed), snake(boardDimension) {
  setFoodPosition();
}

void SnakeGame::setFoodPosition() {
  bool isOccupiedPos = true;
  while(isOccupiedPos) {
    Position newFoodPos = getPosition();
    isOccupiedPos = snake.isSnakeAt(newFoodPos);
    if(!isOccupiedPos) {
      foodPosition = newFoodPos;
      snake.setFoodPosition(newFoodPos);
    }
  }
}

bool SnakeGame::isGameOver() const {
  if(gameOver) {
    cout << "You lost!" << endl;
    cout << "Final Score: " << (snake.getLength() - 1) * scoreMultiple << endl;
    return true;
  }
  return false;
}

void SnakeGame::displayBoard() const {
  system("cls");
  std::cout << "+";
  for (int j = 0; j < boardDimension; ++j) {
    std::cout << "---+";
  }
  std::cout << "\n";

  for (int i = 0; i < boardDimension; ++i) {
    std::cout << "|";
    for (int j = 0; j < boardDimension; ++j) {
      char vacantCell = ' ';
      Position currentPosition = {i, j};

      bool isSnake = snake.isSnakeAt(currentPosition);
      bool isFood = (foodPosition == currentPosition);
      assert(!(isFood && isSnake));
      char drawChar = isSnake ? snake.getSnakeMark(currentPosition) : vacantCell;
      drawChar = isFood ? foodMark : drawChar;

      std::cout << " " << drawChar << " |";
    }
    std::cout << "\n";
    
    std::cout << "+";
    for (int j = 0; j < boardDimension; ++j) {
        std::cout << "---+";
    }
    std::cout << "\n";
  }
}

void SnakeGame::getMoveInput() {
  auto startTime = steady_clock::now();
  auto nowTime = steady_clock::now();

  Direction tmpDirection = snake.currDirection;
  duration<double> elapsed = nowTime - startTime;
  while(elapsed.count() <= gameSpeed) {
    nowTime = steady_clock::now();
    elapsed = nowTime - startTime;

    if (_kbhit()) {
      switch (_getch()) {
      case 'w':
        if(!snake.isLegitDirection(snake.currDirection, UP)) 
          continue;
        tmpDirection = UP;
        break;
      case 's':
        if(!snake.isLegitDirection(snake.currDirection, DOWN)) 
          continue;
        tmpDirection = DOWN;
        break;
      case 'a':
        if(!snake.isLegitDirection(snake.currDirection, LEFT)) 
          continue;
        tmpDirection = LEFT;
        break;
      case 'd':
        if(!snake.isLegitDirection(snake.currDirection, RIGHT)) 
          continue;
        tmpDirection = RIGHT;
        break;
      case 'x':
        gameOver = true;
        break;
      }
    }
  }
  snake.currDirection = tmpDirection;
}

void SnakeGame::moveSnake() {
  bool islegalMove = true;
  switch(snake.currDirection) {
    case UP:
      islegalMove = snake.moveUp();
      break;
    case DOWN:
      islegalMove = snake.moveDown();
      break;
    case LEFT:
      islegalMove = snake.moveLeft();
      break;
    case RIGHT:
      islegalMove = snake.moveRight();
      break;
    default:
      break;
  }
  if(snake.didEatLastMove()) {
    setFoodPosition();
  }
  gameOver = !islegalMove;
}