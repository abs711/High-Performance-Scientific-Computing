//
// This file is part of the course materials for AMATH 483/583 at the University of Washington
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#define CATCH_CONFIG_MAIN    // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#define AMATH583_EIGENFACES_MAIN_HPP

#include "amath583.hpp"

#define outer outer_seq
#define gen_covariance gen_covariance_seq
#define tag tag_seq
#include "eigenfaces_seq.cpp"
#undef outer
#undef gen_covariance
#undef tag

#define outer outer_opt
#define gen_covariance gen_covariance_opt
#define tag tag_opt
#include "eigenfaces_opt.cpp"
#undef outer
#undef gen_covariance
#undef tag

#define outer outer_par
#define gen_covariance gen_covariance_par
#define tag tag_par
#include "eigenfaces_par.cpp"
#undef outer
#undef gen_covariance
#undef tag

#define outer outer_block
#define gen_covariance gen_covariance_block
#define tag tag_block
#include "eigenfaces_block.cpp"
#undef outer
#undef gen_covariance
#undef tag

#define outer outer_dgemm
#define gen_covariance gen_covariance_dgemm
#define tag tag_dgemm
#include "eigenfaces_dgemm.cpp"
#undef outer
#undef gen_covariance
#undef tag



TEST_CASE("opt", "[opt]") {
  std::vector<Vector> z(0, Vector(0));
  size_t sz = 13;

  for (size_t k = 0; k < 17; ++k) {
    Vector x(sz);
    randomize(x);
    z.push_back(x);
  }
  auto C = gen_covariance_seq(z);
  auto D = gen_covariance_opt(z);

  REQUIRE(f_norm(C-D) < 1.e-12 * f_norm(C));
}


TEST_CASE("par", "[par]") {
  std::vector<Vector> z(0, Vector(0));
  size_t sz = 13;

  for (size_t k = 0; k < 17; ++k) {
    Vector x(sz);
    randomize(x);
    z.push_back(x);
  }
  auto C = gen_covariance_seq(z);
  auto D = gen_covariance_par(z);

  REQUIRE(f_norm(C-D) < 1.e-12 * f_norm(C));
}

TEST_CASE("block", "[block]") {
  std::vector<Vector> z(0, Vector(0));
  size_t sz = 13;

  for (size_t k = 0; k < 17; ++k) {
    Vector x(sz);
    randomize(x);
    z.push_back(x);
  }
  auto C = gen_covariance_seq(z);
  auto D = gen_covariance_block(z);

  REQUIRE(f_norm(C-D) < 1.e-12 * f_norm(C));
}

TEST_CASE("dgemm", "[dgemm]") {
  std::vector<Vector> z(0, Vector(0));
  size_t sz = 13;

  for (size_t k = 0; k < 17; ++k) {
    Vector x(sz);
    randomize(x);
    z.push_back(x);
  }
  auto C = gen_covariance_seq(z);
  auto D = gen_covariance_dgemm(z);

  REQUIRE(f_norm(C-D) < 1.e-12 * f_norm(C));
}
