
#ifndef MATRIX_MATRIX
#define MATRIX_MATRIX

#include <complex>
#include <iostream>
#include <vector>

namespace app {

template<typename T>
class matrix {
 public:
  matrix(const unsigned rows, const unsigned cols = 1) : rows_(rows), cols_(cols) {
    data_ = std::vector<T>(rows_ * cols_);
  }

  T at(const unsigned row, const unsigned col) const;

 private:
  unsigned rows_;
  unsigned cols_;
  std::vector<T> data_;
};

}
#endif // MATRIX_MATRIX