#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>
#include <deque>
#include <unordered_map>

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
  using Position = std::pair<int, int>;
  using Direction = std::pair<int, int>;
  using isLocated = bool;

  const char snakeBodyMark = '*';
  int boardDimension;
  Position initialPosition;
  std::unordered_map<Position, isLocated, pair_hash> positionsSet;
  std::deque<Position> snakeBody;

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
  void Move(Direction d);
  void gameLost() const;
  bool checkLegitPosition(Position headPosition);
  bool isSnakeAt(int x, int y) const;
  char getBodyMark() const;
};

#endif // SNAKE_HPP