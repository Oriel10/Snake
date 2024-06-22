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

  /**
  * @return A random position on the board.
  */
  Position getPosition() const;
public:
  SnakeGame(int boardDimension, double gameSpeed);
  
  /**
  * @brief Set food on a clear board position.
  */
  void setFoodPosition();
  
  bool isGameOver() const;

  /**
  * @brief  Displays the board with the snake and food.
  */
  void displayBoard() const;

  /**
  * @brief Gets a move request from the user, and changes the direction of the snake accordingly.
  */
  void getMoveInput();

  /**
  * @brief Moves the snake according to the user's last movement request.
  */
  void moveSnake();
};

#endif // SNAKEGAME_HPP