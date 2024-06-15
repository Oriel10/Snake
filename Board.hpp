#ifndef BOARD_HPP
#define BOARD_HPP

#include "Snake.hpp"
#include "Common.hpp"

class Board {
private:
  const char foodMark = '*';
  int boardDimension;
public:
  Board(int boardDimension) : boardDimension(boardDimension) {}
};

#endif // BOARD_HPP