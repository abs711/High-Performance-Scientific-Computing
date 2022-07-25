
#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "Matrix.hpp"
#include "amath583.hpp"
#include "Timer.hpp"


void header(const std::string& msg = "") {
  auto& os_ = std::cout;
  if (msg != "") {
    os_ << std::setw(12) << std::left << msg << std::endl;
  }
  os_ << std::setw(8) << std::right << "N";
  os_ << std::setw(12) << std::right << "GF/s ijk";
  os_ << std::setw(12) << std::right << "GF/s ikj";
  os_ << std::setw(12) << std::right << "GF/s jik";
  os_ << std::setw(12) << std::right << "GF/s jki";
  os_ << std::setw(12) << std::right << "GF/s kij";
  os_ << std::setw(12) << std::right << "GF/s kji";
  os_ << std::endl;
}


double Gflops_sec(size_t N, size_t trials, double msec) {
  double Gflops = static_cast<double>(trials)*(2.0 * N * N * N)/1.e9;
  double sec = msec / 1.e3;
  if (sec == 0) {
    return 0;
  }
  return Gflops/sec;
}


void log(size_t N, size_t ntrials, std::vector<double> ms_times) {
  auto& os_ = std::cout;
  os_ << std::setw(8) << std::right << N;

  for (size_t i = 0; i < ms_times.size(); ++i) {
    os_ << std::setw(12) << std::right << Gflops_sec(N, ntrials, ms_times[i]);
  }
  os_ << std::endl;
}


size_t num_trials(size_t N) {
  // 1024 * 1024 * 1024 = 1S = trials * 
  double N_1k = std::ceil(175.0 / static_cast<double>(N));
  if (N_1k < 256) {
    N_1k *= 2;
  }
  if (N_1k < 32) {
    N_1k *= 2;
  }
  return 2 + static_cast<size_t>(N_1k * N_1k * N_1k);
}


int main(int argc, char* argv[]) {
  size_t N_max = 256;
  if (argc >= 2) {
    N_max = std::stol(argv[1]);
  }

  header();

  Timer t;
  std::vector<double> ms_times(6);

  for (size_t size = 8; size <= N_max; size *= 2) {
    Matrix A(size, size), B(size, size), C(size, size);
    randomize(A); randomize(B); randomize(C); 

    size_t ntrials = num_trials(size);

    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult_ijk(A, B, C);
    }
    t.stop();
    ms_times[0] = t.elapsed();
    
    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult_ikj(A, B, C);
    }
    t.stop();
    ms_times[1] = t.elapsed();
    
    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult_jik(A, B, C);
    }
    t.stop();
    ms_times[2] = t.elapsed();

    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult_jki(A, B, C);
    }
    t.stop();
    ms_times[3] = t.elapsed();
    
    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult_kij(A, B, C);
    }
    t.stop();
    ms_times[4] = t.elapsed();

    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult_kji(A, B, C);
    }
    t.stop();
    ms_times[5] = t.elapsed();
    
    log(size, ntrials, ms_times);
  }


  return 0;
}
