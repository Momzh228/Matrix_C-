#include "s21_matrix_oop.h"
S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}
S21Matrix::S21Matrix(int rows, int cols) {
  if ((rows && cols < 1) || (rows < 1 && cols)) {
    throw std::invalid_argument("Invalid matrix");
  }
  rows_ = rows;
  cols_ = cols;
  AllocateMemory();
}
S21Matrix::S21Matrix(const S21Matrix& other) { CopyMatrix(other); }
S21Matrix::S21Matrix(S21Matrix&& other) { MoveMatrix(std::move(other)); }
S21Matrix::~S21Matrix() { RemoveMatrix(); }
int S21Matrix::GetCols() const { return cols_; }
int S21Matrix::GetRows() const { return rows_; }
void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::invalid_argument("Invalid rows");
  }
  S21Matrix temp(rows, cols_);
  if (rows_ > rows) {
    for (int i = 0; i < rows; ++i) {
      std::copy(matrix_[i], matrix_[i] + cols_, temp.matrix_[i]);
    }
  } else if (rows > rows_) {
    for (int i = 0; i < rows_; ++i) {
      std::copy(matrix_[i], matrix_[i] + cols_, temp.matrix_[i]);
    }
  }
  *this = temp;
}
void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::invalid_argument("Invalid cols");
  }
  S21Matrix temp(rows_, cols);
  if (cols_ > cols) {
    for (int i = 0; i < rows_; ++i) {
      std::copy(matrix_[i], matrix_[i] + cols, temp.matrix_[i]);
    }
  } else if (cols > cols_) {
    for (int i = 0; i < rows_; ++i) {
      std::copy(matrix_[i], matrix_[i] + cols_, temp.matrix_[i]);
    }
  }
  *this = temp;
}
