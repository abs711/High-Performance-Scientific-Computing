//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <cmath>
#include <iostream>
#define WITHOUT_NUMPY
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main () {
  double pi = std::acos(-1.0);  // C++ does not mandate a value for pi

  plt::figure_size(1280, 960);  // Initialize a 1280 X 960 figure

  std::vector<double> x(1024);  // Create two vectors
  std::vector<double> y(1024);

  // Fill in x with values from 0 to 4*pi (equally spaced)
  double N = 4.0;
  for (size_t i = 0; i < 1024; ++i) {
    x[i] = ((double)i/(double)1023)*(N*pi);// WRITE ME
  }

  // Fill in y with cos of x
  for (size_t i = 0; i < 1024; ++i) {
    y[i] =  cos(x[i]);// WRITE ME
  }

  //for (auto i: x)
  //  std::cout << i << ' ';

  // Check that the last value of x has the right value
  if (std::abs(x[1023] - N * pi) < 1.0e-12) {
    std::cout << "Pass" << std::endl;
  } else {
    std::cout << "Fail" << " " << std::abs(x[1023] - N * pi) << std::endl;
  }

  // Make the plot and save it to a file
  plt::plot(x, y);
  plt::save("cosx.png");

  return 0;
}
