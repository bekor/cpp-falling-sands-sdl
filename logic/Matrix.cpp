//
// Created by Joe Bekor on 2024. 01. 30..
//

#include "Matrix.h"
Matrix::Matrix(int size) : size(size){
  T_Mtx mtx(size);
  std::for_each(mtx.begin(), mtx.end(),[&size](std::vector<bool>& row){row = std::vector<bool>(size);});
  matrix = mtx;
}
const T_Mtx &Matrix::getRepresentation() const {
  return matrix;
}

int Matrix::getSize() const{
  return size;
}
