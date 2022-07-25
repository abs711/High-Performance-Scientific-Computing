//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//

#include <iostream>
#include "Timer.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " N" << std::endl;
    return -1;
  }
  size_t loops = std::stol(argv[1]);

  // long a = 3, b = 314, c = 159;
  long a = 3, b = 14, c = 0;
  // double a = 3.14, b = 3.14159, c = 0.0;

  Timer T;
  T.start();
  for (size_t i = 0; i < loops; ++i) {
    c += a * b;
  }
  T.stop();

  std::cout << loops << " loops took " << T.elapsed() << " milliseconds" << std::endl;

  return 0;
}
