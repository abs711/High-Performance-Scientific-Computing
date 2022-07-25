//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_BLUR_HPP
#define AMATH583_BLUR_HPP

#include <iomanip>
#include <iostream>

#include "Timer.hpp"

#include "AOS_Image.hpp"
#include "SOA_Image.hpp"
#include "Tensor_Image.hpp"

SOA_Image blur_0(const SOA_Image& img) {

  // Construct an image to hold result
  SOA_Image blurred(img.num_rows(), img.num_cols());

  Timer t;
  t.start();

  // Iterate through the image
  for (size_t i = 1; i < img.num_rows() - 1; ++i) {
    for (size_t j = 1; j < img.num_cols() - 1; ++j) {

      // Iterate through the color planes
      for (size_t k = 0; k < 3; ++k) {

	// Apply blurring kernel
        blurred(i, j, k) = (img(i + 0, j + 0, k) +
			    img(i + 0, j + 1, k) +
			    img(i + 0, j - 1, k) +
			    img(i + 1, j + 0, k) +
			    img(i + 1, j + 1, k) +
                            img(i + 1, j - 1, k) +
			    img(i - 1, j + 0, k) +
			    img(i - 1, j + 1, k) +
			    img(i - 1, j - 1, k)) / 9.0;
      }
    }
  }
  t.stop();
  std::cout << std::setw(12) << t.elapsed() ;
  return blurred;
}


SOA_Image blur_1(const SOA_Image& img) {

  // Construct an image to hold result
  SOA_Image blurred(img.num_rows(), img.num_cols());

  Timer t;
  t.start();

  // Iterate through the color planes
  for (size_t k = 0; k < 3; ++k) {

  // Iterate through the image
    for (size_t i = 1; i < img.num_rows() - 1; ++i) {
      for (size_t j = 1; j < img.num_cols() - 1; ++j) {

	// Apply blurring kernel
        blurred(i, j, k) = (img(i + 0, j + 0, k) +
			    img(i + 0, j + 1, k) +
			    img(i + 0, j - 1, k) +
			    img(i + 1, j + 0, k) +
			    img(i + 1, j + 1, k) +
                            img(i + 1, j - 1, k) +
			    img(i - 1, j + 0, k) +
			    img(i - 1, j + 1, k) +
			    img(i - 1, j - 1, k)) / 9.0;
      }
    }
  }
  t.stop();
  std::cout << std::setw(12) << t.elapsed() ;
  return blurred;
}

AOS_Image blur_2(const AOS_Image& img) {

  // Construct an image to hold result
  AOS_Image blurred(img.num_rows(), img.num_cols());

  Timer t;
  t.start();

  // Iterate through the image
  for (size_t i = 1; i < img.num_rows() - 1; ++i) {
    for (size_t j = 1; j < img.num_cols() - 1; ++j) {

      // Iterate through the color planes
      for (size_t k = 0; k < 3; ++k) {

	// Apply blurring kernel
        blurred(i, j, k) = (img(i + 0, j + 0, k) +
			    img(i + 0, j + 1, k) +
			    img(i + 0, j - 1, k) +
			    img(i + 1, j + 0, k) +
			    img(i + 1, j + 1, k) +
                            img(i + 1, j - 1, k) +
			    img(i - 1, j + 0, k) +
			    img(i - 1, j + 1, k) +
			    img(i - 1, j - 1, k)) / 9.0;
      }
    }
  }
  t.stop();
  std::cout << std::setw(12) << t.elapsed() ;
  return blurred;
}

AOS_Image blur_3(const AOS_Image& img) {

  AOS_Image blurred(img.num_rows(), img.num_cols());

  Timer t;
  t.start();

  // Iterate through the color planes
  for (size_t k = 0; k < 3; ++k) {

    // Iterate through the image
    for (size_t i = 1; i < img.num_rows() - 1; ++i) {
      for (size_t j = 1; j < img.num_cols() - 1; ++j) {

	// Apply blurring kernel
        blurred(i, j, k) = (img(i + 0, j + 0, k) +
			    img(i + 0, j + 1, k) +
			    img(i + 0, j - 1, k) +
			    img(i + 1, j + 0, k) +
			    img(i + 1, j + 1, k) +
                            img(i + 1, j - 1, k) +
			    img(i - 1, j + 0, k) +
			    img(i - 1, j + 1, k) +
			    img(i - 1, j - 1, k)) / 9.0;
      }
    }
  }
  t.stop();
  std::cout << std::setw(12) << t.elapsed() ;
  return blurred;
}

Tensor_Image blur_4(const Tensor_Image& img) {

  Tensor_Image blurred(img.num_rows(), img.num_cols());

  Timer t;
  t.start();

  // Iterate through the image
  for (size_t i = 1; i < img.num_rows() - 1; ++i) {
    for (size_t j = 1; j < img.num_cols() - 1; ++j) {

      // Iterate through the color planes
      for (size_t k = 0; k < 3; ++k) {

	// Apply blurring kernel
        blurred(i, j, k) = (img(i + 0, j + 0, k) +
			    img(i + 0, j + 1, k) +
			    img(i + 0, j - 1, k) +
			    img(i + 1, j + 0, k) +
			    img(i + 1, j + 1, k) +
                            img(i + 1, j - 1, k) +
			    img(i - 1, j + 0, k) +
			    img(i - 1, j + 1, k) +
			    img(i - 1, j - 1, k)) / 9.0;
      }
    }
  }
  t.stop();
  std::cout << std::setw(12) << t.elapsed() ;
  return blurred;
}

Tensor_Image blur_5(const Tensor_Image& img) {

  Tensor_Image blurred(img.num_rows(), img.num_cols());

  Timer t;
  t.start();

  // Iterate through the color planes
  for (size_t k = 0; k < 3; ++k) {

    // Iterate through the image
    for (size_t i = 1; i < img.num_rows() - 1; ++i) {
      for (size_t j = 1; j < img.num_cols() - 1; ++j) {

	// Apply blurring kernel
        blurred(i, j, k) = (img(i + 0, j + 0, k) +
			    img(i + 0, j + 1, k) +
			    img(i + 0, j - 1, k) +
			    img(i + 1, j + 0, k) +
			    img(i + 1, j + 1, k) +
                            img(i + 1, j - 1, k) +
			    img(i - 1, j + 0, k) +
			    img(i - 1, j + 1, k) +
			    img(i - 1, j - 1, k)) / 9.0;
      }
    }
  }
  t.stop();
  std::cout << std::setw(12) << t.elapsed() ;
  return blurred;
}

#endif
