#include <assert.h>
#include "Snake.hpp"

using namespace std;

Snake::Snake(int boardDimension) : boardDimension(boardDimension) {
  Position initialPosition = {boardDimension/2, boardDimension/2};
  positionsSet[initialPosition] = true;
  snakeBody.push_front(initialPosition);
}

Position Snake::getHead() const {
  return snakeBody.front();
}

Position Snake::getTail() const {
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

bool Snake::moveUp() {
  Direction up{-1,0};
  return move(up);
}

bool Snake::moveDown() {
  Direction down{1,0};
  return move(down);
}

bool Snake::moveRight() {
  Direction right{0,1};
  return move(right);
}

bool Snake::moveLeft() {
  Direction left{0,-1};
  return move(left);
}

bool Snake::move(Direction d) {
  assert(d.first == 0 || d.second == 0);
  assert(d.first != 0 || d.second != 0);

  pair<int,int> newHeadPosition = {getHead().first + d.first, getHead().second + d.second};
  if(!checkLegitPosition(newHeadPosition)) {
    gameLost();
  }
  // Snake at the food
  if(newHeadPosition == foodPosition) {
    addHead(newHeadPosition);
    return true;
  }
  // Snake did not eat the food
  else {
    addHead(newHeadPosition);
    deleteTail();
    return false;
  }
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

bool Snake::isSnakeAt(Position pos) const {
  return positionsSet.find(pos) != positionsSet.end();
}

char Snake::getBodyMark() const {
  return snakeBodyMark;
}

void Snake::setFoodPosition(Position position) {
  foodPosition = position;
}