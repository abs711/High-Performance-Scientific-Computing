//
// This file is part of the course materials for AMATH 483/583 at the University of Washington
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_EIGENFACES_MAIN_HPP
#define AMATH583_EIGENFACES_MAIN_HPP

#define __USE_CIMG

#ifdef __USE_CIMG
#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;
#endif

#include <vector>

#include "Timer.hpp"
#include "amath583.hpp"
#include "face_db.hpp"
#include "mkl_lapack.h"

void usage(const std::string& msg) {
  std::cout << "Usage: " + msg << " [-i bin_file] [-n num_images] [-f faces_to_save] [-z size]" << std::endl;
}

int main(int argc, char* argv[]) {

  size_t      faces_to_save = 0;
  size_t      num_images    = 500;
  std::string bin_file      = "";
  std::string face_size     = "55x45";
  size_t      height        = 55;
  size_t      width         = 45;

  try {
    for (int arg = 1; arg < argc; ++arg) {
      if (std::string(argv[arg]) == "-i") {
        if (argc == ++arg) usage(argv[0]);
        bin_file = std::string(argv[arg]);
      } else if (std::string(argv[arg]) == "-z") {
        if (argc == ++arg) usage(argv[0]);
        face_size = std::string(argv[arg]);
      } else if (std::string(argv[arg]) == "-n") {
        if (argc == ++arg) usage(argv[0]);
        num_images = std::stol(argv[arg]);
      } else if (std::string(argv[arg]) == "-f") {
        if (argc == ++arg) usage(argv[0]);
        faces_to_save = std::stol(argv[arg]);
      } else {
        usage(argv[0]);
        return -1;
      }
    }
  } catch (int) {
    usage(argv[0]);
    return -1;
  }

  if (bin_file == "") {
    usage(argv[0]);
    return -1;
  }

  if (face_size == "218x178") {
    height = 218;
    width  = 178;
  } else if (face_size == "109x89") {
    height = 109;
    width  = 89;
  } else if (face_size == "55x45") {
    height = 55;
    width  = 45;
  } else {
    std::cout << "Bad face size" << std::endl;
    return -1;
  }

  std::cout << "# Face size " << height << " x " << width << std::endl;
  std::cout << "# Reading " << bin_file << std::endl;

  // Read in the face image data
  DEF_TIMER(read_file);
  START_TIMER(read_file);
  face_db A(bin_file, num_images, height, width);
  STOP_TIMER(read_file);

  num_images = A.size();

  // Compute mean of all of the images
  DEF_TIMER(compute_mean);
  START_TIMER(compute_mean);
  Vector sum(height * width);

  for (size_t k = 0; k < num_images; ++k) {
    auto img = A[k];
    for (size_t j = 0; j < height * width; ++j) {
      sum(j) += img(j);
    }
  }
  for (size_t j = 0; j < height * width; ++j) {
    sum(j) /= num_images;
  }
  STOP_TIMER(compute_mean);

  // Subtract mean from all of the images
  DEF_TIMER(compute_shifted);
  START_TIMER(compute_shifted);
  for (size_t k = 0; k < num_images; ++k) {
    for (size_t j = 0; j < height * width; ++j) {
      A[k](j) = A[k](j) - sum(j);
    }
  }
  STOP_TIMER(compute_shifted);

  // Generate the covariance matrix C
  DEF_TIMER(compute_covariance);
  START_TIMER(compute_covariance);
  auto C = gen_covariance(A);
  STOP_TIMER(compute_covariance);
  double elapsed = 1.e-3 * t_compute_covariance.elapsed();
  double gflops  = 2.e-9 * (C.num_rows() * C.num_cols() * num_images);
  std::cout << "# Gflops/s = " << gflops / elapsed << std::endl;

  if (faces_to_save > 0) {

    // Compute SVD of covariance matrix C
    DEF_TIMER(compute_svd);
    START_TIMER(compute_svd);

    int csize = C.num_rows();

    Vector vals(csize);
    Matrix U(csize, csize), VT(csize, csize);
    int    info  = 0;
    int    lwork = -1;
    double wkopt = 0;
    dgesvd("A", "A", &csize, &csize, &C(0, 0), &csize, &vals(0), &U(0, 0), &csize, &VT(0, 0), &csize, &wkopt, &lwork, &info);

    lwork = (int)wkopt;
    Vector work(lwork);

    dgesvd("A", "A", &csize, &csize, &C(0, 0), &csize, &vals(0), &U(0, 0), &csize, &VT(0, 0), &csize, &work(0), &lwork, &info);
    STOP_TIMER(compute_svd);

#ifdef __USE_CIMG
    cimg_library::CImg<float> mean_face = cimg_library::CImg<float>(&sum(0), width, height).resize(450, 500, 1, 1, 5);
    mean_face.save(("mean_face_" + std::string(tag) + "_" + std::to_string(num_images) + "_" +
		    std::to_string(height) + "_" + std::to_string(width) + ".bmp").c_str());

    for (size_t f = 0; f < faces_to_save; ++f) {
      Vector face(csize);
      for (size_t i = 0; i < face.num_rows(); ++i) {
        face(i) = U(f, i);
      }
      cimg_library::CImg<float> u0_img = cimg_library::CImg<float>(&face(0), width, height).resize(450, 500, 1, 1, 5);
      u0_img.normalize(0, 255).save(("u_" + std::string(tag) + "_" + std::to_string(f) + "_" + std::to_string(num_images) + "_" +
                                     std::to_string(height) + "_" + std::to_string(width) + ".bmp")
                                        .c_str());
    }
#endif
  }

  return 0;
}

#endif    // AMATH583_EIGENFACES_MAIN_HPP
