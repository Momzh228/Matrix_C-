#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_
#include <cmath>
#include <new>
#include <stdexcept>
class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix operator=(const S21Matrix& other);
  S21Matrix operator=(S21Matrix&& other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(const double num);
  double& operator()(int i, int j);
  double& operator()(int i, int j) const;
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

 private:
  int rows_, cols_;
  double** matrix_;
  void AllocateMemory();
  void MatrixAssigment(const S21Matrix& other);
  void SumOrSubMatrix(const S21Matrix& other, bool check);
  void MoveMatrix(S21Matrix&& other);
  void CopyMatrix(const S21Matrix& other);
  void MinorMatrix(const S21Matrix& other, int rows, int cols);
  void RemoveMatrix();
};

#endif