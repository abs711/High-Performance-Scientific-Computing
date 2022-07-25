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

#include "norms.hpp"

template <typename Function>
void do_test(Function&& f, size_t parts) {
  SECTION("zero") {
    omp_set_num_threads(parts);
    Vector x(10);
    zeroize(x);
    REQUIRE(f(x) == 0.0);
    x(0) = 1;
    REQUIRE(f(x) == 1.0);
    x(0) = 0;
    REQUIRE(f(x) == 0.0);
    x(1) = 1;
    REQUIRE(f(x) == 1.0);
    x(1) = 0;
    REQUIRE(f(x) == 0.0);
    x(9) = 1;
    REQUIRE(f(x) == 1.0);
    x(9) = 0;
    x(1) = 1;
    x(2) = 1;
    x(3) = 1;
    x(4) = 1;
    REQUIRE(f(x) == 2.0);
  }
  SECTION("1.1") {
    Vector x(1);
    x(0) = 1.0;
    REQUIRE(f(x) == 1.0);
  }
  SECTION("one") {
    Vector x(9);
    unitize(x);
    REQUIRE(std::abs(f(x) - 3.0) < 1.e-12);
  }
  SECTION("rand") {
    Vector x(1024 * 1024);
    randomize(x);
    REQUIRE(std::abs(two_norm(x) - f(x)) < 1.e-12 * two_norm(x));
  }
}

TEST_CASE("sequential two norm", "[norm_seq") {
  do_test(norm_seq, 1);
  for (size_t i = 1; i < 8; i *= 2) {
    do_test(norm_seq, i);
  }
}

TEST_CASE("OMP parfor norm", "[norm_parfor") {
  do_test(norm_parfor, 1);
  for (size_t i = 1; i < 8; i *= 2) {
    do_test(norm_parfor, i);
  }
}

TEST_CASE("OMP block reduction norm", "[norm_block_reduction") {
  do_test(norm_block_reduction, 1);
  for (size_t i = 1; i < 8; i *= 2) {
    do_test(norm_block_reduction, i);
  }
}

TEST_CASE("OMP block critical norm", "[norm_block_critical") {
  do_test(norm_block_critical, 1);
  for (size_t i = 1; i < 8; i *= 2) {
    do_test(norm_block_critical, i);
  }
}

TEST_CASE("OMP cyclic reduction norm", "[norm_cyclic_reduction") {
  do_test(norm_cyclic_reduction, 1);
  for (size_t i = 1; i < 8; i *= 2) {
    do_test(norm_cyclic_reduction, i);
  }
}

TEST_CASE("OMP cyclic critical norm", "[norm_cyclic_critical") {
  do_test(norm_cyclic_critical, 1);
  for (size_t i = 1; i < 8; i *= 2) {
    do_test(norm_cyclic_critical, i);
  }
}
