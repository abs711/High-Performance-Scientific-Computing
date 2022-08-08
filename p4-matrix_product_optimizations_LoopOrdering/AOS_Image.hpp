//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_AOS_IMAGE_HPP
#define AMATH583_AOS_IMAGE_HPP

#include <array>
#include <cstddef>
#include <string>
#include <vector>

#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;

class AOS_Image {
public:
  AOS_Image(size_t M, size_t N) : nrows_(M), ncols_(N), storage_(M * N) {}

  const double& operator()(size_t i, size_t j, size_t k) const { return storage_[i * ncols_ + j][k]; }
  double&       operator()(size_t i, size_t j, size_t k) { return storage_[i * ncols_ + j][k]; }

  size_t num_rows() const { return nrows_; }
  size_t num_cols() const { return ncols_; }

private:
  size_t                             nrows_;
  size_t                             ncols_;
  std::vector<std::array<double, 3>> storage_;
};

AOS_Image to_aos(const CImg<double>& from) {
  AOS_Image img(from.height(), from.width());

  for (size_t i = 0; i < img.num_rows(); ++i) {
    for (size_t j = 0; j < img.num_cols(); ++j) {
      for (size_t k = 0; k < 3; ++k) {
        img(i, j, k) = from(i, j, k);
      }
    }
  }
  return img;
}

CImg<double> from_aos(const AOS_Image& from) {
  CImg<double> img(from.num_rows(), from.num_cols(), 1, 3);

  for (int i = 0; i < img.height(); ++i) {
    for (int j = 0; j < img.width(); ++j) {
      for (int k = 0; k < 3; ++k) {
        img(i, j, k) = from(i, j, k);
      }
    }
  }
  return img;
}

#endif
