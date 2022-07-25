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

template <typename Mat>
void do_eye_test(const Mat& A, size_t parts) {

  Vector x(5);
  randomize(x);
  Vector y = mult(A, x, parts);
  for (size_t i = 0; i < 5; ++i) {
    REQUIRE(y(i) != 0.0);
    REQUIRE(y(i) == x(i));
  }
  Vector z = mult(x, A, parts);
  for (size_t i = 0; i < 5; ++i) {
    REQUIRE(z(i) != 0.0);
    REQUIRE(z(i) == x(i));
  }
}

template <typename Mat>
void do_sing_test(const Mat& A, size_t parts) {

  Vector x(5), y(5);
  unitize(x);
  randomize(y);
  Vector z = y;
  mult(A, x, y, parts);
  REQUIRE(two_norm(z - y) < 1.e-12);
}

template <typename Mat>
void do_sing_t_test(const Mat& A, size_t parts) {

  Vector x(5), y(5);
  unitize(x);
  randomize(y);
  Vector z = y;
  mult(x, A, y, parts);
  REQUIRE(two_norm(z - y) < 1.e-12);
}

TEST_CASE("Identity", "[Eye]") {

  for (size_t i = 1; i < 8; i *= 2) {
    SECTION("COO") { do_eye_test(read_coomatrix("data/eye5.mmio"), i); }
    SECTION("CSR") { do_eye_test(read_csrmatrix("data/eye5.mmio"), i); }
    SECTION("CSC") { do_eye_test(read_cscmatrix("data/eye5.mmio"), i); }
  }
}

TEST_CASE("Singular", "[Sing]") {
  for (size_t i = 1; i < 8; i *= 2) {
    SECTION("COO") { do_sing_test<COOMatrix>(read_coomatrix("data/sing5.mmio"), i); }
    SECTION("CSR") { do_sing_test<CSRMatrix>(read_csrmatrix("data/sing5.mmio"), i); }
    SECTION("CSC") { do_sing_test<CSCMatrix>(read_cscmatrix("data/sing5.mmio"), i); }
  }
}

TEST_CASE("Singular Transpose", "[Sing_t]") {
  for (size_t i = 1; i < 8; i *= 2) {
    SECTION("COO") { do_sing_t_test<COOMatrix>(read_coomatrix("data/sing5_t.mmio"), i); }
    SECTION("CSR") { do_sing_t_test<CSRMatrix>(read_csrmatrix("data/sing5_t.mmio"), i); }
    SECTION("CSC") { do_sing_t_test<CSCMatrix>(read_cscmatrix("data/sing5_t.mmio"), i); }
  }
}

TEST_CASE("Sherman", "[Sherman]") {

  COOMatrix ACOO = read_coomatrix("data/sherman4.mtx");
  CSRMatrix ACSR = read_csrmatrix("data/sherman4.mtx");
  CSCMatrix ACSC = read_cscmatrix("data/sherman4.mtx");

  SECTION("I/O") {
    REQUIRE(ACOO.num_rows() == ACSR.num_rows());
    REQUIRE(ACOO.num_cols() == ACSR.num_cols());
    REQUIRE(ACOO.num_rows() == ACSC.num_rows());
    REQUIRE(ACOO.num_cols() == ACSC.num_cols());
  }

  for (size_t i = 1; i < 8; i *= 2) {
    SECTION("zero x") {

      Vector x(ACOO.num_cols());

      Vector yCOO = mult(ACOO, x, i);
      Vector yCSR = mult(ACSR, x, i);

      REQUIRE(two_norm(yCOO - yCSR) < 1.e-9);
      Vector yCSC = mult(ACSC, x);
      REQUIRE(two_norm(yCOO - yCSC) < 1.e-9);
    }

    SECTION("Random x") {
      Vector x(ACOO.num_cols());
      randomize(x);

      Vector yCOO = mult(ACOO, x, i);
      Vector yCSR = mult(ACSR, x, i);
      REQUIRE(two_norm(yCOO - yCSR) < 1.e-9);

      Vector yCSC = mult(ACSC, x, i);
      REQUIRE(two_norm(yCOO - yCSC) < 1.e-9);
    }
  }
}
