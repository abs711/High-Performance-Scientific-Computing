//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2017
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <cmath>
#include <iomanip>
#include <iostream>
#include <mpi.h>
#include <string>
#include <cstdlib>

typedef unsigned long size_t;

double partial_pi(size_t begin, size_t end, size_t skip, double h) {
  double partial_pi = 0.0;
  for (size_t i = begin; i < end; i += skip) {
    partial_pi += 4.0 / (1.0 + (i * h * i * h));
  }
  return partial_pi;
}

namespace MPI {
  class RAII {
  public:
    RAII()  { Init();     }
    ~RAII() { Finalize(); }
  };
}


int main(int argc, char* argv[]) {
  MPI::RAII X;

  size_t intervals = 1024 * 1024;

  int myrank = MPI::COMM_WORLD.Get_rank();
  int mysize = MPI::COMM_WORLD.Get_size();
  std::cout << " I AM " << myrank << " OF " << mysize << std::endl;
  if (0 == myrank) {
    if (argc >= 2) intervals = std::atol(argv[1]);
  }

  MPI::COMM_WORLD.Bcast(&intervals, 1, MPI::UNSIGNED_LONG, 0);

  double h    = 1.0 / ((double)intervals);
  double mypi = h * partial_pi(myrank, intervals, mysize, h);

  double pi = 0.0;
  MPI::COMM_WORLD.Reduce(&mypi, &pi, 1, MPI::DOUBLE, MPI::SUM, 0);

  if (myrank == 0) {
    std::cout << "pi is approximately " << std::setprecision(15) << pi << std::endl;
    std::cout << "error is " << std::abs(M_PI - pi) << std::endl;
  }

  return 0;
}
