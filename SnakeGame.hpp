#ifndef SNAKEGAME_HPP
#define SNAKEGAME_HPP

#include <unordered_map>
#include "Snake.hpp"
#include "Common.hpp"

class SnakeGame {
private:
  const char foodMark = '*';
  
  int boardDimension;
  Snake snake;
  Position foodPosition;
  std::unordered_map<Position, isLocated, pair_hash> emptySpots;
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