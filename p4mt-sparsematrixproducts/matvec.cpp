
#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "COOMatrix.hpp"
#include "CSRMatrix.hpp"
#include "CSCMatrix.hpp"

#ifdef __583
#include "AOSMatrix.hpp"
#endif

#include "Vector.hpp"
#include "amath583.hpp"
#include "amath583sparse.hpp"
#include "Timer.hpp"


void header(const std::string& msg = "") {
  auto& os_ = std::cout;
  if (msg != "") {
    os_ << std::setw(12) << std::left << msg << std::endl;
  }
  os_ << std::setw(8) << std::right << "N(Grid)";
  os_ << std::setw(10) << std::right << "N(Matrix)";
  os_ << std::setw(12) << std::right << "NNZ";
  os_ << std::setw(12) << std::right << "COO";
  os_ << std::setw(12) << std::right << "COO^T";
  os_ << std::setw(12) << std::right << "CSR";
  os_ << std::setw(12) << std::right << "CSR^T";
  os_ << std::setw(12) << std::right << "CSC";
  os_ << std::setw(12) << std::right << "CSC^T";

#ifdef __583
  os_ << std::setw(12) << std::right << "AOS";
  os_ << std::setw(12) << std::right << "AOS^T";
#endif

  os_ << std::endl;
}


double Gflops_sec(size_t nnz, size_t trials, double msec) {
  double Gflops = static_cast<double>(trials)*(2.0 * nnz)/1.e9;
  double sec = msec / 1.e3;
  if (sec == 0) {
    return 0;
  }
  return Gflops/sec;
}


void log(size_t n, size_t nnz, size_t ntrials, std::vector<double> ms_times) {
  auto& os_ = std::cout;
  os_ << std::setw(8) << std::right << n;
  os_ << std::setw(10) << std::right << n*n;
  os_ << std::setw(12) << std::right << nnz;

  for (size_t i = 0; i < ms_times.size(); ++i) {
    os_ << std::setw(12) << std::right << Gflops_sec(nnz, ntrials, ms_times[i]);
  }
  os_ << std::endl;
}


size_t num_trials(size_t nnz) {
  // trials*nnz/1G = 1S => trials = 1G/nnz
  double N_1k = std::ceil(1E8 / static_cast<double>(nnz));

  return 3 + static_cast<size_t>(N_1k);
}


int main(int argc, char* argv[]) {
  size_t points_max = 2048;
  if (argc >= 2) {
    points_max = std::stol(argv[1]);
  }

  header();

  Timer t;

#ifdef __583
  std::vector<double> ms_times(8);
#else
  std::vector<double> ms_times(6);
#endif

  for (size_t size = 64; size <= points_max; size *= 2) {
    Vector x(size*size), y(size*size);
    randomize(x); randomize(y);

    COOMatrix ACOO(size*size, size*size);
    piscetize(ACOO, size, size);

    size_t nnz = ACOO.num_nonzeros();
    size_t ntrials = num_trials(nnz);

    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult(ACOO, x, y);
    }
    t.stop();
    ms_times[0] = t.elapsed();
    
    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult(x, ACOO, y);
    }
    t.stop();
    ms_times[1] = t.elapsed();


    CSRMatrix ACSR(size*size, size*size);
    piscetize(ACSR, size, size);
    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult(ACSR, x, y);
    }
    t.stop();
    ms_times[2] = t.elapsed();
 
    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult(x, ACSR, y);
    }
    t.stop();
    ms_times[3] = t.elapsed();
    

    CSCMatrix ACSC(size*size, size*size);
    piscetize(ACSC, size, size);
    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult(ACSC, x, y);
    }
    t.stop();
    ms_times[4] = t.elapsed();

    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult(x, ACSC, y);
    }
    t.stop();
    ms_times[5] = t.elapsed();

#ifdef __583
    AOSMatrix AAOS(size*size, size*size);
    piscetize(AAOS, size, size);
    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult(AAOS, x, y);
    }
    t.stop();
    ms_times[6] = t.elapsed();

    t.start(); 
    for (size_t i = 0; i < ntrials; ++i) {
      mult(x, AAOS, y);
    }
    t.stop();
    ms_times[7] = t.elapsed();
#endif

    log(size, nnz, ntrials, ms_times);
  }


  return 0;
}
