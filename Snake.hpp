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
  Direction currDirection = Direction::STOP;
  int boardDimension;
  std::unordered_map<Position, isLocated, pair_hash> positionsSet;
  std::deque<Position> snakeBody;
  Position foodPosition;

public:
  Snake(int boardDimension);

  Position getHead() const;
  Position getTail() const;
  void deleteTail();
  void addHead(Position newHeadPosition);
  
  /**
  * @brief move<Direction>
  * 
  * Moves the snake according to Direction.
  * 
  * 
  * @return true if movement is legal and false otherwise.
  */
  bool moveUp();
  bool moveDown();
  bool moveRight();
  bool moveLeft();

  /**
  * @brief implements move<direction>
  * @return true if movement is legal and false otherwise.
  */
  bool move(Direction d);

  /**
  * @brief Check if position p is a legitimate position for a snake head.
  * @param p Position being checked.
  * @return true if position is legit and false otherwise.
  */
  bool isLegitPosition(Position p);

  /**
  * @brief Check if any snake part is at position (x,y).
  * @param x Row coordinate.
  * @param y Column coordinate.
  * @return true if snake is positioned in (x,y) and false otherwise.
  */
  bool isSnakeAt(int x, int y) const;

  /**
  * @brief Check if any snake part is at position p.
  * @param p Position to check.
  * @return true if snake is positioned in p and false otherwise.
  */
  bool isSnakeAt(Position p) const;

  /**
  * @brief This function is used to return the head/body mark of the snake.
  * @param p Position of the snake.
  * @return The character that represents the snake at position p.
  */
  char getSnakeMark(Position p) const;


  /**
  * @brief Sets foodPosition with p.
  */
  void setFoodPosition(Position p);

  /**
  * @brief Checks if a new direction is legitimate according to the current direction.
  * @param newDirection New direction to check.
  * @param currDirection Current direction the snake is heading.
  * @return True if the new direction is legitimate and false otherwise.
  */
  bool isLegitDirection(Direction newDirection, Direction currDirection) const;

  /**
  * @return eatLastMove, which says whether the snake ate the food in its last movement.
  */
  bool didEatLastMove() const;

  /**
  * @return The length of the snake whole body.
  */
  int getLength() const;

  friend class SnakeGame;
};

#endif // SNAKE_HPP