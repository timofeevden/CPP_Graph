#include "s21_matrix.h"

namespace s21 {

//  конструктор по-умолчанию
Matrix::Matrix()
    : size_(0),
      matrix_(nullptr){

      };

//  конструктор по заданному размеру
Matrix::Matrix(int size) : size_(size) {
  if (size_ <= 0) {
    throw std::invalid_argument(
        "Matrix rows and columns must be greater than 0");
  }
  CreateMatrixArray(size);
}

//  конструктор по заданному размеру
Matrix::Matrix(int size, int value) : size_(size) {
  if (size_ <= 0) {
    throw std::invalid_argument(
        "Matrix rows and columns must be greater than 0");
  }
  CreateMatrixArray(size);
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      matrix_[i][j] = value;
    }
  }
}

//   конструктор копирования
Matrix::Matrix(const Matrix& other) { CopyMatrix(other); }

//   конструктор перемещения
Matrix::Matrix(Matrix&& other) noexcept
    : size_(other.size_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.size_ = 0;
}

//  деструктор
Matrix::~Matrix() { Clear(); }

void Matrix::CreateMatrixArray(int size) {
  matrix_ = new double*[size];
  for (int i = 0; i < size; i++) {
    // [cols_] c () чтобы инициализировать значения нулями
    matrix_[i] = new double[size]();
  }
  size_ = size;
}

void Matrix::CopyMatrix(const Matrix& other) {
  size_ = other.size_;
  matrix_ = new double*[size_];

  for (int i = 0; i < size_; i++) {
    matrix_[i] = new double[size_];
    for (int j = 0; j < size_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void Matrix::Clear() {
  if (size_ && matrix_) {
    for (int i = 0; i < size_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
    size_ = 0;
  }
}

//  значения размеров матрицы
int Matrix::GetSize() const noexcept { return size_; }

//  изменение размеров матрицы

void Matrix::Resize(int new_size) {
  if (new_size <= 0) {
    throw std::invalid_argument(
        "Incorrect index in ResizeMatrix(), index must be greater than 0");
  } else if (new_size != size_) {
    double** tmp_matrix = new double*[new_size];
    double need_cols = new_size < size_ ? new_size : size_;

    for (int i = 0; i < new_size; i++) {
      //  сразу зануляем с помощью ()
      tmp_matrix[i] = new double[new_size]();
      //  копируем нужное кол-во столбцов и строк:
      if (i < size_) {
        for (int j = 0; j < need_cols; j++) {
          tmp_matrix[i][j] = matrix_[i][j];
        }
      }
    }
    //  освобождаем память от старых значений
    Clear();
    //  и перемещаем значения
    matrix_ = tmp_matrix;
    size_ = new_size;
    tmp_matrix = nullptr;
  }
}

//  равенство матриц
bool Matrix::EqMatrix(const Matrix& other) const {
  bool result = true;

  if (size_ == other.size_) {
    for (int i = 0; i < size_ && result == true; i++) {
      for (int j = 0; j < size_; j++) {
        double delta = matrix_[i][j] - other.matrix_[i][j];
        //  делем delta положительным
        delta = delta < 0 ? -delta : delta;
        if (delta >= 1e-7) {
          result = false;
          break;
        }
      }
    }
  } else {
    result = false;
  }

  return result;
}

//  Заполнение значением всех ячеек
void Matrix::Fill(double value) {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      matrix_[i][j] = value;
    }
  }
}

//  перегрузка операторов:
double& Matrix::operator()(int i, int j) {
  if (i >= size_ || j >= size_ || i < 0 || j < 0) {
    std::cout << "i j = " << i << " " << j << "\n";
    throw std::out_of_range(
        "Incorrect index in operator() in Matrix, index is out of range");
  }
  return matrix_[i][j];
}

const double& Matrix::operator()(int i, int j) const {
  if (i >= size_ || j >= size_ || i < 0 || j < 0) {
    std::cout << "i j = " << i << " " << j << "\n";
    throw std::out_of_range(
        "Incorrect index in operator() in Matrix, index is out of range");
  }
  return matrix_[i][j];
}

//  приравнивание копированием
Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    Clear();
    CopyMatrix(other);
  }

  return *this;
}

//  приравнивание перемещением
Matrix& Matrix::operator=(Matrix&& other) {
  if (this != &other) {
    Clear();
    size_ = other.size_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
    other.size_ = 0;
  }

  return *this;
}

bool Matrix::operator==(const Matrix& other) const { return EqMatrix(other); }

bool Matrix::operator!=(const Matrix& other) const { return !EqMatrix(other); }

void Matrix::PrintMatrix() {
  std::cout << size_ << "\n";

  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << "\n";
  }
}

}  // namespace s21