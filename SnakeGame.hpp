#ifndef SNAKEGAME_HPP
#define SNAKEGAME_HPP

#include "Snake.hpp"

class SnakeGame {
private:
  const char foodMark = '*';
  
  int boardDimension;
  Snake snake;
  Position foodPosition;

  Position getPosition() const;
public:
  SnakeGame(int boardDimension);
  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();
  void setFoodPosition();
  Position getFoodPosition() const;
  char getFoodMark() const;
  const Snake& getSnake() const;

};

#endif // SNAKEGAME_HPP