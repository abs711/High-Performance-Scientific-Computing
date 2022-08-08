//
// This file is part of the course materials for AMATH 483/583 at the University of Washington
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#define __USE_CIMG

#ifdef __USE_CIMG
#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;
#endif

#include <algorithm>
#include <numeric>
#include <vector>

#include <mpi.h>

#include "Timer.hpp"
#include "amath583.hpp"
#include "face_db.hpp"
#include "mkl_lapack.h"
#include "mkl_cblas.h"

// Replace outer and gen_covariance with your best versions
// But don't normalize here!

// Replace me
void outer(Matrix& A, const Vector& x) {
  
#pragma omp parallel for
for (size_t i = 0; i < A.num_rows(); ++i) {
    double t = x(i);
    for (size_t j = 0; j < A.num_cols(); ++j) {
      A(i, j) += t * x(j);
    }
  }
}

// Replace me
auto gen_covariance(const std::vector<Vector>& z) {



  size_t sz = z[0].num_rows();
    Matrix F(sz, z.size());
    Matrix C(sz, sz);
   
    for (size_t k = 0; k < z.size(); ++k) {
        for (size_t i = 0; i < C.num_rows(); ++i) {
            F(i, k) = z[k](i);
    
        }
    }
    double alpha = 1;
    double beta = 0;
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, sz, sz, z.size(), alpha, &F(0,0), z.size(), &F(0,0), z.size(), beta, &C(0,0), sz);


  return C;
}


auto scatter_images(const std::string& bin_file, size_t num_images, size_t height, size_t width) {
  size_t myrank = MPI::COMM_WORLD.Get_rank();
  size_t mysize = MPI::COMM_WORLD.Get_size();

  // Count how many images each rank needs
  std::vector<size_t> sendcounts(mysize);
  std::fill(sendcounts.begin(), sendcounts.end(), num_images / mysize);
  for (size_t i = 0; i < num_images % mysize; ++i) {
    ++sendcounts[i];
  }

  // Allocate a local vector for my image data
  std::vector<Vector> myimg_data(sendcounts[myrank], Vector(height * width));

  // Send from 0 to everyone
  if (myrank == 0) {
    DEF_TIMER(read_file);
    START_TIMER(read_file);
    face_db z(bin_file, num_images, height, width);
    STOP_TIMER(read_file);

    DEF_TIMER(scattering);
    START_TIMER(scattering);
    if (mysize > 1) {
      size_t count = sendcounts[1];
      for (size_t rank = 1; rank < mysize; ++rank) {
        for (size_t i = 0; i < sendcounts[rank]; ++i) {

	  // Send z[count]
	  // Write me
          MPI::COMM_WORLD.Send(&z[count](0), height * width, MPI::DOUBLE, rank, 321);
          ++count;

        }
      }
    }

    // Copy rather than send to myself (rank 0)
    for (size_t i = 0; i < sendcounts[myrank]; ++i) {
      for (size_t j = 0; j < height * width; ++j) {
        myimg_data[i](j) = z[i](j);
      }
    }
    STOP_TIMER(scattering);
  } else {

    // Everyone else receive images from rank 0
    for (size_t i = 0; i < sendcounts[myrank]; ++i) {

      // Receive myimg_data[i]
      // Write me
      MPI::COMM_WORLD.Recv(&myimg_data[i](0), height * width, MPI::DOUBLE, 0 , 321);
    }
  }
  
  return myimg_data;
}


void usage(const std::string& msg) {
  std::cout << "Usage: " + msg << " [-i bin_file] [-n num_images] [-f faces_to_save] [-z size]" << std::endl;
}

int main(int argc, char* argv[]) {

  MPI::Init();
  size_t myrank = MPI::COMM_WORLD.Get_rank();

  size_t      faces_to_save = 0;
  size_t      num_images    = 500;
  std::string bin_file      = "";
  std::string face_size     = "55x45";
  size_t      height        = 55;
  size_t      width         = 45;

  if (myrank == 0) {
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
          num_images = -1;
          break;
        }
      }
    } catch (int) {
      usage(argv[0]);
      num_images = -1;
    }

    if (bin_file == "") {
      usage(argv[0]);
      num_images = -1;
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
      num_images = -1;
    }
    std::cout << "# Face size " << height << " x " << width << std::endl;
  }

  MPI::COMM_WORLD.Bcast(&num_images, 1, MPI::UNSIGNED_LONG, 0);
  if (num_images == (size_t)-1) {
    MPI_Finalize();
    return -1;
  }
  MPI::COMM_WORLD.Bcast(&height, 1, MPI::UNSIGNED_LONG, 0);
  MPI::COMM_WORLD.Bcast(&width, 1, MPI::UNSIGNED_LONG, 0);

  // After this, all processes will have a local subset of images in A
  auto A = scatter_images(bin_file, num_images, height, width);


  DEF_TIMER(compute_mean);
  START_TIMER(compute_mean);

  // First all processes compute local sum of their images
  Vector local_sum(height * width);
  for (size_t k = 0; k < A.size(); ++k) {
    auto img = A[k];
    for (size_t j = 0; j < height * width; ++j) {
      local_sum(j) += img(j);
    }
  }

  // Write me
  // Add up all the local_sums to global sum
  // All processes need global sum
  Vector sum(height * width);
  MPI::COMM_WORLD.Allreduce(&local_sum(0), &sum(0), height*width , MPI::DOUBLE, MPI::SUM);
  

  // Divide global sum by num_images to get average
  for (size_t j = 0; j < height * width; ++j) {
    sum(j) /= num_images;
  }

  if (myrank == 0) STOP_TIMER(compute_mean);


  // All processes compute their local shifted images
  DEF_TIMER(compute_shifted);
  START_TIMER(compute_shifted);

  for (size_t k = 0; k < A.size(); ++k) {
    for (size_t j = 0; j < height * width; ++j) {
      A[k](j) = A[k](j) - sum(j);
    }
  }

  if (myrank == 0) STOP_TIMER(compute_shifted);


  // All processes wait here (to aid with timing next op)
  MPI::COMM_WORLD.Barrier();

  DEF_TIMER(compute_covariance);
  START_TIMER(compute_covariance);

  // All processes compute their non-normalized contributions to covariance
  auto   local_C = gen_covariance(A);

  DEF_TIMER(reduce);
  START_TIMER(reduce);

  // Write me
  // Add up all the local_Cs to C
  // Only rank 0 needs C
  Matrix C(local_C.num_rows(), local_C.num_cols());
  MPI::COMM_WORLD.Reduce(&local_C(0,0), &C(0,0), C.num_rows() * C.num_cols(), MPI::DOUBLE, MPI::SUM,0);
  
      

  if (myrank == 0) STOP_TIMER(reduce);

  if (myrank == 0) {

    // Normalize here
    for (size_t i = 0; i < C.num_rows(); ++i) {
      for (size_t j = 0; j < C.num_cols(); ++j) {
	C(i,j) = C(i,j) / num_images;
      }
    }

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
      mean_face.save(("mean_face_" + std::string("mpi") + "_" + std::to_string(num_images) + "_" +
		      std::to_string(height) + "_" + std::to_string(width) + ".bmp").c_str());

      for (size_t f = 0; f < faces_to_save; ++f) {
        Vector face(C.num_rows());
        for (size_t i = 0; i < face.num_rows(); ++i) {
          face(i) = U(f, i);
        }
        cimg_library::CImg<float> u0_img = cimg_library::CImg<float>(&face(0), width, height).resize(450, 500, 1, 1, 5);
        u0_img.normalize(0, 255).save(("u_mpi_" + std::to_string(f) + "_" + std::to_string(num_images) + "_" + std::to_string(height) + "_" +
                                       std::to_string(width) + ".bmp")
                                          .c_str());
      }

#endif
    }
  }

  MPI::Finalize();

  return 0;
}
