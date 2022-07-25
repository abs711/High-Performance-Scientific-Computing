//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "Vector.hpp"
#include "amath583.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

void compare_norms(double norm0, double norm1) {
  if (norm1 != norm0) {
    std::cout << "# Norms differ!" << std::endl;
    std::cout << "# Absolute difference: " << std::abs(norm1 - norm0) << std::endl;
    std::cout << "# Relative difference: " << std::abs(norm1 - norm0) / norm0 << std::endl;
  }
}

int main(int argc, char* argv[]) {
  size_t N = 1024 * 1024;

  if (argc == 2) {
    N = std::stol(argv[1]);
  }

  Vector v(N);
  randomize(v, 1, 1);

  // std::cout << "N: " << N << std::endl;

  double norm0 = two_norm(v);
  std::cout << "Calling two_norm first time: " << norm0 << std::endl;

  assert(norm0 == norm0);    // Is this safe / correct to do?
  compare_norms(norm0, norm0);

  double norm1 = two_norm(v);
  std::cout << "Calling two_norm second time: " << norm1 << std::endl;

  assert(norm0 == norm1);    // Is this safe / correct to do?
  compare_norms(norm0, norm1);

  double norm2 = two_norm_r(v);
  std::cout << "Calling two_norm with reversed values: " << norm2 << std::endl;

  // assert(norm0 == norm2);
  compare_norms(norm0, norm2);

  double norm3 = two_norm_s(v);
  std::cout << "Calling two_norm with sorted values: " << norm3 << std::endl;

  // assert(norm0 == norm3);  // Is this safe / correct to do?
  compare_norms(norm0, norm3);

  return 0;
}
