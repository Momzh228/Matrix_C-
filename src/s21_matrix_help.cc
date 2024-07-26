#include "s21_matrix_oop.h"

void S21Matrix::AllocateMemory() {
  matrix_ = new double*[rows_];
  for (int t = 0; t < rows_; ++t) {
    matrix_[t] = nullptr;
  }
  try {
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = 0;
      }
    }
  } catch (const std::bad_alloc& e) {
    RemoveMatrix();
    throw e;
  }
}
void S21Matrix::MatrixAssigment(const S21Matrix& other) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
void S21Matrix::SumOrSubMatrix(const S21Matrix& other, bool check) {
  if (rows_ != other.rows_ || cols_ != other.cols_ || matrix_ == nullptr ||
      other.matrix_ == nullptr) {
    throw std::invalid_argument("Invalid matrix");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (!check)
        matrix_[i][j] += other.matrix_[i][j];
      else
        matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}
void S21Matrix::MinorMatrix(const S21Matrix& other, int rows, int cols) {
  int rows_m = 0;
  int cols_m = 0;
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      if (i != rows && j != cols) {
        matrix_[rows_m][cols_m] = other.matrix_[i][j];
        cols_m++;
        if (cols_m == other.cols_ - 1) {
          rows_m++;
          cols_m = 0;
        }
      }
    }
  }
}

void S21Matrix::MoveMatrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}
void S21Matrix::CopyMatrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMemory();
  MatrixAssigment(other);
}
void S21Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}