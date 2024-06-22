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
  snake.moveUp();
  if(snake.didEatLastMove()) {
    setFoodPosition();
  }
}

void SnakeGame::moveDown() {
  snake.moveDown();
  if(snake.didEatLastMove()) {
    setFoodPosition();
  }
}

void SnakeGame::moveRight() {
  snake.moveRight();
  if(snake.didEatLastMove()) {
    setFoodPosition();
  }
}

void SnakeGame::moveLeft() {
  snake.moveLeft();
  if(snake.didEatLastMove()) {
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