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
#include "CSCMatrix.hpp"
#include "CSRMatrix.hpp"
#include "Vector.hpp"
#include "amath583.hpp"
#include "amath583IO.hpp"
#include "amath583sparse.hpp"
#include <cstddef>

TEST_CASE("Coordinate Matrix", "[COO]") {

  SECTION("test identity") {

    COOMatrix A = read_coomatrix("../data/eye5.mmio");

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
}

TEST_CASE("Compressed Sparse Row Matrix", "[CSR]") {
  SECTION("test identity") {
    CSRMatrix A = read_csrmatrix("../data/eye5.mmio");
    Matrix    B(5, 10);
    randomize(B);
    Matrix C = mult(A, B);
    for (size_t i = 0; i < 5; ++i) {
      for (size_t j = 0; j < 10; ++j) {
        REQUIRE(B(i, j) != 0.0);
        REQUIRE(C(i, j) == B(i, j));
      }
    }
  }
  SECTION("test identity 3") {
    CSRMatrix A = read_csrmatrix("../data/eye5.mmio");
    Matrix    B(5, 3);
    randomize(B);
    Matrix C = mult(A, B);
    for (size_t i = 0; i < 5; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        REQUIRE(B(i, j) != 0.0);
        REQUIRE(C(i, j) == B(i, j));
      }
    }
  }
}

TEST_CASE("Compressed Sparse Column Matrix", "[CSC]") {
  SECTION("test identity") {
    CSCMatrix A = read_cscmatrix("../data/eye5.mmio");
    Matrix    B(5, 10);
    randomize(B);
    Matrix C = mult(A, B);
    for (size_t i = 0; i < 5; ++i) {
      for (size_t j = 0; j < 10; ++j) {
        REQUIRE(B(i, j) != 0.0);
        REQUIRE(C(i, j) == B(i, j));
      }
    }
  }
  SECTION("test identity 3") {
    CSCMatrix A = read_cscmatrix("../data/eye5.mmio");
    Matrix    B(5, 3);
    randomize(B);
    Matrix C = mult(A, B);
    for (size_t i = 0; i < 5; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        REQUIRE(B(i, j) != 0.0);
        REQUIRE(C(i, j) == B(i, j));
      }
    }
  }
}
