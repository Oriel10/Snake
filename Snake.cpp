#include <assert.h>
#include "Snake.hpp"

using namespace std;

static bool isLegitDirection(Direction newDirection, Direction currDirection) {
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
  Direction up = Direction::UP;
  return move(up);
}

bool Snake::moveDown() {
  Direction down = Direction::DOWN;
  return move(down);
}

bool Snake::moveRight() {
  Direction right = Direction::RIGHT;
  return move(right);
}

bool Snake::moveLeft() {
  Direction left = Direction::LEFT;
  return move(left);
}

bool Snake::move(Direction d) {
  if(!isLegitDirection(d, currDirection)) {
    // Ignore move if the direction pressed is illegal
    return false;
  }

  pair<int,int> newHeadPosition = {getHead().first + directionsMap[d].first, getHead().second + directionsMap[d].second};
  if(!isLegitPosition(newHeadPosition)) {
    gameLost();
  }

  currDirection = d;
  // Snake ate the food
  if(newHeadPosition == foodPosition) {
    addHead(newHeadPosition);
    return true;
  }
  // Snake did not eat the food
  else {
    deleteTail();
    addHead(newHeadPosition);
    return false;
  }
}

void Snake::gameLost() const {
  cout << "You lost!" << endl;
  cout << "Final Score: " << snakeBody.size() << endl;
  exit(0);
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