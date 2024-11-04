#ifndef SRC_CONTAINERS_S21_MATRIX_H_
#define SRC_CONTAINERS_S21_MATRIX_H_

#include <iostream>

namespace s21 {

class Matrix {
 public:
  Matrix();
  Matrix(int size);
  Matrix(int size, int value);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other) noexcept;
  ~Matrix();
  int GetSize() const noexcept;
  void Resize(int new_size);
  void Clear();
  bool EqMatrix(const Matrix& other) const;
  void Fill(double value);
  double& At(int row, int col);
  const double& At(int row, int col) const;
  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other);
  double& operator()(int i, int j);
  const double& operator()(int row, int col) const;
  bool operator==(const Matrix& other) const;
  bool operator!=(const Matrix& other) const;
  void PrintMatrix();

 private:
  int size_;
  double** matrix_;

 private:
  void CreateMatrixArray(int size);
  void CopyMatrix(const Matrix& other);
};

}  // namespace s21

#endif  //  SRC_CONTAINERS_S21_MATRIX_H_