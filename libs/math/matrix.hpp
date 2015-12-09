#ifndef MATRIX_T
#define MATRIX_T

template<typename T>
struct matrix_t {
  T a[MaxMS][MaxMS];
  int r, c;
  matrix_t() : r(0), c(0) {}
  matrix_t(int r, int c) : r(r), c(c) {
    for (int i = 0; i < r; i++) std::fill(a[i], a[i] + c, 0);
  }
  matrix_t operator*(const matrix_t& other) const {
    matrix_t res(r, other.c);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < other.c; j++) {
        for (int k = 0; k < c; k++) {
          res.a[i][j] += a[i][k] * other.a[k][j];
        }
      }
    }
    return res;
  }
};

#endif
