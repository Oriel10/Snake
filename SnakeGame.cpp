#include <cstdlib> // for rand() 
#include <ctime>   // for time()

#include "SnakeGame.hpp"

Position SnakeGame::getPosition() const {
  // Seed the random number generator
  srand(static_cast<unsigned>(time(0)));

  // Generate and print a random number between 1 and 5
  int row = rand() % boardDimension;
  int col = rand() % boardDimension;
  return Position{row, col};
}

SnakeGame::SnakeGame(int boardDimension) : boardDimension(boardDimension), snake(boardDimension) {
  setFoodPosition();
}

void SnakeGame::moveUp() {
  bool didEat = snake.moveUp();
  if(didEat) {
    setFoodPosition();
  }
}

void SnakeGame::moveDown() {
  bool didEat = snake.moveDown();
  if(didEat) {
    setFoodPosition();
  }
}

void SnakeGame::moveRight() {
  bool didEat = snake.moveRight();
  if(didEat) {
    setFoodPosition();
  }
}

void SnakeGame::moveLeft() {
  bool didEat = snake.moveLeft();
  if(didEat) {
    setFoodPosition();
  }
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

Position SnakeGame::getFoodPosition() const {
  return foodPosition;
}

char SnakeGame::getFoodMark() const {
  return foodMark;
}

const Snake& SnakeGame::getSnake() const {
    return snake;
  }