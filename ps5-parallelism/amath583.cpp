//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "amath583.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <random>

// ----------------------------------------------------------------
//
// Vector arithmetic
//
// ----------------------------------------------------------------
void zeroize(Vector& x) {
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) = 0.0;
  }
}

void unitize(Vector& x) {
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) = 1.0;
  }
}

void randomize(Vector& x, double scale, double mean) {
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(mean - scale, mean + scale);
  static auto                            dice = std::bind(distribution, generator);

  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) = dice();
  }
}

double one_norm(const Vector& x) {
  double sum = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += std::abs(x(i));
  }
  return sum;
}

double two_norm(const Vector& x) {
  double sum = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += x(i) * x(i);
  }
  return std::sqrt(sum);
}

double two_norm_r(const Vector& x) {
  // Fix me
  double sum = 0.0;
  for (size_t i = x.num_rows() - 1; i > 0; --i) {
    sum += x(i) * x(i);
  }
  sum += x(0) * x(0);

  return std::sqrt(sum);
}

double two_norm_s(const Vector& x) {
  // Fix me
  Vector w(x);
  std::sort(&w(0), &w(0) + w.num_rows());
  double sum = 0.0;
  for (size_t i = 0; i < w.num_rows(); ++i) {
    sum += w(i) * w(i);
  }
  return std::sqrt(sum);
}

double inf_norm(const Vector& x);
double p_norm(const Vector& x);

Vector operator+(const Vector& x, const Vector& y);

Vector operator-(const Vector& x, const Vector& y) {
  Vector z(x.num_rows());
  for (size_t i = 0; i < z.num_rows(); ++i) {
    z(i) = x(i) - y(i);
  }
  return z;
}

Vector& operator*=(Vector& x, double alpha) {
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) *= alpha;
  }
  return x;
}

Vector& operator+=(Vector& x, double alpha) {
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) += alpha;
  }
  return x;
}

Vector& operator+=(Vector& x, const Vector& y) {
  assert(x.num_rows() == y.num_rows());
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) += y(i);
  }
  return x;
}
Vector& operator-=(const Vector& x, const Vector& y);

// ----------------------------------------------------------------
//
// Matrix arithmetic
//
// ----------------------------------------------------------------
void zeroize(Matrix& x);

void randomize(Matrix& A) {
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(2.0, 32.0);
  static auto                            dice = std::bind(distribution, generator);

  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      A(i, j) = dice();
    }
  }
}

double one_norm(const Matrix& x);
double two_norm(const Matrix& x);
double inf_norm(const Matrix& x);

double f_norm(const Matrix& A) {
  double sum = 0;
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      sum += A(i, j) * A(i, j);
    }
  }
  return std::sqrt(sum);
}

Matrix operator+(const Matrix& A, const Matrix& B) {
  assert(A.num_rows() == B.num_rows());
  assert(A.num_cols() == B.num_cols());
  Matrix C(A.num_rows(), A.num_cols());
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      C(i, j) = A(i, j) + B(i, j);
    }
  }
  return C;
}

Matrix operator-(const Matrix& A, const Matrix& B) {
  assert(A.num_rows() == B.num_rows());
  assert(A.num_cols() == B.num_cols());
  Matrix C(A.num_rows(), A.num_cols());
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      C(i, j) = A(i, j) - B(i, j);
    }
  }
  return C;
}

Matrix& operator*=(double alpha, const Matrix& x);
Matrix& operator+=(const Matrix& x, const Matrix& y);
Matrix& operator-=(const Matrix& x, const Matrix& y);

// ----------------------------------------------------------------
//
// Matrix-vector operations
//
// ----------------------------------------------------------------
Vector mult(const Matrix& A, const Vector& x) {
  Vector y(A.num_rows());
  mult(A, x, y);
  return y;
}

void mult(const Matrix& A, const Vector& x, Vector& y) {
  assert(y.num_rows() == A.num_rows());
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      y(i) += A(i, j) * x(j);
    }
  }
}

// ----------------------------------------------------------------
//
// Matrix-matrix operations
//
// ----------------------------------------------------------------
Matrix operator*(const Matrix& A, const Matrix& B);
void   matmat(const Matrix& A, const Vector& B, Matrix& C);

void copy(const Matrix& A, Matrix& B) {
  assert(B.num_rows() == A.num_rows());
  assert(B.num_cols() == A.num_cols());
  for (size_t i = 0; i < B.num_rows(); ++i) {
    for (size_t j = 0; j < B.num_cols(); ++j) {
      B(i, j) = A(i, j);
    }
  }
}

Matrix copy(const Matrix& A) {
  Matrix B(A.num_cols(), A.num_rows());
  copy(A, B);
  return B;
}

void transpose(const Matrix& A, Matrix& At) {
  assert(At.num_rows() == A.num_cols());
  assert(At.num_cols() == A.num_rows());
  for (size_t i = 0; i < At.num_rows(); ++i) {
    for (size_t j = 0; j < At.num_cols(); ++j) {
      At(i, j) = A(j, i);
    }
  }
}

Matrix transpose(const Matrix& A) {
  Matrix B(A.num_cols(), A.num_rows());
  transpose(A, B);
  return B;
}

void mult(const Matrix& A, const Matrix& B, Matrix& C) {
  assert(A.num_rows() == C.num_rows());
  assert(B.num_cols() == C.num_cols());
  assert(A.num_cols() == B.num_rows());

  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      for (size_t k = 0; k < A.num_cols(); ++k) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
}
