#include "Snake.h"
#include <assert.h>

using namespace std;

Snake::Snake(int boardDimension) : boardDimension(boardDimension) {
  Position initialPosition = {boardDimension/2, boardDimension/2};
  positionsSet[initialPosition] = true;
  snakeBody.push_front(initialPosition);
}

Snake::Position Snake::getHead() const {
  return snakeBody.front();
}

Snake::Position Snake::getTail() const {
  return snakeBody.back();
}

void Snake::deleteTail() {
  positionsSet.erase(getTail());
  snakeBody.pop_back();
}

void Snake::addHead(Position newHeadPosition) {
  snakeBody.push_front(newHeadPosition);
  positionsSet[newHeadPosition] = true;
}

void Snake::moveUp() {
  Direction up{-1,0};
  Move(up);
}

void Snake::moveDown() {
  Direction down{1,0};
  Move(down);
}

void Snake::moveRight() {
  Direction right{0,1};
  Move(right);
}

void Snake::moveLeft() {
  Direction left{0,-1};
  Move(left);
}

void Snake::Move(Direction d) {
  assert(d.first == 0 || d.second == 0);
  assert(d.first != 0 || d.second != 0);

  pair<int,int> newHeadPosition = {getHead().first + d.first, getHead().second + d.second};
  if(!checkLegitPosition(newHeadPosition)) {
    gameLost();
  }
  addHead(newHeadPosition);
  deleteTail();
}

void Snake::gameLost() const {
  cout << "You lost!" << endl;
  cout << "Final Score: " << snakeBody.size() << endl;
  exit(0);
}

bool Snake::checkLegitPosition(Position headPosition) {
  int rowPosition = headPosition.first;
  int colPosition = headPosition.second;
  if(rowPosition < 0 || boardDimension <= rowPosition) {
    return false;
  }
  else if(colPosition < 0 || boardDimension <= colPosition) {
    return false;
  }
  else if(positionsSet.find({rowPosition, colPosition}) != positionsSet.end()) {
    return false;
  }
  return true;
}

bool Snake::isSnakeAt(int x, int y) const {
  return positionsSet.find({x, y}) != positionsSet.end();
}

char Snake::getBodyMark() const {
  return snakeBodyMark;
}