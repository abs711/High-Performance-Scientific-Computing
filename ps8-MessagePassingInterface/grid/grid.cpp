//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//


#include <iomanip>
#include <iostream>
#include <mpi.h>

#include "Grid.hpp"
#include "Stencil.hpp"
#include "Timer.hpp"
#include "cg.hpp"
#include "ir.hpp"
#include "jacobi.hpp"
#include "mpiStencil.hpp"

#include "mpiMath.hpp"

enum method { with_ir, with_jacobi, with_cg };

void usage(const std::string& msg) { std::cout << "Usage: " << msg << std::endl; }

int main(int argc, char* argv[]) {

  bool   seq   = true;
  method mtd   = with_jacobi;
  size_t xsize = 128, ysize = 128;
  size_t maxiter = 128;
  double tolerance = 1.e-6;
  bool debug = false;

  try {
    for (int arg = 1; arg < argc; ++arg) {
      if (std::string(argv[arg]) == "-p") {
        seq = false;
      } else if (std::string(argv[arg]) == "-x") {
        if (argc == ++arg) usage(argv[0]);
        xsize = std::stol(argv[arg]);
      } else if (std::string(argv[arg]) == "-y") {
        if (argc == ++arg) usage(argv[0]);
        ysize = std::stol(argv[arg]);
      } else if (std::string(argv[arg]) == "-m") {
        if (argc == ++arg) usage(argv[0]);
        maxiter = std::stol(argv[arg]);
      } else if (std::string(argv[arg]) == "-j") {
        mtd = with_jacobi;
      } else if (std::string(argv[arg]) == "-c") {
        mtd = with_cg;
      } else if (std::string(argv[arg]) == "-i") {
        mtd = with_ir;
      } else if (std::string(argv[arg]) == "-d") {
	debug = true;
      } else if (std::string(argv[arg]) == "-t") {
        if (argc == ++arg) usage(argv[0]);
        tolerance = std::stod(argv[arg]);
      }
    }
  } catch (int) {
    usage(argv[0]);
    return -1;
  }

  auto print_info = [&]() {
    std::cout << "Parallel " << (seq ? "No" : "Yes") << std::endl;
    std::cout << "maxiter " << maxiter << std::endl;    
    std::cout << "xsize " << xsize << std::endl;
    std::cout << "ysize " << ysize << std::endl;        
    switch (mtd) {
    case with_jacobi:
      std::cout << "With jacobi" << std::endl;      
      break;
    case with_ir:
      std::cout << "With ir" << std::endl;      
      break;
    case with_cg:
      std::cout << "With cg" << std::endl;      
      break;
    default:
      std::cerr << "This should never happen" << std::endl;
      abort();
      break;
    }
  };


  if (seq) {
    if (debug) {
      print_info();
    }

    Grid X0(xsize, ysize), X1(xsize, ysize);

    for (size_t i = 0; i < ysize+2; ++i) {
      X1(0, i) = X0(0, i) = ((double) i) / ((double) ysize+1);
    }
#if 1
    for (size_t j = 0; j < xsize+2; ++j) {
      X1(j, ysize+1) = X0(j, ysize+1) = ((double) j) / ((double) xsize+1);
    }
#endif

    Stencil A;
    size_t num_iters = 0;

    DEF_TIMER(seqgrid);
    START_TIMER(seqgrid);
    switch(mtd) {
    case with_jacobi:
      num_iters = jacobi(A, X1, X0, maxiter, tolerance, debug);
      break;
    case with_ir:
      num_iters = ir(A, X1, X0, maxiter, tolerance, debug);
      break;
    case with_cg:
      num_iters = cg(A, X1, X0, maxiter, tolerance, debug);
      break;
    default:
      std::cerr << "This should never happen" << std::endl;
      abort();
      break;
    }
    STOP_TIMER(seqgrid);
    std::cout << "# " << num_iters << " iterations" << std::endl;
    Grid r = X0 - A*X1;
    std::cout << "# ||r|| = " << std::sqrt(dot(r,r)) << std::endl;    

  } else {
    MPI::Init();
    size_t myrank = MPI::COMM_WORLD.Get_rank();
    size_t mysize = MPI::COMM_WORLD.Get_size();
    
    if (debug && 0 == myrank) {
      print_info();
    }

    if (debug && false) {
      std::cout << "comm size " << mysize << std::endl;
      std::cout << "comm rank " << myrank << std::endl;
    }

    size_t lsize = xsize / mysize;

    Grid X0(lsize, ysize), X1(lsize, ysize);

    if (0 == myrank) {
      for (size_t i = 0; i < ysize+2; ++i) {
	X1(0, i) = X0(0, i) = ((double) i) / ((double) ysize+1);
      }
    }

#if 1
    for (size_t j = 0; j < lsize+2; ++j) {
      size_t k = myrank*lsize + j;
      X1(j, ysize+1) = X0(j, ysize+1) = ((double) k) / ((double) xsize+1);
    }
#endif

    mpiStencil A;
    size_t num_iters = 0;

    DEF_TIMER(mpigrid);
    START_TIMER(mpigrid);
    switch(mtd) {
    case with_jacobi:
      num_iters = jacobi(A, X1, X0, maxiter, tolerance, debug);
      break;
    case with_ir:
      num_iters = ir(A, X1, X0, maxiter, tolerance, debug);
      break;
    case with_cg:
      num_iters = cg(A, X1, X0, maxiter, tolerance, debug);
      break;
    default:
      std::cerr << "This should never happen" << std::endl;
      abort();
      break;
    }
    if (myrank == 0) {
      STOP_TIMER(mpigrid);
      std::cout << "# " << num_iters << " iterations" << std::endl;
    }
    Grid r = X0 - A*X1;
    double rn = std::sqrt(mpi_dot(r,r));
    
    if (myrank == 0) {
      std::cout << "# ||r|| = " << rn  << std::endl;
    } else {
      double foo = STOP_TIMER_QUIETLY(mpigrid);
    }
    MPI::Finalize();
  }

  return 0;
}
