//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#define CATCH_CONFIG_MAIN    // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "COOMatrix.hpp"
#include "CSRMatrix.hpp"
#include "Vector.hpp"
#include "amath583.hpp"
#include "amath583IO.hpp"
#include "amath583sparse.hpp"
#include <cstddef>

#include "CSCMatrix.hpp"

#ifdef __583
#include "AOSMatrix.hpp"
#endif

template <class Mat>
void do_eye_test(const Mat& A) {
  Matrix B(5, 10);
  randomize(B);
  Matrix C = mult(A, B);
  for (size_t i = 0; i < 5; ++i) {
    for (size_t j = 0; j < 10; ++j) {
      REQUIRE(B(i, j) != 0.0);
      REQUIRE(C(i, j) == B(i, j));
    }
  }
}

template <class Mat>
void do_sherman_test(const Mat& A) {
  COOMatrix ACOO = read_coomatrix("data/sherman4.mtx");
  Matrix B(1104, 17);
  randomize(B);
  Matrix C = mult(A, B);
  Matrix D = mult(ACOO, B);
  REQUIRE (f_norm(C-D) < 1.e-12*f_norm(C));
}


TEST_CASE("Coordinate Matrix", "[COO]") {

  SECTION("test identity") {
    COOMatrix A = read_coomatrix("data/eye5.mmio");
    do_eye_test(A);
    do_sherman_test(read_coomatrix("data/sherman4.mtx"));
  }
}

TEST_CASE("Compressed Sparse Row Matrix", "[CSR]") {

  SECTION("test identity") {
    CSRMatrix A = read_csrmatrix("data/eye5.mmio");
    do_eye_test(A);
    do_sherman_test(read_csrmatrix("data/sherman4.mtx"));
  }
}

TEST_CASE("Compressed Sparse Column Matrix", "[CSC]") {

  SECTION("test identity") {
    CSCMatrix A = read_cscmatrix("data/eye5.mmio");
    do_eye_test(A);
    do_sherman_test(read_cscmatrix("data/sherman4.mtx"));
  }
}


#ifdef __583
TEST_CASE("Array of Structs Matrix", "[AOS]") {

  SECTION("test identity") {
    AOSMatrix A = read_aosmatrix("data/eye5.mmio");
    do_eye_test(A);
    do_sherman_test(read_aosmatrix("data/sherman4.mtx"));
  }
}
#endif
