//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_MNIST_HPP
#define AMATH583_MNIST_HPP

#include <fstream>
#include <iostream>
#include <vector>

#include "CImg.h"
#include "Matrix.hpp"

int reverse_int(int i) {
  unsigned char ch1, ch2, ch3, ch4;
  ch1 = i & 255;
  ch2 = (i >> 8) & 255;
  ch3 = (i >> 16) & 255;
  ch4 = (i >> 24) & 255;

  return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

Matrix read_mnist(const std::string filename, size_t num_to_read) {
  std::ifstream file(filename, std::ios::binary);

  if (file.is_open()) {
    int magic_number = 0;
    int num_images   = 0;
    int m_rows       = 0;
    int n_cols       = 0;

    file.read((char*)&magic_number, sizeof(magic_number));
    magic_number = reverse_int(magic_number);

    file.read((char*)&num_images, sizeof(num_images));
    num_images = reverse_int(num_images);

    file.read((char*)&m_rows, sizeof(m_rows));
    m_rows = reverse_int(m_rows);

    file.read((char*)&n_cols, sizeof(n_cols));
    n_cols = reverse_int(n_cols);

    size_t image_size = m_rows * n_cols;

    num_to_read = std::min<size_t>(num_images, num_to_read);
    Matrix A(num_to_read, image_size);

#ifndef NDEBUG
    std::cout << "Reading " << magic_number << " " << num_to_read << " of " << num_images << " " << m_rows << " by " << n_cols
              << std::endl;
#endif

    unsigned char temp[image_size * num_to_read];
    file.read((char*)temp, image_size * num_to_read);

    for (size_t k = 0; k < num_to_read; ++k) {
      for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
          A(k, i * n_cols + j) = (double)temp[k * image_size + i * n_cols + j];
        }
      }

#ifndef NDEBUG
      if (k == 0) {
        double       max_val = 0;
        CImg<double> dbimg(m_rows, n_cols, 1, 1, 255);
        for (int i = 0; i < m_rows; ++i) {
          for (int j = 0; j < n_cols; ++j) {
            dbimg(i, j, 0, 0) = A(k, i * n_cols + j);
            max_val           = std::max(max_val, A(k, i * n_cols + j));
          }
        }
        std::cout << "max val = " << max_val << std::endl;
        dbimg.save_bmp("mnist_0.bmp");
      }
#endif
    }
    return A;
  }
  return Matrix(0, 0);
}

#endif    // AMATH583_MNIST_HPP
