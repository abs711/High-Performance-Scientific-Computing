//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//


#include "Matrix.hpp"
#include "amath583.hpp"
#include "Timer.hpp"
#include <iostream>



int main(int argc, char* argv[]) {

  if (argc < 2) {
    std::cout << "Please supply a size" << std::endl;
    return -1;
  }
  size_t size = std::stol(argv[1]);

  Matrix A(size, size), B(size, size), C(size, size);

  Timer t;
  t.start();
  mult_0(A, B, C);
  t.stop();
  
  std::cout << "mult_0(A, B, C) for size = " << size << " took " << t.elapsed() << " ms" << std::endl;

  return 0;
}
