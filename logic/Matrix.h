//
// Created by Joe Bekor on 2024. 01. 30..
//

#pragma once
#include <vector>
#include <chrono>
#include "Sand.hpp"
using T_Mtx = std::vector<std::vector<Sand>>;
class Matrix {
 public:
  explicit Matrix(int size);
  void mark(Coordinate coordinate);
  [[nodiscard]] bool marked(Coordinate coordinate) const;
  [[nodiscard]] const T_Mtx& getRepresentation() const;
  [[nodiscard]] int getSize() const;
  void update();
  [[nodiscard]] TimeStamp getTimeStamp(Coordinate coordinate) const;

 private:
  T_Mtx matrix;
  const int size;
  TimeStamp timeStamp;
  void propagateFall(int row, int column);
  Coordinate selectSlope(int row, int column) const;
  bool isSlopeAvailable(int row, int column) const;
  bool isLeftSlopeFree(int row, int column) const;
  bool isRightSlopeFree(int row, int column) const;
  void swapSands(Coordinate to, Coordinate from);
};
