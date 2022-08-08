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

#include "mkl_cblas.h"

auto gen_covariance(const std::vector<Vector>& z) {
  size_t sz = z[0].num_rows();
  Matrix F(sz, z.size());
  //Matrix Ft(z.size(),sz);
  Matrix C(sz, sz);

  //Matrix A(2,2);
  //Matrix B(2,2);
  //Matrix R(2,2);

 
  //A(0,0) = 1; A(0,1) = 1; A(1,0) = 0; A(1,1) = 1;
  //B(0,0) = 1; B(0,1) = 0; B(1,0) = 1; B(1,1) = 1;

  //cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 2, 2, 2, 1, &A(0,0), 2, &B(0,0), 2, 0, &R(0,0), 2);	  
		  
  //std::cout << "||R1|| = " << R(0,0) <<","<< R(0,1) << std::endl;
  //std::cout << "||R2|| = " << R(1,0) <<","<< R(1,1) << std::endl;

  // Replace me with call to cblas_dgemm
  for (size_t k = 0; k < z.size(); ++k) {   
      for (size_t i = 0; i < C.num_rows(); ++i) {
       F(i, k) = z[k](i);     
       //Ft(k,i) = z[k](i); 
      }
    }

 double alpha = 1;
 double beta = 0; 

  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, sz, sz, z.size(), alpha, &F(0,0), z.size(), &F(0,0), z.size(), beta, &C(0,0), sz);
  

 // Normalize
 for (size_t i = 0; i < C.num_rows(); ++i) {
   for (size_t j = 0; j < C.num_cols(); ++j) {
     C(i,j) = C(i,j) / z.size();
   }
  }

  return C;
}

const char* tag = "dgemm";

#include "main.hpp"
