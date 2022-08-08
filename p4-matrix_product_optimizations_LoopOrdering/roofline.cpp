
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

#include "Timer.hpp"
#include "kernels.hpp"

void header(const std::string& msg = "") {
  auto& os_ = std::cout;
  os_ << std::setw(12) << std::left << msg << std::endl;
  os_ << std::setw(12) << std::right << "kernel sz";
  os_ << std::setw(12) << std::right << "res_bytes";
  os_ << std::setw(10) << std::right << "ntrials";
  os_ << std::setw(15) << std::right << "usecs";
  os_ << std::setw(15) << std::right << "ttl_bytes";
  os_ << std::setw(18) << std::right << "ttl_flops";
  os_ << std::setw(15) << std::right << "intensity";
  os_ << std::setw(15) << std::right << "flops/sec";
  os_ << std::setw(15) << std::right << "bytes/sec";
  os_ << std::endl;
}


void log(size_t sz, size_t resident_bytes, size_t ntrials, double seconds, size_t total_bytes, size_t total_flops) {
  auto& os_ = std::cout;
  os_ << std::setw(12) << std::right << sz;
  os_ << std::setw(12) << std::right << resident_bytes;
  os_ << std::setw(10) << std::right << ntrials;
  os_ << std::setw(15) << std::right << seconds * 1000000;
  os_ << std::setw(15) << std::right << total_bytes;
  os_ << std::setw(18) << std::right << total_flops;
  os_ << std::setw(15) << std::right << static_cast<double>(total_flops) / static_cast<double>(total_bytes);

  if (seconds != 0) {
    os_ << std::setw(15) << std::right << static_cast<double>(total_flops) / seconds;
  } else {
    os_ << std::setw(15) << std::right << 0;
  }
  if (seconds != 0) {
    os_ << std::setw(15) << std::right << static_cast<double>(total_bytes) / seconds;
  } else {
    os_ << std::setw(15) << std::right << 0;
  }
  os_ << std::endl;
}

int main(int argc, char* argv[]) {

  size_t nbytes = 134217728;
  if (argc >= 2) {
    nbytes = std::stol(argv[1]);
  }
  size_t nsize = nbytes/8;
  if (nsize == 0) {
    nsize = 1;
  }


  header();
  for (size_t kernel_size = 2; kernel_size <= 64; kernel_size *= 2) {
    // 1B  ~ 1s : kernel * trial * size ; trial = 1B / (kernel*size)
    size_t trial = 3 + (1024UL * 1024 * 1024 *8) / (kernel_size * nsize);

    std::vector<double> A(nsize, 1.0);

    Timer t0;

    switch (kernel_size) {
      case 2:
        t0.start();
        kernel_02(A, trial);
        t0.stop();
        break;
      case 4:
        t0.start();
        kernel_04(A, trial);
        t0.stop();
        break;
      case 8:
        t0.start();
        kernel_08(A, trial);
        t0.stop();
        break;
      case 16:
        t0.start();
        kernel_16(A, trial);
        t0.stop();
        break;
      case 32:
        t0.start();
        kernel_32(A, trial);
        t0.stop();
        break;
      case 64:
        t0.start();
        kernel_64(A, trial);
        t0.stop();
        break;
      case 128:
        t0.start();
        kernel_128(A, trial);
        t0.stop();
        break;
      default:
        std::cout << "No such kernel " << kernel_size << std::endl;
    }

    double seconds = (double)t0.elapsed() / 1.e3;

    size_t bytes_per_elem        = sizeof(A[0]);
    size_t mem_accesses_per_elem = 2;
    size_t working_set_size      = nsize;
    size_t total_bytes           = trial * working_set_size * bytes_per_elem * mem_accesses_per_elem;
    size_t total_flops           = trial * working_set_size * kernel_size;

    log(kernel_size, working_set_size * bytes_per_elem, trial, seconds, total_bytes, total_flops);
  }

  return 0;
}
