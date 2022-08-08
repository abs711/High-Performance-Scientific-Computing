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

#include "rnorm.hpp"

template <typename Function>
void do_test(Function&& f, size_t parts) {
  SECTION("zero") {
    Vector x(10);
    zeroize(x);
    REQUIRE(f(x, parts) == 0.0);
    x(0) = 1;
    REQUIRE(f(x, parts) == 1.0);
    x(0) = 0;
    REQUIRE(f(x, parts) == 0.0);
    x(1) = 1;
    REQUIRE(f(x, parts) == 1.0);
    x(1) = 0;
    REQUIRE(f(x, parts) == 0.0);
    x(9) = 1;
    REQUIRE(f(x, parts) == 1.0);
    x(9) = 0;
    x(1) = 1;
    x(2) = 1;
    x(3) = 1;
    x(4) = 1;
    REQUIRE(f(x, parts) == 2.0);
  }
  SECTION("1.1") {
    Vector x(1);
    x(0) = 1.0;
    REQUIRE(f(x, parts) == 1.0);
  }
  SECTION("one") {
    Vector x(9);
    unitize(x);
    REQUIRE(std::abs(f(x, parts) - 3.0) < 1.e-14);
  }
  SECTION("rand") {
    Vector x(1024 * 1024);
    randomize(x);
    REQUIRE(std::abs(two_norm(x) - f(x, parts)) < 1.e-14 * two_norm(x));
  }
}

TEST_CASE("two norm", "[two_norm]") {
  do_test(recursive_two_norm_a, 1);
  for (size_t i = 1; i <= 3; ++i) {
    do_test(recursive_two_norm_a, i);
  }
  do_test(recursive_two_norm_b, 1);
  for (size_t i = 1; i <= 3; ++i) {
    do_test(recursive_two_norm_b, i);
  }
}
