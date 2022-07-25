
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

#include "Timer.hpp"
#include "kernels.hpp"

void header(const std::string& msg) {
  auto& os_ = std::cout;
  os_ << std::setw(12) << std::left << msg << std::endl;
  os_ << std::setw(12) << std::right << "bytes/elt";
  os_ << std::setw(12) << std::right << "#elts";
  os_ << std::setw(12) << std::right << "res_bytes";
  os_ << std::setw(10) << std::right << "ntrials";
  os_ << std::setw(15) << std::right << "usecs";
  os_ << std::setw(15) << std::right << "ttl_bytes";
  os_ << std::setw(15) << std::right << "bytes/sec";
  os_ << std::endl;
}


void log(size_t sz, size_t num_elts, size_t rss, size_t ntrials, double seconds, size_t total_bytes) {
  auto& os_ = std::cout;
  os_ << std::setw(12) << std::right << sz;
  os_ << std::setw(12) << std::right << num_elts;
  os_ << std::setw(12) << std::right << rss;
  os_ << std::setw(10) << std::right << ntrials;
  os_ << std::setw(15) << std::right << seconds * 1000000;
  os_ << std::setw(15) << std::right << total_bytes;
  if (seconds != 0) {
    os_ << std::setw(15) << std::right << static_cast<double>(total_bytes) / seconds;
  } else {
    os_ << std::setw(15) << std::right << 0;
  }
  os_ << std::endl;
}


double bw_r(size_t nbytes, size_t ntrials) {
  size_t nsize = nbytes / sizeof(double);
  if (nsize == 0) {
    nsize = 1;
  }
  std::vector<double> A(nsize, 2.0), B(nsize, 1.0);

  double a = 867.5309;

  Timer t;
  t.start();
  for (size_t j = 0; j < ntrials; ++j) {
    for (size_t i = 0; i < A.size(); ++i) {
      a = A[i];
    }
  }
  t.stop();

  double seconds = (double)t.elapsed() / 1.e3;
  size_t total_bytes           = ntrials * nbytes;
  log(sizeof(double), nsize, nbytes, ntrials, seconds, total_bytes);

  return a;
}


double bw_w(size_t nbytes, size_t ntrials) {
  size_t nsize = nbytes / sizeof(double);
  if (nsize == 0) {
    nsize = 1;
  }
  std::vector<double> A(nsize, 2.0), B(nsize, 1.0);

  double a = 867.5309;

  Timer t;
  t.start();
  for (size_t j = 0; j < ntrials; ++j) {
    for (size_t i = 0; i < A.size(); ++i) {
      A[i] = a;
    }
  }
  t.stop();

  double seconds = (double)t.elapsed() / 1.e3;
  size_t total_bytes           = ntrials * nbytes;
  log(sizeof(double), nsize, nbytes, ntrials, seconds, total_bytes);

  return A[0];
}


double bw_rw(size_t nbytes, size_t ntrials) {
  size_t nsize = nbytes / (2 * sizeof(double));
  if (nsize == 0) {
    nsize = 1;
  }
  std::vector<double> A(nsize, 2.0), B(nsize, 1.0);

  Timer t;
  t.start();
  for (size_t j = 0; j < ntrials; ++j) {
    for (size_t i = 0; i < A.size(); ++i) {
      B[i] = A[i];
    }
  }
  t.stop();

  double seconds = (double)t.elapsed() / 1.e3;
  size_t total_bytes           = ntrials * nbytes;
  log(sizeof(double), nsize, nbytes, ntrials, seconds, total_bytes);

  return B[0];
}


size_t ntrials(size_t nbytes) {
  size_t trials = 1 + (1024UL * 1024 * 1024 * 2) / (nbytes);
  if (nbytes < 1024*1024) {
    trials *= 2;
  }
  if (nbytes < 32*1024) {
    trials *= 2;
  }
  return trials;
}


int main(int argc, char* argv[]) {
  size_t nbytes = 134217728;
  if (argc >= 2) {
    nbytes = std::stol(argv[1]);
  }

  header("read");
  for (size_t bytes = 128; bytes <= nbytes; bytes *=2) {
    bw_r(bytes, ntrials(bytes));
  }
  header("write");
  for (size_t bytes = 128; bytes <= nbytes; bytes *=2) {
    bw_w(bytes, ntrials(bytes));
  }
  header("read/write");
  for (size_t bytes = 128; bytes <= nbytes; bytes *=2) {
    bw_rw(bytes, ntrials(bytes));
  }

  return 0;
}
