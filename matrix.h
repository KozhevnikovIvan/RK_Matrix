#include <iostream>
#include <fstream>
#include <cstdlib>
#include <initializer_list>

using namespace std;

class Matrix {
 public:
  Matrix() {
    matrix = nullptr;
    a = 0;
    b = 0;
  }
  Matrix(std::initializer_list<int> list) {
    matrix = new int*[a];
    for (int i = 0; i < a; i++) matrix[i] = new int[b];
    for (int i = 0; i < a; i++) {
      for (int j = 0; j < b; j++) {
        matrix[i][j] = rand() % 10;
      }
    }
  }

  Matrix(const Matrix& ptr) {
    a = ptr.a;
    b = ptr.b;
    matrix = new int*[ptr.a];
    for (int i = 0; i < ptr.a; i++) {
      matrix[i] = new int[ptr.b];
    }

    for (int i = 0; i < ptr.a; i++) {
      for (int j = 0; j < ptr.b; j++) {
        matrix[i][j] = ptr.matrix[i][j];
      }
    }
  }

  auto swap_(Matrix& ptr) -> void {
    swap(matrix, ptr.matrix);
    swap(a, ptr.a);
    swap(b, ptr.b);
  }
  auto operator=(const Matrix_t& q) -> Matrix {
    if (matrix != nullptr) {
      for (int i = 0; i < a; i++) delete[] matrix[i];
      delete[] matrix;
      return *this;
    }
    a = q.a;
    b = q.b;
    matrix = new int*[a];
    for (int i = 0; i < a; i++) matrix[i] = new int[b];
    for (int i = 0; i < a; i++) {
      for (int j = 0; j < b; j++) {
        matrix[i][j] = q.matrix[i][j];
      }
    }
    return *this;
  }

  auto rows() -> size_t { return a; }

  auto columns() -> size_t { return b; }

  auto empty() -> bool {
    if (matrix == nullptr)
      return true;
    else
      return false;
  }

  auto operator-(const Matrix& ptr) -> Matrix & {
    if (a == ptr.a && b == ptr.b) {
      for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
          matrix[i][j] = matrix[i][j] - ptr.matrix[i][j];
        }
      }
      return *this;
    }
  }

  auto operator+(const Matrix& ptr) -> Matrix & {
    if (a == ptr.a && b == ptr.b) {
      for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
          matrix[i][j] = matrix[i][j] + ptr.matrix[i][j];
        }
      }
      return *this;
    }
  }
  auto operator[](size_t index) -> int * { return matrix[index]; }
  bool operator==(const Matrix& ptr) {
    if (a == ptr.a && b == ptr.b) {
      for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
          if (matrix[i][j] != ptr.matrix[i][j]) return false;
        }
      }
      return true;
    }
    return false;
  }

  friend auto operator<<(ostream& os, Matrix& ptr) -> ostream & {
    os << ptr.a << " " << ptr.b << endl;
    for (int i = 0; i < ptr.a; i++) {
      for (int j = 0; j < ptr.b; j++) {
        os << ptr.matrix[i][j] << "  ";
      }
      os << endl;
    }
    return os;
  }
  friend auto operator>>(istream& is, Matrix& ptr) -> istream & {
    if (is) {
      is >> ptr.a >> ptr.b;
      ptr.matrix = new int*[ptr.a];
      for (int i = 0; i < ptr.a; i++) ptr.matrix[i] = new int[ptr.b];
      for (int i = 0; i < ptr.a; i++) {
        for (int j = 0; j < ptr.b; j++) {
          is >> ptr.matrix[i][j];
        }
      }
      return is;
    }
  }
  ~Matrix() {
    for (int i = 0; i < a; i++) delete[] matrix[i];
    delete[] matrix;
  }

 private:
  int** matrix;
  size_t a;
  size_t b;
};
