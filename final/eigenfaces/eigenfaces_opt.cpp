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

// Optimize me (sequential)
void outer(Matrix& A, const Vector& x) {
  for (size_t i = 0; i < A.num_rows(); ++i) {  
    double t = x(i);	  
    for (size_t j = 0; j < A.num_cols(); ++j) {
      A(i, j) += t*x(j);
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

const char* tag = "opt";
;

#include "main.hpp"
