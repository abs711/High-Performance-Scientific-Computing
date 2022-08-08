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

TEST_CASE("Dot product", "[Dot]") {
  Vector x(50), y(50);
  REQUIRE(x.num_rows() == 50);
  REQUIRE(y.num_rows() == 50);

  SECTION("test initial values") {
    for (size_t i = 0; i < 50; ++i) {
      x(i) = y(i) = 1.0;
    }
    for (size_t i = 0; i < 50; ++i) {
      REQUIRE((1.0 == x(i) && 1.0 == y(i)));
    }
    REQUIRE(dot(x, y) == 50);
    for (size_t i = 0; i < 50; ++i) {
      x(i) = y(i) = 2.0;
    }
    for (size_t i = 0; i < 50; ++i) {
      REQUIRE((2.0 == x(i) && 2.0 == y(i)));
    }
    REQUIRE(dot(x, y) == 200);
  }
}
