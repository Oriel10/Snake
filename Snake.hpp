#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>
#include <deque>
#include <unordered_map>
#include "Common.hpp"

class Snake {
private:
  std::unordered_map<Direction, std::pair<int,int>> directionsMap{
    {Direction::UP, {-1, 0}},
    {Direction::DOWN, {1, 0}},
    {Direction::LEFT, {0, -1}},
    {Direction::RIGHT, {0, 1}}
  };

  const char snakeBodyMark = 'O';
  const char snakeHeadMark = '0';
  bool eatLastMove = false;
  Direction currDirection = Direction::UP;
  int boardDimension;
  Position initialPosition;
  std::unordered_map<Position, isLocated, pair_hash> positionsSet;
  std::deque<Position> snakeBody;
  Position foodPosition;

public:
  Snake(int boardDimension);

  Position getHead() const;
  Position getTail() const;
  void deleteTail();
  void addHead(Position newHeadPosition);
  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();
  void move(Direction d);
  void gameLost() const;
  bool isLegitPosition(Position p);
  bool isSnakeAt(int x, int y) const;
  bool isSnakeAt(Position p) const;
  char getSnakeMark(Position p) const;
  void setFoodPosition(Position p);
  bool isLegitDirection(Direction newDirection, Direction currDirection) const;
  bool didEatLastMove() const;
};

#endif // SNAKE_HPP