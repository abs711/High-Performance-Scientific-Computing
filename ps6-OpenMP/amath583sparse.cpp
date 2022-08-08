//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "Matrix.hpp"
#include "Vector.hpp"
#include <cassert>

#include "COOMatrix.hpp"
#include "CSRMatrix.hpp"

#include "AOSMatrix.hpp"
#include "CSCMatrix.hpp"

#include "amath583sparse.hpp"

// ----------------------------------------------------------------
//
// COOMatrix operations
//
// ----------------------------------------------------------------
void piscetize(COOMatrix& A, size_t xpoints, size_t ypoints) {
  assert(A.num_rows() == A.num_cols());
  assert(xpoints * ypoints == A.num_rows());

  A.clear();

  for (size_t j = 0; j < xpoints; j++) {
    for (size_t k = 0; k < ypoints; k++) {
      size_t jrow = j * ypoints + k;

      if (j != 0) {
        size_t jcol = (j - 1) * ypoints + k;
        A.push_back(jrow, jcol, -1.0);
      }
      if (k != 0) {
        size_t jcol = j * ypoints + (k - 1);
        A.push_back(jrow, jcol, -1.0);
      }

      A.push_back(jrow, jrow, 4.0);

      if (k != ypoints - 1) {
        size_t jcol = j * ypoints + (k + 1);
        A.push_back(jrow, jcol, -1.0);
      }
      if (j != xpoints - 1) {
        size_t jcol = (j + 1) * ypoints + k;
        A.push_back(jrow, jcol, -1.0);
      }
    }
  }
}

Vector mult(const COOMatrix& A, const Vector& x) {
  Vector y(A.num_rows());
  mult(A, x, y);
  return y;
}

Vector mult(const Vector& x, const COOMatrix& A) {
  Vector y(A.num_rows());
  mult(x, A, y);
  return y;
}

void mult(const COOMatrix& A, const Vector& x, Vector& y) { A.matvec(x, y); }
void mult(const Vector& x, const COOMatrix& A, Vector& y) { A.t_matvec(x, y); }

Matrix mult(const COOMatrix& A, const Matrix& B) {
  Matrix C(A.num_rows(), B.num_cols());
  A.matmat(B, C);
  return C;
}

void mult(const COOMatrix& A, const Matrix& B, Matrix& C) { A.matmat(B, C); }

// ----------------------------------------------------------------
//
// CSRMatrix operations
//
// ----------------------------------------------------------------
void piscetize(CSRMatrix& A, size_t xpoints, size_t ypoints) {
  assert(A.num_rows() == A.num_cols());
  assert(xpoints * ypoints == A.num_rows());

  A.clear();
  A.open_for_push_back();

  for (size_t j = 0; j < xpoints; j++) {
    for (size_t k = 0; k < ypoints; k++) {
      size_t jrow = j * ypoints + k;

      if (j != 0) {
        size_t jcol = (j - 1) * ypoints + k;
        A.push_back(jrow, jcol, -1.0);
      }
      if (k != 0) {
        size_t jcol = j * ypoints + (k - 1);
        A.push_back(jrow, jcol, -1.0);
      }

      A.push_back(jrow, jrow, 4.0);

      if (k != ypoints - 1) {
        size_t jcol = j * ypoints + (k + 1);
        A.push_back(jrow, jcol, -1.0);
      }
      if (j != xpoints - 1) {
        size_t jcol = (j + 1) * ypoints + k;
        A.push_back(jrow, jcol, -1.0);
      }
    }
  }
  A.close_for_push_back();
}

Vector mult(const CSRMatrix& A, const Vector& x) {
  Vector y(A.num_rows());
  A.matvec(x, y);
  return y;
}

Vector mult(const Vector& x, const CSRMatrix& A) {
  Vector y(A.num_rows());
  A.t_matvec(x, y);
  return y;
}

void mult(const CSRMatrix& A, const Vector& x, Vector& y) { A.matvec(x, y); }
void mult(const Vector& x, const CSRMatrix& A, Vector& y) { A.t_matvec(x, y); }

Matrix mult(const CSRMatrix& A, const Matrix& B) {
  Matrix C(A.num_rows(), B.num_cols());
  A.matmat(B, C);
  return C;
}

void mult(const CSRMatrix& A, const Matrix& B, Matrix& C) { A.matmat(B, C); }

// ----------------------------------------------------------------
//
// CSCMatrix operations
//
// ----------------------------------------------------------------
void piscetize(CSCMatrix& A, size_t xpoints, size_t ypoints) {
  assert(A.num_rows() == A.num_cols());
  assert(xpoints * ypoints == A.num_rows());

  A.clear();
  A.open_for_push_back();

  for (size_t j = 0; j < xpoints; j++) {
    for (size_t k = 0; k < ypoints; k++) {
      size_t jrow = j * ypoints + k;

      if (j != 0) {
        size_t jcol = (j - 1) * ypoints + k;
        A.push_back(jcol, jrow, -1.0);
      }
      if (k != 0) {
        size_t jcol = j * ypoints + (k - 1);
        A.push_back(jcol, jrow, -1.0);
      }

      A.push_back(jrow, jrow, 4.0);

      if (k != ypoints - 1) {
        size_t jcol = j * ypoints + (k + 1);
        A.push_back(jcol, jrow, -1.0);
      }
      if (j != xpoints - 1) {
        size_t jcol = (j + 1) * ypoints + k;
        A.push_back(jcol, jrow, -1.0);
      }
    }
  }
  A.close_for_push_back();
}

Vector mult(const CSCMatrix& A, const Vector& x) {
  Vector y(A.num_rows());
  A.matvec(x, y);
  return y;
}

Vector mult(const Vector& x, const CSCMatrix& A) {
  Vector y(A.num_rows());
  A.t_matvec(x, y);
  return y;
}

void mult(const CSCMatrix& A, const Vector& x, Vector& y) { A.matvec(x, y); }
void mult(const Vector& x, const CSCMatrix& A, Vector& y) { A.t_matvec(x, y); }

Matrix mult(const CSCMatrix& A, const Matrix& B) {
  Matrix C(A.num_rows(), B.num_cols());
  A.matmat(B, C);
  return C;
}

void mult(const CSCMatrix& A, const Matrix& B, Matrix& C) { A.matmat(B, C); }

// ----------------------------------------------------------------
//
// AOSMatrix operations
//
// ----------------------------------------------------------------
void piscetize(AOSMatrix& A, size_t xpoints, size_t ypoints) {
  assert(A.num_rows() == A.num_cols());
  assert(xpoints * ypoints == A.num_rows());

  A.clear();

  for (size_t j = 0; j < xpoints; j++) {
    for (size_t k = 0; k < ypoints; k++) {
      size_t jrow = j * ypoints + k;

      if (j != 0) {
        size_t jcol = (j - 1) * ypoints + k;
        A.push_back(jrow, jcol, -1.0);
      }
      if (k != 0) {
        size_t jcol = j * ypoints + (k - 1);
        A.push_back(jrow, jcol, -1.0);
      }

      A.push_back(jrow, jrow, 4.0);

      if (k != ypoints - 1) {
        size_t jcol = j * ypoints + (k + 1);
        A.push_back(jrow, jcol, -1.0);
      }
      if (j != xpoints - 1) {
        size_t jcol = (j + 1) * ypoints + k;
        A.push_back(jrow, jcol, -1.0);
      }
    }
  }
}

Vector mult(const AOSMatrix& A, const Vector& x) {
  Vector y(A.num_rows());
  A.matvec(x, y);
  return y;
}

Vector mult(const Vector& x, const AOSMatrix& A) {
  Vector y(A.num_rows());
  A.t_matvec(x, y);
  return y;
}

void mult(const AOSMatrix& A, const Vector& x, Vector& y) { A.matvec(x, y); }

void mult(const Vector& x, const AOSMatrix& A, Vector& y) { A.t_matvec(x, y); }

Matrix mult(const AOSMatrix& A, const Matrix& B) {
  Matrix C(A.num_rows(), B.num_cols());
  A.matmat(B, C);
  return C;
}

void mult(const AOSMatrix& A, const Matrix& B, Matrix& C) { A.matmat(B, C); }
