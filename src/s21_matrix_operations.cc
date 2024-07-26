#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool check_eq = true;
  if (rows_ != other.rows_ || cols_ != other.cols_ || matrix_ == nullptr ||
      other.matrix_ == nullptr)
    check_eq = false;
  for (int i = 0; i < rows_ && check_eq; i++) {
    for (int j = 0; j < cols_ && check_eq; j++) {
      if (fabs(other.matrix_[i][j] - matrix_[i][j]) >= 1e-8) {
        check_eq = false;
      }
    }
  }
  return check_eq;
}
void S21Matrix::SumMatrix(const S21Matrix& other) {
  this->SumOrSubMatrix(other, 0);
}
void S21Matrix::SubMatrix(const S21Matrix& other) {
  this->SumOrSubMatrix(other, 1);
}
void S21Matrix::MulNumber(const double num) {
  if (matrix_ == nullptr) {
    throw std::invalid_argument("Invalid matrix");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_ || matrix_ == nullptr) {
    throw std::invalid_argument("Invalid matrix");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int g = 0; g < other.rows_; g++) {
        res.matrix_[i][j] += matrix_[i][g] * other.matrix_[g][j];
      }
    }
  }
  *this = res;
}
S21Matrix S21Matrix::Transpose() {
  if (matrix_ == nullptr) {
    throw std::invalid_argument("Invalid matrix");
  }
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_ || matrix_ == nullptr) {
    throw std::invalid_argument("Invalid matrix");
  }
  S21Matrix result_m(rows_, cols_);
  if (rows_ == 1) {
    result_m.matrix_[0][0] = matrix_[0][0];
  } else {
    S21Matrix M(rows_ - 1, cols_ - 1);
    double d;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        M.MinorMatrix(*this, i, j);
        d = M.Determinant();
        result_m.matrix_[i][j] = d * pow(-1, i + j);
      }
    }
  }
  return result_m;
}
double S21Matrix::Determinant() {
  if (rows_ != cols_ || matrix_ == nullptr) {
    throw std::invalid_argument("Invalid matrix");
  }
  double result = 0;
  if (rows_ == 1)
    result = matrix_[0][0];
  else if (rows_ == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else if (rows_ > 2) {
    S21Matrix M(rows_ - 1, cols_ - 1);
    for (int i = 0; i < cols_; ++i) {
      M.MinorMatrix(*this, 0, i);
      double temp = M.Determinant();
      result += std::pow((-1.0), i) * temp * matrix_[0][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (cols_ != rows_ || matrix_ == nullptr) {
    throw std::invalid_argument("Invalid matrix");
  }
  double d;
  d = Determinant();
  if (d == 0) throw std::invalid_argument("Zero determinant");
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    S21Matrix G(CalcComplements());
    S21Matrix G_trans(G.Transpose());
    result = G_trans;
    result.MulNumber(1.0 / d);
  }
  return result;
}
