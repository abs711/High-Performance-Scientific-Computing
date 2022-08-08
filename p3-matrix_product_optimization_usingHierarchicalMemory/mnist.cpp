//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;

#include "Matrix.hpp"
#include "amath583.hpp"
#include "Timer.hpp"
#include "mnist.hpp"
#include <cassert>
#include <iomanip>

void usage(const std::string& msg) { std::cout << "Usage: " << msg << " mnist_file [ max_images ]" << std::endl; }

double gflops(const Matrix& similarity, const Matrix& A, double elapsed_ms) {
  double flops    = 2.0 * similarity.num_rows() * similarity.num_cols() * A.num_cols();
  if (elapsed_ms == 0.0) {
    return -1.0;
  }
  double floppage = flops / (elapsed_ms / 1e3);
  return floppage / 1.e9;
}

std::vector<std::string> names = {
  "#images", 

  "mult_0(A,B)", 
  "mult_1(A,B)", 
  "mult_2(A,B)", 
  "mult_3(A,B)", 

  "m_t_0(A,C)", 
  "m_t_1(A,C)", 
  "m_t_2(A,C)", 
  "m_t_3(A,C)", 

  "m_t_0(A,A)", 
  "m_t_1(A,A)", 
  "m_t_2(A,A)", 
  "m_t_3(A,A)", 

  "m_t_4(A)",
  "m_t_5(A,A)"  // Extra Credit
  };


template <class F, class Mat, class V1, class V2>
void run_benchmark(int i, F f, const Mat& A, const Mat& B, Mat& S, V1& layout, V2& times) {
  Timer t;
  if (layout[i] == false) {
    t.start();
    f(A, B, S);
    t.stop();
    double g = gflops(S, A, t.elapsed());
    times.push_back(g);
    if (g < 2.0) {
      layout[i] = true;
    }
  } else {
    times.push_back(-1.0);
  }
}


int main(int argc, char* argv[]) {
  size_t max_num_images = 4096;

  if (argc < 2) {
    usage(argv[0]);
    return -1;
  }
  std::cout << argc << std::endl;

  if (argc >= 3) {
    max_num_images = std::stod(argv[2]);
  }

  std::vector<std::vector<double>> all_times;

  for (size_t i = 0; i < names.size(); ++i) {
    std::cout << std::setw(12) << names[i];
  }
  std::cout << std::endl;

  std::vector<double> layout(names.size(), false);

  for (size_t num_images = 128; num_images <= max_num_images; num_images *= 2) {
    std::vector<double> times;
    Matrix A = read_mnist(std::string(argv[1]), num_images);

#ifndef NDEBUG
    std::cout << "Read " << A.num_rows() << " images, each with " << A.num_cols() << " pixels" << std::endl;
    std::cout << "A is " << A.num_rows() << " by " << A.num_cols() << std::endl;
#endif

    num_images = A.num_rows();

    Matrix similarity(num_images, num_images);
    Matrix B = transpose(A);
    Matrix C = A;

    times.push_back(num_images);

    run_benchmark(0, mult_0, A, B, similarity, layout, times);
    run_benchmark(1, mult_1, A, B, similarity, layout, times);
    run_benchmark(2, mult_2, A, B, similarity, layout, times);
    run_benchmark(3, mult_3, A, B, similarity, layout, times);

    run_benchmark(4, mult_trans_0, A, C, similarity, layout, times);
    run_benchmark(5, mult_trans_1, A, C, similarity, layout, times);
    run_benchmark(6, mult_trans_2, A, C, similarity, layout, times);
    run_benchmark(7, mult_trans_3, A, C, similarity, layout, times);

    run_benchmark(8, mult_trans_0, A, A, similarity, layout, times);
    run_benchmark(9, mult_trans_1, A, A, similarity, layout, times);
    run_benchmark(10, mult_trans_2, A, A, similarity, layout, times);
    run_benchmark(11, mult_trans_3, A, A, similarity, layout, times);
    
    Timer t;
    if (layout[12] == false) {
      t.start();
      mult_trans_4(A, similarity);      
      t.stop();
      double g = gflops(similarity, A, t.elapsed());
      times.push_back(g);
      if (g < 2.0) {
	layout[12] = true;
      }
    } else {
      times.push_back(-1.0);
    }

    run_benchmark(13, mult_trans_5, A, A, similarity, layout, times); // Extra Credit

    all_times.push_back(times);
    
    for (size_t i = 0; i < times.size(); ++i) {
      std::cout << std::setw(12) << times[i];
    }
    std::cout << std::endl;

    CImg<double> sim_img(num_images, num_images, 1, 1, 255);
    double       max_val = 0;
    for (size_t i = 0; i < num_images; ++i) {
      for (size_t j = 0; j < num_images; ++j) {
	max_val = std::max(max_val, similarity(i, j));
      }
    }
    for (size_t i = 0; i < num_images; ++i) {
      for (size_t j = 0; j < num_images; ++j) {
	sim_img(i, j, 0, 0) = 255.0 * similarity(i, j) / max_val;
      }
    }
    sim_img.save_bmp(("mnist_similarity_" + std::to_string(num_images) + ".bmp").c_str());
  }

  return 0;
}
