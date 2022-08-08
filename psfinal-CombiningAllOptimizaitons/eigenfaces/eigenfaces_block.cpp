//
// This file is part of the course materials for AMATH 483/583 at the University of Washington
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "amath583.hpp"
#include "omp.h"
// Parallelize, optimize, and cache block me
auto gen_covariance(const std::vector<Vector>& z) {
  size_t sz = z[0].num_rows();
  Matrix C(sz, sz);
  
#pragma omp parallel 
  {

  size_t tid = omp_get_thread_num();
  size_t parts = omp_get_num_threads();
  size_t blocksize = C.num_rows()/parts;
  size_t begin = tid*blocksize;
  size_t end = (tid+1)*blocksize;

  if (tid == parts - 1) {
     end = C.num_rows();
  }	    

  //size_t blocksize = 32;
  //for (size_t ii = 0; ii < C.num_rows(); ii += blocksize) {
  //for (size_t jj = 0; jj < C.num_cols(); jj += blocksize) {  

  //size_t stop_i  = std::min(ii + blocksize, C.num_rows());
  //size_t stop_j  = std::min(jj + blocksize, C.num_cols());	

  for (size_t k = 0; k < z.size(); ++k) {       
      #pragma omp parallel for     
      for (size_t i = begin; i < end; ++i) {
        double t = z[k](i);       
        for (size_t j = 0; j < C.num_cols(); ++j) {                 	          
          C(i,j) +=  t*z[k](j);      	
        }
      }
  }



}
//  }
//  }


  // Normalize
  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      C(i,j) = C(i,j) / z.size();
    }
  }
  
  return C;
  }


const char* tag = "block";

#include "main.hpp"
