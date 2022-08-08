// -*- c++ -*-
//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/sequence.h>

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Timer.hpp"
#include "Vector.hpp"
#include "amath583.hpp"

template<typename T>
T norm_thrust(const thrust::device_vector<T>& x) {
  T sum = thrust::transform_reduce(x.begin(), x.end(), []__host__ __device__(const float& x) { return x*x; }, T(0), thrust::plus<T>());
  return std::sqrt(sum);
}


void header(const std::string& msg = "") {
  auto& os_ = std::cout;
  if (msg != "") {
    os_ << std::setw(12) << std::left << msg << std::endl;
  }
  os_ << std::setw(12) << std::right << "N";
  os_ << std::setw(12) << std::right << "Sequential";

  os_ << std::setw(12) << std::right << "First";
  os_ << std::setw(12) << std::right << "Second";

  os_ << std::setw(12) << std::right << "First";
  os_ << std::setw(12) << std::right << "Second";

  os_ << std::endl;
}

double Gflops_sec(size_t nnz, size_t trials, double msec) {
  double Gflops = static_cast<double>(trials) * (2.0 * nnz) / 1.e9;
  double sec    = msec / 1.e3;
  if (sec == 0) {
    return 0;
  }
  return Gflops / sec;
}

void log(size_t nnz, size_t ntrials, const std::vector<double>& ms_times, const std::vector<double>& norms) {
  auto& os_ = std::cout;
  os_ << std::setw(12) << std::right << nnz;

  for (size_t i = 0; i < ms_times.size(); ++i) {
    os_ << std::setw(12) << std::right << Gflops_sec(nnz, ntrials, ms_times[i]);
  }
  for (size_t i = 1; i < ms_times.size(); ++i) {
    os_ << std::setw(14) << std::right << std::abs(norms[i] - norms[0]) / norms[0];
  }
  os_ << std::endl;
}

size_t num_trials(size_t nnz) {
  // trials*nnz/1G = 1S => trials = 1G/nnz

  double N_1k = std::ceil(1E9 / static_cast<double>(nnz));

  return 5 + static_cast<size_t>(N_1k);
}

template <class T, typename Function>
void run_cu(Function&& f, size_t N_min, size_t N_max) {
  header(sizeof(T) == 4 ? "\nFloat" : "\nDouble");
  Timer t;

  for (size_t size = N_min; size <= N_max; size *= 2) {
    std::vector<double> ms_times;
    std::vector<double> norms;

    Vector            x(size);
      
    randomize(x);

    double norm0 = two_norm(x);
    double norm1 = 0.0;

    size_t ntrials = num_trials(size);

    t.start();
    for (size_t i = 0; i < ntrials; ++i) {
      norm0 = two_norm(x);
    }
    t.stop();
    ms_times.push_back(t.elapsed());
    norms.push_back(norm0);

    thrust::device_vector<T> X(size);
    thrust::copy(&x(0), &x(0)+x.num_rows(), X.begin());

    for (size_t trip = 0; trip < 2; ++trip) {

      t.start();
      cudaDeviceSynchronize();
      for (size_t i = 0; i < ntrials; ++i) {
        norm1 = f(X);
        cudaDeviceSynchronize();
      }
      t.stop();
      ms_times.push_back(t.elapsed());
      norms.push_back(norm1);
    }

    log(size, ntrials, ms_times, norms);
  }
}




int main(int argc, char* argv[]) {
  size_t N_min = 1024 * 1024;
  size_t N_max = 128 * 1024 * 1024;

  if (argc >= 2) {
    N_min = std::stol(argv[1]);
  }
  if (argc >= 3) {
    N_max = std::stol(argv[2]);
  }

  run_cu<float>(norm_thrust<float>, N_min, N_max);
  run_cu<double>(norm_thrust<double>, N_min, N_max);

  return 0;
}
