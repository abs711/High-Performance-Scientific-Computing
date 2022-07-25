//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "norm_utils.hpp"
#include "norms.hpp"

int main(int argc, char* argv[]) {
  size_t N_min = 1024 * 1024;
  size_t N_max = 32 * 1024 * 1024;

  size_t threads_max = 8;

  if (argc >= 2) {
    N_min = std::stol(argv[1]);
  }
  if (argc >= 3) {
    N_max = std::stol(argv[2]);
  }
  if (argc >= 4) {
    threads_max = std::stol(argv[3]);
  }

  run(norm_cyclic_reduction, N_min, N_max, threads_max);

  return 0;
}
