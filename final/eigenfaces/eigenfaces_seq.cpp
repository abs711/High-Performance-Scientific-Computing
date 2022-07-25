//
// This file is part of the course materials for AMATH 483/583 at the University of Washington
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "amath583.hpp"

// Basic (original) outer
void outer(Matrix& A, const Vector& x) {
  for (size_t j = 0; j < A.num_cols(); ++j) {
    for (size_t i = 0; i < A.num_rows(); ++i) {
      A(i, j) += x(i) * x(j);
    }
  }
}

auto gen_covariance(const std::vector<Vector>& z) {
  size_t sz = z[0].num_rows();
  Matrix C(sz, sz);

  for (size_t k = 0; k < z.size(); ++k) {
    outer(C, z[k]);
  }

  // Normalize
  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      C(i,j) = C(i,j) / z.size();
    }
  }

  return C;
}

const char* tag = "seq";

#include "main.hpp"
