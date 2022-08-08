//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_KERNELS_HPP
#define AMATH583_KERNELS_HPP

void kernel_02(std::vector<double>& A, size_t ntrials) {
  double alpha = 0.5;
  for (size_t j = 0; j < ntrials; ++j) {
    for (size_t i = 0; i < A.size(); ++i) {
      double beta = 0.8;
      ((beta) = (beta) * (A[i]) + (alpha));
      A[i] = beta;
    }
    alpha = alpha * (1 - 1e-8);
  }
}

void kernel_04(std::vector<double>& A, size_t ntrials) {
  double alpha = 0.5;
  for (size_t j = 0; j < ntrials; ++j) {
    for (size_t i = 0; i < A.size(); ++i) {
      double beta = 0.8;
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      A[i] = beta;
    }
    alpha = alpha * (1 - 1e-8);
  }
}

void kernel_08(std::vector<double>& A, size_t ntrials) {
  double alpha = 0.5;
  for (size_t j = 0; j < ntrials; ++j) {
    for (size_t i = 0; i < A.size(); ++i) {
      double beta = 0.8;
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      A[i] = beta;
    }
    alpha = alpha * (1 - 1e-8);
  }
}

void kernel_16(std::vector<double>& A, size_t ntrials) {
  double alpha = 0.5;
  for (size_t j = 0; j < ntrials; ++j) {
    for (size_t i = 0; i < A.size(); ++i) {
      double beta = 0.8;
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      A[i] = beta;
    }
    alpha = alpha * (1 - 1e-8);
  }
}

void kernel_32(std::vector<double>& A, size_t ntrials) {
  double alpha = 0.5;
  for (size_t j = 0; j < ntrials; ++j) {
    for (size_t i = 0; i < A.size(); ++i) {
      double beta = 0.8;
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      A[i] = beta;
    }
    alpha = alpha * (1 - 1e-8);
  }
}

void kernel_64(std::vector<double>& A, size_t ntrials) {
  double alpha = 0.5;
  for (size_t j = 0; j < ntrials; ++j) {
    for (size_t i = 0; i < A.size(); ++i) {
      double beta = 0.8;
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      A[i] = beta;
    }
    alpha = alpha * (1 - 1e-8);
  }
}

void kernel_128(std::vector<double>& A, size_t ntrials) {
  double alpha = 0.5;
  for (size_t j = 0; j < ntrials; ++j) {
    for (size_t i = 0; i < A.size(); ++i) {
      double beta = 0.8;
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      ((beta) = (beta) * (A[i]) + (alpha));
      A[i] = beta;
    }
    alpha = alpha * (1 - 1e-8);
  }
}

#endif    // AMATH583_KERNELS_HPP
