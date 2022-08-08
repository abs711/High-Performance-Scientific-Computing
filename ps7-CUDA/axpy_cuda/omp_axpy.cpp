

#include "Timer.hpp"
#include <iostream>
#include <string>

#include <vector>
#include <omp.h>
#include <cmath>

template <typename T>
void madd(T a, const std::vector<T>& x, std::vector<T>& y) {
#pragma omp parallel for
  for (size_t i = 0; i < x.size(); i++)
    y[i] = a * x[i] + y[i];
}

size_t frob(size_t size) {
  size_t r = 0;
  while(size >>= 1) {
    ++r;
  }
  return 1 << r;
}

size_t find_10ms_size () {
  size_t size = 4;
  Timer t0;

  for (; size < 4UL * 1024 * 1024 * 1024; size *= 2) {
    size_t N = size;
    std::vector<float> x(N), y(N);
    t0.start();
    madd(3.14150f, x, y);
    t0.stop();
    if (t0.elapsed() >= 10.0) {
      break;
    }
  }

  double rat = std::max<double>(1.0, std::ceil(t0.elapsed()/10.0));
  size /= static_cast<size_t>(rat);

  return frob(size);
}


int main(int argc, char* argv[]) {

  size_t N = 1 << 16;

  if (argc >= 2) {
    size_t nn = std::stol(argv[1]);
    N = frob(1 << nn);
  }

  DEF_TIMER(vector); START_TIMER(vector);
  std::vector<float> x(N), y(N);
  STOP_TIMER(vector);

#pragma omp parallel for
  for (size_t i = 0; i < N; i++)
    y[i] = 2.0 * (x[i] = 1.0f);
  
  size_t num_trips = 50.0 * find_10ms_size() / static_cast<double>(N);
  num_trips = std::max<size_t>(num_trips, 5);
  
  float a = 3.14159;

  DEF_TIMER(omp_call); START_TIMER(omp_call);
  for (size_t i = 0; i < num_trips; ++i) {
    madd(a, x, y);
  }
  STOP_TIMER(omp_call);

  double gflops = 2.0 * num_trips * N / 1.e9;
  double gflops_sec = gflops / (t_omp_call.elapsed() * 1.e-3);
  std::cout << "# gflops / sec [ madd ]: " << gflops_sec << std::endl;

  return 0;
}
