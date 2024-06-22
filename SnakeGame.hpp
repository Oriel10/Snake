#ifndef SNAKEGAME_HPP
#define SNAKEGAME_HPP

#include <unordered_map>
#include "Snake.hpp"
#include "Common.hpp"

class SnakeGame {
private:
  const char foodMark = '*';
  const int scoreMultiple = 10;
  bool gameOver = false;
  int boardDimension;
  double gameSpeed; // Game speed in seconds
  
  Snake snake;
  Position foodPosition;
  std::unordered_map<Position, isLocated, pair_hash> emptySpots;
  Position getPosition() const;
public:
  SnakeGame(int boardDimension, double gameSpeed);
  void setFoodPosition();
  bool isGameOver() const;
  void displayBoard() const;
  void getMoveInput();
  void moveSnake();
};

#endif // SNAKEGAME_HPP