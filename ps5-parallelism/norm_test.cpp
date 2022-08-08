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

#include "Vector.hpp"
#include "amath583.hpp"
#include <cstddef>

TEST_CASE("two norm", "[two_norm]") {
  SECTION("zero") {
    Vector x(10);
    zeroize(x);
    REQUIRE(two_norm(x) == 0.0);
    x(0) = 1;
    REQUIRE(two_norm(x) == 1.0);
    x(0) = 0;
    REQUIRE(two_norm(x) == 0.0);
    x(1) = 1;
    REQUIRE(two_norm(x) == 1.0);
    x(1) = 0;
    REQUIRE(two_norm(x) == 0.0);
    x(9) = 1;
    REQUIRE(two_norm(x) == 1.0);
    x(9) = 0;
    x(1) = 1;
    x(2) = 1;
    x(3) = 1;
    x(4) = 1;
    REQUIRE(two_norm(x) == 2.0);
  }
  SECTION("1.1") {
    Vector x(1);
    x(0) = 1.0;
    REQUIRE(two_norm(x) == 1.0);
  }
  SECTION("one") {
    Vector x(9);
    unitize(x);
    REQUIRE(std::abs(two_norm(x) - 3.0) < 1.e-14);
  }
}

TEST_CASE("two norm r", "[two_norm_r]") {
  SECTION("zero") {
    Vector x(10);
    zeroize(x);
    REQUIRE(two_norm_r(x) == 0.0);
    x(0) = 1;
    REQUIRE(two_norm_r(x) == 1.0);
    x(0) = 0;
    REQUIRE(two_norm_r(x) == 0.0);
    x(1) = 1;
    REQUIRE(two_norm_r(x) == 1.0);
    x(1) = 0;
    REQUIRE(two_norm_r(x) == 0.0);
    x(9) = 1;
    REQUIRE(two_norm_r(x) == 1.0);
    x(9) = 0;
    x(1) = 1;
    x(2) = 1;
    x(3) = 1;
    x(4) = 1;
    REQUIRE(two_norm_r(x) == 2.0);
  }
  SECTION("1.1") {
    Vector x(1);
    x(0) = 1.0;
    REQUIRE(two_norm_r(x) == 1.0);
  }
  SECTION("one") {
    Vector x(9);
    unitize(x);
    REQUIRE(std::abs(two_norm_r(x) - 3.0) < 1.e-14);
  }
}

TEST_CASE("two norm s", "[two_norm_s]") {
  SECTION("zero") {
    Vector x(10);
    zeroize(x);
    REQUIRE(two_norm_s(x) == 0.0);
    x(0) = 1;
    REQUIRE(two_norm_s(x) == 1.0);
    x(0) = 0;
    REQUIRE(two_norm_s(x) == 0.0);
    x(1) = 1;
    REQUIRE(two_norm_s(x) == 1.0);
    x(1) = 0;
    REQUIRE(two_norm_s(x) == 0.0);
    x(9) = 1;
    REQUIRE(two_norm_s(x) == 1.0);
    x(9) = 0;
    x(1) = 1;
    x(2) = 1;
    x(3) = 1;
    x(4) = 1;
    REQUIRE(two_norm_s(x) == 2.0);
  }
  SECTION("1.1") {
    Vector x(1);
    x(0) = 1.0;
    REQUIRE(two_norm_s(x) == 1.0);
  }
  SECTION("one") {
    Vector x(9);
    unitize(x);
    REQUIRE(std::abs(two_norm_s(x) - 3.0) < 1.e-14);
  }
}
