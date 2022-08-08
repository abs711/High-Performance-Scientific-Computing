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

#include "Matrix.hpp"
#include "amath583.hpp"
#include <cstddef>

TEST_CASE("Matrices can be created and initialized", "[Matrix]") {
  Matrix A(40, 50);
  REQUIRE(A.num_rows() == 40);
  REQUIRE(A.num_cols() == 50);

  SECTION("test initial values") {
    for (size_t i = 0; i < 40; ++i) {
      for (size_t j = 0; j < 50; ++j) {
        REQUIRE(A(i, j) == 0.0);
      }
    }
  }

  SECTION("test filling values") {
    for (size_t i = 0; i < 40; ++i) {
      for (size_t j = 0; j < 50; ++j) {
        A(i, j) = 50 - i - j;
      }
    }
    for (size_t i = 0; i < 40; ++i) {
      for (size_t j = 0; j < 50; ++j) {
        REQUIRE(A(i, j) == 50 - i - j);
      }
    }
  }
}

TEST_CASE("Take norms of a Matrix", "[Norms]") {
  SECTION("one_norm") {
    Matrix A(40, 50);
    REQUIRE(one_norm(A) == 0.0);
    A(0, 0) = A(0, 1) = A(0, 2) = A(0, 3) = 1.0;
    REQUIRE(one_norm(A) == 1.0);
  }
  SECTION("one_norm") {
    Matrix A(40, 50);
    A(0, 0) = A(1, 0) = A(2, 0) = A(3, 0) = 1.0;
    REQUIRE(one_norm(A) == 4.0);
  }
  SECTION("inf_norm") {
    Matrix A(40, 50);
    REQUIRE(inf_norm(A) == 0.0);
    A(0, 0) = A(0, 1) = A(0, 2) = A(0, 3) = 1.0;
    REQUIRE(inf_norm(A) == 4.0);
  }
  SECTION("inf_norm") {
    Matrix A(40, 50);
    A(0, 0) = A(1, 0) = A(2, 0) = A(3, 0) = 1.0;
    REQUIRE(inf_norm(A) == 1.0);
  }
}
