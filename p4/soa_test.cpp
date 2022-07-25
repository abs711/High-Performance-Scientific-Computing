//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "catch.hpp"
#include "blur.hpp"
#include "SOA_Image.hpp"

TEST_CASE("soa test", "[soa]") {

  SOA_Image A(4, 4);
  A(1, 1, 0) = 3;
  A(1, 1, 1) = 5;
  A(1, 1, 2) = 7;  

  auto B = blur_0(A);
  auto C = blur_1(A);

  REQUIRE(B(0,0,0) == 0.0);
  REQUIRE(B(3,3,0) == 0.0);
  REQUIRE(B(2,2,0) == Approx(3.0/9.0));
  REQUIRE(B(1,1,0) == Approx(3.0/9.0));
  REQUIRE(B(1,2,0) == Approx(3.0/9.0));
  REQUIRE(B(1,2,0) == Approx(3.0/9.0));

  REQUIRE(B(0,0,1) == 0.0);
  REQUIRE(B(3,3,1) == 0.0);
  REQUIRE(B(2,2,1) == Approx(5.0/9.0));
  REQUIRE(B(1,1,1) == Approx(5.0/9.0));
  REQUIRE(B(1,2,1) == Approx(5.0/9.0));
  REQUIRE(B(1,2,1) == Approx(5.0/9.0));

  REQUIRE(C(0,0,2) == 0.0);
  REQUIRE(C(3,3,2) == 0.0);
  REQUIRE(C(2,2,2) == Approx(7.0/9.0));
  REQUIRE(C(1,1,2) == Approx(7.0/9.0));
  REQUIRE(C(1,2,2) == Approx(7.0/9.0));
  REQUIRE(C(1,2,2) == Approx(7.0/9.0));
}
