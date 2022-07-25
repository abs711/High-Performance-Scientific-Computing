//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "pagerank.hpp"

#define CATCH_CONFIG_MAIN    // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

TEST_CASE("is csr stochastic", "[is_stochastic]") {
  CSRMatrix A = read_csrmatrix("data/Erdos02.mtx");
  A.stochastify();

  REQUIRE(A.num_rows() != 0);
  REQUIRE(A.num_cols() != 0);
  REQUIRE(A.num_rows() == A.num_cols());
  Vector x = pagerank(A, 0.85, 1.e-4, 100);
  auto   r = rank(x);

  REQUIRE(r[0] == 6926);
  REQUIRE(r[1] == 502);
  REQUIRE(r[2] == 303);
  REQUIRE(r[3] == 444);
  REQUIRE(r[4] == 261);
  REQUIRE(r[5] == 391);
  REQUIRE(r[6] == 354);
  REQUIRE(r[7] == 299);
  REQUIRE(r[8] == 231);
  REQUIRE(r[9] == 474);
}
