//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "pagerank.hpp"

void usage(const std::string& msg) {
  std::cout << "Usage: " + msg << " [-l label_file] [-a alpha] [-t tol] [-n num_threads] [-i max_iters] [-v N] input_file"
            << std::endl;
}

int main(int argc, char* argv[]) {

  std::string input_file  = "";
  std::string label_file  = "";
  size_t      num_threads = 1;
  size_t      max_iters   = 100;
  double      tol         = 1.e-4;
  double      alpha       = .85;
  int         verbose     = -1;

  try {
    for (int arg = 1; arg < argc; ++arg) {
      if (std::string(argv[arg]) == "-v") {
        if (argc == ++arg) usage(argv[0]);
        verbose = std::stol(argv[arg]);
      } else if (std::string(argv[arg]) == "-l") {
        if (argc == ++arg) usage(argv[0]);
        label_file = std::string(argv[arg]);
      } else if (std::string(argv[arg]) == "-n") {
        if (argc == ++arg) usage(argv[0]);
        num_threads = std::stol(argv[arg]);
      } else if (std::string(argv[arg]) == "-a") {
        if (argc == ++arg) usage(argv[0]);
        alpha = std::stod(argv[arg]);
      } else if (std::string(argv[arg]) == "-t") {
        if (argc == ++arg) usage(argv[0]);
        tol = std::stod(argv[arg]);
      } else if (std::string(argv[arg]) == "-i") {
        if (argc == ++arg) usage(argv[0]);
        max_iters = std::stol(argv[arg]);
      } else {
        if (input_file != "") {
          usage(argv[0]);
          return 1;
        }
        input_file = std::string(argv[arg]);
      }
    }
  } catch (int) {
    usage(argv[0]);
    return -1;
  }

  if (input_file == "") {
    usage(argv[0]);
    return 1;
  }

  DEF_TIMER(read);
  START_TIMER(read);
  CSRMatrix A = read_csrmatrix(input_file);
  A.stochastify();
  STOP_TIMER(read);

  assert(A.num_rows() != 0);
  assert(A.num_cols() != 0);
  if (A.num_rows() != A.num_cols()) {
    std::cerr << "Error: Matrix " << input_file << " must be symmetric and is instead " << A.num_rows() << " by " << A.num_cols()
              << std::endl;
    return -3;
  }

  // ================================================================
  //
  // Call pagerank
  //
  // ================================================================
  DEF_TIMER(pagerank);
  START_TIMER(pagerank);
  Vector x = pagerank(A, alpha, tol, max_iters, num_threads);
  STOP_TIMER(pagerank);

  for (int i = 0; i < verbose; ++i) {
    std::cout << i << "\t" << x(i) << std::endl;
  }

  // ================================================================
  //
  // Rank order the result
  //
  // ================================================================
  DEF_TIMER(rank);
  START_TIMER(rank);
  auto r = rank(x);
  STOP_TIMER(rank);

  if (verbose == 0) {
    verbose = x.num_rows();
  }

  if (label_file != "") {
    std::vector<std::string> labels = read_labels(label_file);
    for (int i = 0; i < verbose; ++i) {
      std::cout << i;
      std::cout << "\t" << r[i];
      std::cout << "\t" << x(r[i]);
      std::cout << "\t" << labels[r[i]];
      std::cout << std::endl;
    }
  } else {
    for (int i = 0; i < verbose; ++i) {
      std::cout << i;
      std::cout << "\t" << r[i];
      std::cout << "\t" << x(r[i]);
      std::cout << std::endl;
    }
  }

  return 0;
}
