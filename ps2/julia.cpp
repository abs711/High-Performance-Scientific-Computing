//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <complex>
#include <cstddef>
#include <iostream>

#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;

int                  scale   = 1024;
double               stretch = 0.5;
std::complex<double> origin{0.0, 0.0};

std::complex<double> xy_to_complex(int ix, int iy) {
  std::complex<double> v = {double(ix) / double(scale) - 0.5, double(iy) / double(scale) - 0.5};
  return v * stretch + origin;
}

std::complex<double> f(std::complex<double> x)  { return std::pow(x,7)+double(23)*std::pow(x,2)-double(13); }  // f(x) = x^6 + 13x^4 - 11
std::complex<double> fp(std::complex<double> x) { return double(7)*std::pow(x,6)+double(46)*std::pow(x,1); }  // derivative of f

int newt(std::complex<double> x0) {
  for (int i = 0; i < 256; ++i) {
    std::complex<double> delta = -f(x0) / fp(x0);
    if (std::abs(delta) < 0.00001) {
      return i;
    }
    x0 += delta;
  }

  return 255;
}

int main() {
  int                 depth  = 1;
  int                 planes = 3;
  unsigned char       white  = 255;
  CImg<unsigned char> julia(scale, scale, depth, planes, white);

  for (int i = 0; i < scale; ++i) {
    for (int j = 0; j < scale; ++j) {
      std::complex<double> x   = xy_to_complex(i, j);       // convert screen coord to complex number
      unsigned char        pix = (unsigned char)newt(x);    // get number of iterations
      julia(i, j, 0, 0)        = 13 * pix;                  // red
      julia(i, j, 0, 1)        = 17 * pix;                  // green
      julia(i, j, 0, 2)        = 21 * pix;                  // blue
    }
  }

  julia.save_bmp("julia.bmp");

  return 0;
}
