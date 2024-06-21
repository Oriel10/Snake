#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>
#include <deque>
#include <unordered_map>
#include "Common.hpp"

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);
    return h1 ^ (h2 << 1); // Combine the hash values
  }
};

class Snake {
private:
  std::unordered_map<Direction, std::pair<int,int>> directionsMap{
    {Direction::UP, {-1, 0}},
    {Direction::DOWN, {1, 0}},
    {Direction::LEFT, {0, -1}},
    {Direction::RIGHT, {0, 1}}
  };

  using isLocated = bool;

  const char snakeBodyMark = 'O';
  const char snakeHeadMark = '0';
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
  bool moveUp();
  bool moveDown();
  bool moveRight();
  bool moveLeft();
  bool move(Direction d);
  void gameLost() const;
  bool isLegitPosition(Position p);
  bool isSnakeAt(int x, int y) const;
  bool isSnakeAt(Position p) const;
  char getSnakeMark(Position p) const;
  void setFoodPosition(Position p);
  bool isLegitDirection(Direction newDirection, Direction currDirection) const;
};

#endif // SNAKE_HPP