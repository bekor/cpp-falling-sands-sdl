//
// Created by Joe Bekor on 2024. 01. 30..
//

#pragma once
#include <vector>
#include "Sand.h"

using T_Mtx = std::vector<std::vector<Sand>>;
class Matrix {
 public:
  explicit Matrix(int size);
  void mark(Coordinate coordinate);
  bool marked(Coordinate coordinate) const;
  [[nodiscard]] const T_Mtx& getRepresentation() const;
  [[nodiscard]] int getSize() const;
  void update();

 private:
  T_Mtx matrix;
  const int size;
  void propagateFall(int row, int column);
  Coordinate selectSlope(int row, int column) const;
  bool isSlopeAvailable(int row, int column) const;
  bool isLeftSlopeFree(int row, int column) const;
  bool isRightSlopeFree(int row, int column) const;
};
