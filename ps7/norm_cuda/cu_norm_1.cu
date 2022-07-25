// -*- c++ -*-

#include "Timer.hpp"
#include <iostream>
#include <string>

#include "helper_cuda.h"

__global__ 
void dot0(int n, float* a, float* x, float* y) {
  extern __shared__ float sdata[];

  int tid    = threadIdx.x;
  int index  = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;

  sdata[tid] = 0.0;
  for (int i = index; i < n; i += stride)
    sdata[tid] += x[i] * y[i];

  __syncthreads();

  for (size_t s = 1; s < blockDim.x; s *= 2) {
    if (tid % (2*s) == 0) {
      sdata[tid] += sdata[tid + s];
    }
    __syncthreads();
  }

  if (tid == 0) {
    a[blockIdx.x] = sdata[0];
  }
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
    float *a, *x, *y;
    size_t N = size;

    int block_size = 256;
    int num_blocks = (N + block_size - 1) / block_size;
    int shm_size = block_size * sizeof(float);
  
    cudaMallocManaged(&a, num_blocks * sizeof(float));
    cudaMallocManaged(&x, N * sizeof(float));
    cudaMallocManaged(&y, N * sizeof(float));
    t0.start();
    checkCudaErrors(cudaDeviceSynchronize());
    dot0<<<num_blocks, block_size, shm_size>>>(N, a, x, y);
    checkCudaErrors(cudaDeviceSynchronize());
    t0.stop();
    cudaFree(a);
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
  int    block_size = 256;

  if (argc >= 2) {
    size_t nn = std::stol(argv[1]);
    N = frob(1 << nn);
  }
  if (argc >= 3) {
    block_size = frob(std::stol(argv[2]));
  }
  int num_blocks = (N + block_size - 1) / block_size;
  int shm_size = block_size * sizeof(float);

  float *a = nullptr, *x = nullptr, *y = nullptr;

  DEF_TIMER(cuda_malloc); START_TIMER(cuda_malloc);
  cudaMallocManaged(&a, num_blocks * sizeof(float));
  cudaMallocManaged(&x, N * sizeof(float));
  cudaMallocManaged(&y, N * sizeof(float));

  STOP_TIMER(cuda_malloc);

  size_t num_trips = 50.0 * find_10ms_size() / static_cast<double>(N);
  num_trips = std::max<size_t>(num_trips, 5);
  
  for (int i = 0; i < N; i++)
    y[i] = 2.0 * (x[i] = 1.0f);
  
  DEF_TIMER(cuda_call);
  START_TIMER(cuda_call);
  cudaDeviceSynchronize();
  for (size_t i = 0; i < num_trips; ++i) {
    dot0<<<num_blocks, block_size, shm_size>>>(N, a, x, y);
    cudaDeviceSynchronize();
  }
  STOP_TIMER(cuda_call);

  double ans = 0.0;
  for (int i = 0; i < num_blocks; ++i) {
    ans += a[i];
  }
  std::cout << "ans " << ans << " " << 2.0 * ((double) N) << std::endl;

  double gflops = 2.0 * num_trips * N / 1.e9;
  double gflops_sec = gflops / (t_cuda_call.elapsed() * 1.e-3);
  std::cout << "# gflops / sec [ dot0 ]: " << gflops_sec << std::endl;

  DEF_TIMER(cuda_free); START_TIMER(cuda_free);
  cudaFree(a);
  cudaFree(x);
  cudaFree(y);
  STOP_TIMER(cuda_free);

  return 0;
}
