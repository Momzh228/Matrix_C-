#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix this_copy = *this;
  this_copy.SumMatrix(other);
  return this_copy;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix this_copy = *this;
  this_copy.SubMatrix(other);
  return this_copy;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix this_copy = *this;
  this_copy.MulMatrix(other);
  return this_copy;
}
S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix this_copy = *this;
  this_copy.MulNumber(num);
  return this_copy;
}
bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }
S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  RemoveMatrix();
  CopyMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator=(S21Matrix&& other) {
  RemoveMatrix();
  MoveMatrix(std::move(other));
  return *this;
}
void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }
void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }
void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }
void S21Matrix::operator*=(const double num) { MulNumber(num); }
double& S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0 || matrix_ == nullptr) {
    throw std::invalid_argument("Invalid matrix");
  }
  return matrix_[i][j];
}
double& S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0 || matrix_ == nullptr) {
    throw std::invalid_argument("Invalid matrix");
  }
  return matrix_[i][j];
}