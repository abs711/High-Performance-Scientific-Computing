//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#ifndef AMATH583_COOMATRIX_HPP
#define AMATH583_COOMATRIX_HPP

#include "Matrix.hpp"
#include "Vector.hpp"
#include <cassert>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

class COOMatrix {
private:
public:
  COOMatrix(size_t M, size_t N) : num_rows_(M), num_cols_(N) {}

  void push_back(size_t i, size_t j, double val) {
    assert(i < num_rows_ && i >= 0);
    assert(j < num_cols_ && j >= 0);

    row_indices_.push_back(i);
    col_indices_.push_back(j);
    storage_.push_back(val);
  }

  void clear() {
    row_indices_.clear();
    col_indices_.clear();
    storage_.clear();
  }

  void reserve(size_t n) {
    assert(n >= 0);

    row_indices_.reserve(n);
    col_indices_.reserve(n);
    storage_.reserve(n);
  }

  size_t num_rows() const { return num_rows_; }
  size_t num_cols() const { return num_cols_; }
  size_t num_nonzeros() const { return storage_.size(); }

  void stream_coordinates(std::ostream& output_file) const {
    for (size_t i = 0; i < num_nonzeros(); ++i) {
      output_file << row_indices_[i] << " ";
      output_file << col_indices_[i] << " ";
      output_file << storage_[i];
      output_file << std::endl;
    }
  }

  void matvec(const Vector& x, Vector& y) const {
    for (size_t k = 0; k < storage_.size(); ++k) {
      y(row_indices_[k]) += storage_[k] * x(col_indices_[k]);
    }
  }

  void t_matvec(const Vector& x, Vector& y) const {
    for (size_t k = 0; k < storage_.size(); ++k) {
      y(col_indices_[k]) += storage_[k] * x(row_indices_[k]);
    }
  }

  void matmat(const Matrix& B, Matrix& C) const { /* Write Me */
    for (size_t i = 0; i < storage_.size(); ++i) {
      double t  = storage_[i];
      size_t ii = row_indices_[i];
      size_t jj = col_indices_[i];
      for (size_t k = 0; k < B.num_cols(); ++k) {
        C(ii, k) += t * B(jj, k);
      }
    }
  }

private:
  size_t              num_rows_, num_cols_;
  std::vector<size_t> row_indices_, col_indices_;
  std::vector<double> storage_;
};

#endif    // AMATH583_COOMATRIX_HPP
