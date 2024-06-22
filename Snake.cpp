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
  return move(Direction::UP);
}

bool Snake::moveDown() {
  return move(Direction::DOWN);
}

bool Snake::moveRight() {
  return move(Direction::RIGHT);
}

bool Snake::moveLeft() {
  return move(Direction::LEFT);
}

bool Snake::move(Direction d) {
  if(!isLegitDirection(d, currDirection)) {
    // Ignore move if the direction pressed is illegal
    return true;
  }

  pair<int,int> newHeadPosition = {getHead().first + directionsMap[d].first, getHead().second + directionsMap[d].second};
  if(!isLegitPosition(newHeadPosition)) {
    return false;
  }

  currDirection = d;
  // Snake ate the food
  if(newHeadPosition == foodPosition) {
    addHead(newHeadPosition);
    eatLastMove = true;
    return true;
  }
  // Snake did not eat the food
  else {
    deleteTail();
    addHead(newHeadPosition);
    eatLastMove = false;
    return true;
  }
}

bool Snake::isLegitPosition(Position newHeadPosition) {
  int rowPosition = newHeadPosition.first;
  int colPosition = newHeadPosition.second;
  if(rowPosition < 0 || boardDimension <= rowPosition) {
    return false;
  }
  else if(colPosition < 0 || boardDimension <= colPosition) {
    return false;
  }
  // Snake collide with itself, except the tail will be deleted
  else if(positionsSet.find(newHeadPosition) != positionsSet.end()
          && getTail() != newHeadPosition) {
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

char Snake::getSnakeMark(Position bodyPos) const {
  return bodyPos == getHead() ? snakeHeadMark : snakeBodyMark;
}

void Snake::setFoodPosition(Position position) {
  foodPosition = position;
}

bool Snake::isLegitDirection(Direction newDirection, Direction currDirection) const {
  if(currDirection == Direction::UP)
    return newDirection != Direction::DOWN;
  else if(currDirection == Direction::DOWN)
    return newDirection != Direction::UP;
  else if(currDirection == Direction::LEFT)
    return newDirection != Direction::RIGHT;
  else if(currDirection == Direction::RIGHT)
    return newDirection != Direction::LEFT;
  else{
    assert(false && "Unrecognized direction");
    return false;
  }
}

bool Snake::didEatLastMove() const {
  return eatLastMove;
}

int Snake::getLength() const{
  return snakeBody.size();
}