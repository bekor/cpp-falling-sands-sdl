//
// Created by Joe Bekor on 2024. 01. 30..
//

#pragma once
#include <vector>

using T_Mtx = std::vector<std::vector<bool>>;
class Matrix {
 public:
  explicit Matrix(int size);
  void mark(int x, int y);
  const T_Mtx& getRepresentation() const;
  int getSize() const;

 private:
  T_Mtx matrix;
  const int size;
};
