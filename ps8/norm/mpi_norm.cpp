//
// This file is part of the course materials for AMATH 483/583 at the University of Washington
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <mpi.h>
#include <string>
#include "Timer.hpp"
#include "amath583.hpp"


double mpi_norm(const Vector& local_x) {
  double global_rho = 0.0;

  // Write me -- compute local sum of squares and then REDUCE 
  // ALL ranks should get the same global_rho  (that was a hint)

  double local_rho = 0.0; // local variable
  for (size_t i = 0; i<local_x.num_rows(); ++i) {
     local_rho += local_x(i)*local_x(i); // local rho computations
  }	

  //Reduce from local to global variable and update all the ranks with the same value
  MPI::COMM_WORLD.Allreduce(&local_rho, &global_rho, 1, MPI::DOUBLE, MPI::SUM);
  // Summing a local variables and updating all the ranks

  return std::sqrt(global_rho);
}


template <class F>
size_t find_10ms_size(F&& f) {
  Timer t;
  size_t sz = 128;

  for (; sz < 1024 * 1024 * 1024; sz *= 1.414) {
    Vector x(sz);
    t.start();
    f(x);
    t.stop();
    if (t.elapsed() >= 10.0) {
      break;
    }
  }

  return sz;
}


size_t num_trials(size_t base_size, size_t nnz) {
  double N_1k = std::ceil((static_cast<double>(base_size) * 50.0) / static_cast<double>(nnz));

  return 5 + static_cast<size_t>(N_1k);
}


int main(int argc, char* argv[]) {
  MPI::Init();

  size_t myrank = MPI::COMM_WORLD.Get_rank();
  size_t mysize = MPI::COMM_WORLD.Get_size();

  size_t exponent           = 24;
  size_t num_trips          = 32;
  size_t num_elements 	    = 0;

	
	
  if (0 == myrank) {

    if (argc >= 2) exponent   = std::stol(argv[1]);

    size_t total_elements = 1 << exponent;
    num_elements = total_elements / mysize;

    size_t base_size = find_10ms_size(static_cast<double(*)(const Vector&)>(two_norm));
    num_trips = num_trials(base_size, num_elements);

    //std::cout << myrank << ", num_elements: "<< num_elements <<std::endl;
  } 

  // Every rank gets num_elements and num_trips
  MPI::COMM_WORLD.Bcast(&num_elements, 1, MPI::UNSIGNED_LONG, 0);
  MPI::COMM_WORLD.Bcast(&num_trips, 1, MPI::UNSIGNED_LONG, 0);

  size_t global_size = myrank == 0 ? num_elements * mysize : 0;
  Vector x(global_size);

  double rho = 0.0;
  if (myrank == 0) {
    randomize(x, 10.0, 0.0);
    rho = std::sqrt(std::inner_product(&x(0), &x(0)+x.num_rows(), &x(0), 0.0)); // get sequential result
  }

  //
  // Parallelize me -- the contents of vector x on rank 0 should be randomized and scattered to local_x on all ranks
  //
  Vector local_x(num_elements);
  

  MPI::COMM_WORLD.Scatter(&x(0), num_elements, MPI::DOUBLE, &local_x(0), num_elements, MPI::DOUBLE, 0);


  double sigma = 0.0;

  if (myrank == 0) {
    DEF_TIMER(mpi_norm);
    START_TIMER(mpi_norm);
    for (size_t i = 0; i < num_trips; ++i) {
      sigma = mpi_norm(local_x);
    }
    STOP_TIMER(mpi_norm);

    double ms_per = t_mpi_norm.elapsed() / static_cast<double>(num_trips);
    std::cout << "# msec_per norm [mpi_norm]: " << ms_per << std::endl;
    double gflops = 2.0 * num_trips * num_elements * mysize / 1.e9;
    double gflops_sec = gflops / (t_mpi_norm.elapsed() * 1.e-3);
    std::cout << "# gflops / sec [mpi_norm]: " << gflops_sec << std::endl;
    std::cout << "# | rho - sigma | = " << std::abs((rho-sigma)/sigma) << std::endl;

  } else {
    for (size_t i = 0; i < num_trips; ++i) {
      sigma = mpi_norm(local_x);
    }
  }
  
  MPI::Finalize();
  
  return 0;
}
