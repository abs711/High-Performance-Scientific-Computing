

#include "Timer.hpp"
#include <iostream>
#include <string>

#include "helper_cuda.h"

__global__ void madd(int n, float a, float* x, float* y) {
  for (int i = 0; i < n; i++)
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
    float *x, *y;
    size_t N = size;

    cudaMallocManaged(&x, N * sizeof(float));
    cudaMallocManaged(&y, N * sizeof(float));
    t0.start();
    checkCudaErrors(cudaDeviceSynchronize());
    madd<<<1, 1>>>(N, 3.14159, x, y);
    checkCudaErrors(cudaDeviceSynchronize());
    t0.stop();
    cudaFree(x);
    cudaFree(y);
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

  float *x = nullptr, *y = nullptr;

  DEF_TIMER(cuda_malloc); START_TIMER(cuda_malloc);
  cudaMallocManaged(&x, N * sizeof(float));
  cudaMallocManaged(&y, N * sizeof(float));
  STOP_TIMER(cuda_malloc);

  size_t num_trips = 25.0 * find_10ms_size() / static_cast<double>(N);
  num_trips = std::max<size_t>(num_trips, 5);
  
  for (int i = 0; i < N; i++)
    y[i] = 2.0 * (x[i] = 1.0f);
  
  DEF_TIMER(cuda_call);
  START_TIMER(cuda_call);
  for (size_t i = 0; i < num_trips; ++i) {
    madd<<<1, 1>>>(N, 3.1459, x, y);
  }
  STOP_TIMER(cuda_call);

  double gflops = 2.0 * num_trips * N / 1.e9;
  double gflops_sec = gflops / (t_cuda_call.elapsed() * 1.e-3);
  std::cout << "# gflops / sec [ madd ]: " << gflops_sec << std::endl;

  DEF_TIMER(cuda_free); START_TIMER(cuda_free);
  cudaFree(x);
  cudaFree(y);
  STOP_TIMER(cuda_free);

  return 0;
}
