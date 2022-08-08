
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/sequence.h>

#include "Timer.hpp"
#include <iostream>
#include <string>

#include "helper_cuda.h"

template<typename T>
struct add {
  __host__ __device__ T operator()(const T& x, const T& y) const { return 3.14159 * x + y; }
};

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
    thrust::device_vector<float> X(N), Y(N);
    t0.start();
    checkCudaErrors(cudaDeviceSynchronize());
    thrust::transform(X.begin(), X.end(), Y.begin(), Y.begin(), [=]__host__ __device__(const float x, const float y) { return 3.14159*x + y; });
    checkCudaErrors(cudaDeviceSynchronize());
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

  DEF_TIMER(host_vector); START_TIMER(host_vector);
  thrust::host_vector<float>   x(N), y(N);
  STOP_TIMER(host_vector);
  DEF_TIMER(device_vector); START_TIMER(device_vector);
  thrust::device_vector<float> X(N), Y(N);
  STOP_TIMER(device_vector);

  for (int i = 0; i < N; i++)
    y[i] = 2.0 * (x[i] = 1.0f);
  
  DEF_TIMER(copy);    START_TIMER(copy);
  thrust::copy(x.begin(), x.end(), X.begin());
  thrust::copy(y.begin(), y.end(), Y.begin());
  STOP_TIMER(copy);

  size_t num_trips = 50.0 * find_10ms_size() / static_cast<double>(N);
  num_trips = std::max<size_t>(num_trips, 5);
  
  double a = 3.14159;

  DEF_TIMER(thrust_call); START_TIMER(thrust_call);
  cudaDeviceSynchronize();
  for (size_t i = 0; i < num_trips; ++i) {
    thrust::transform(X.begin(), X.end(), Y.begin(), Y.begin(), [=]__host__ __device__(const float x, const float y) { return a*x + y; });
  
    cudaDeviceSynchronize();
  }
  STOP_TIMER(thrust_call);

  double gflops = 2.0 * num_trips * N / 1.e9;
  double gflops_sec = gflops / (t_thrust_call.elapsed() * 1.e-3);
  std::cout << "# gflops / sec [ madd ]: " << gflops_sec << std::endl;

  DEF_TIMER(copy_back); START_TIMER(copy_back);
  thrust::copy(Y.begin(), Y.end(), y.begin());
  STOP_TIMER(copy_back);

  return 0;
}
