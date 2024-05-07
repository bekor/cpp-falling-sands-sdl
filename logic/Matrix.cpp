//
// Created by Joe Bekor on 2024. 01. 30..
//

#include "Matrix.h"
#include "../util/Random.hpp"
Matrix::Matrix(int size) : size(size) {
  T_Mtx mtx(size);
  std::for_each(mtx.begin(), mtx.end(), [&size](std::vector<Sand> &row) { row = std::vector<Sand>(size); });
  matrix = mtx;
}

const T_Mtx &Matrix::getRepresentation() const {
  return matrix;
}

int Matrix::getSize() const {
  return size;
}

void Matrix::mark(Coordinate coordinate) {
  matrix.at(coordinate.x).at(coordinate.y).mark();
}

bool Matrix::marked(Coordinate coordinate) const {
  return matrix.at(coordinate.x).at(coordinate.y).isOccupied();
}

void Matrix::update() {
  for (int row = matrix.size() - 2; row >= 0; --row) { // fall is not propagated in the last row
    for (int column = 0; column < matrix.at(row).size(); ++column) {
      if (matrix.at(row).at(column).isOccupied()) {
        propagateFall(row, column);
      }
    }
  }
}

TimeStamp Matrix::getTimeStamp(Coordinate coordinate) const {
  return matrix.at(coordinate.x).at(coordinate.y).getTimeStamp();
}

void Matrix::propagateFall(int row, int column) {
  if (!matrix.at(row + 1).at(column).isOccupied()) {
    swapSands({row + 1, column}, {row, column});
  } else {
    if (isSlopeAvailable(row, column)) {
      auto slope = selectSlope(row, column);
      swapSands(slope, {row, column});
    }
  }
}

Coordinate Matrix::selectSlope(int row, int column) const {
  std::vector<Coordinate> possibleMoves;
  if (isLeftSlopeFree(row, column))
    possibleMoves.push_back({row + 1, column - 1});
  if (isRightSlopeFree(row, column))
    possibleMoves.push_back({row + 1, column + 1});
  if (possibleMoves.size() > 1) {
    int randomDirection = Random::between(0, 1);
    return possibleMoves.at(randomDirection);
  } else if (possibleMoves.size() == 1) {
    return possibleMoves.front();
  } else {
    return {row, column};
  }
}
bool Matrix::isSlopeAvailable(int row, int column) const {
  return (isLeftSlopeFree(row, column))
      || (isRightSlopeFree(row, column));
}
bool Matrix::isLeftSlopeFree(int row, int column) const {
  return column > 0 && !matrix.at(row + 1).at(column - 1).isOccupied();
}

bool Matrix::isRightSlopeFree(int row, int column) const {
  return column < matrix.size() - 1 && !matrix.at(row + 1).at(column + 1).isOccupied();
}
void Matrix::swapSands(Coordinate to, Coordinate from) {
  matrix.at(to.x).at(to.y).swap(matrix.at(from.x).at(from.y));
}
