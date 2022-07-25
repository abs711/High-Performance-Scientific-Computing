//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_PAGERANK_HPP
#define AMATH583_PAGERANK_HPP

#include "COOMatrix.hpp"
#include "CSCMatrix.hpp"
#include "CSRMatrix.hpp"

#include "Timer.hpp"
#include "Vector.hpp"
#include "amath583.hpp"
#include "amath583IO.hpp"
#include "amath583sparse.hpp"
#include <cassert>
#include <cstddef>
#include <functional>
#include <random>
#include <string>
#include <vector>

template <typename Matrix>
Vector pagerank(const Matrix& P, double alpha, double tol = 1.e-4, size_t max_iters = 64, size_t num_threads = 1) {

  Vector x(P.num_rows(), 1.0);
  x *= 1.0 / one_norm(x);

  for (size_t i = 0; i < max_iters; ++i) {

    Vector y = mult(x, P);    // Don't parallelize me

    y *= alpha;

    y += (1.0 - alpha) / static_cast<double>(x.num_rows());

    if (two_norm(x - y) < tol * two_norm(x)) {
      std::cout << "Converged in " << i << " iterations" << std::endl;
      return y;
    }
    std::swap(x, y);
  }

  return x;
}

std::vector<size_t> rank(const Vector& x) {
  using element = std::pair<double, size_t>;
  std::vector<element> rp(x.num_rows());

  for (size_t i = 0; i < x.num_rows(); ++i) {
    std::get<0>(rp[i]) = x(i);
    std::get<1>(rp[i]) = i;
  }
  std::sort(rp.begin(), rp.end(), [](element& a, element& b) -> bool { return (std::get<0>(a) > std::get<0>(b)); });

  std::vector<size_t> r(x.num_rows());

  for (size_t i = 0; i < x.num_rows(); ++i) {
    r[i] = std::get<1>(rp[i]);
  }

  return r;
}

std::vector<std::string> read_labels(const std::string& filename) {
  std::ifstream            input_file(filename);
  std::vector<std::string> labels;

  std::string string_input;
  while (std::getline(input_file, string_input)) {
    labels.push_back(string_input);
  }
  return labels;
}

#endif    //  AMATH583_PAGERANK_HPP
