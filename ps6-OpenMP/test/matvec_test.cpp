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

#ifdef __583
#include "AOSMatrix.hpp"
#endif

template <typename Mat>
void do_eye_test(const Mat& A) {

  Vector x(5);
  randomize(x);
  Vector    y = mult(A, x);
  for (size_t i = 0; i < 5; ++i) {
    REQUIRE(y(i) != 0.0);
    REQUIRE(y(i) == x(i));
  }
  Vector    z = mult(x, A);
  for (size_t i = 0; i < 5; ++i) {
    REQUIRE(z(i) != 0.0);
    REQUIRE(z(i) == x(i));
  }
}

template <typename Mat>
void do_sing_test(const Mat& A) {

  Vector x(5), y(5);
  unitize(x);
  randomize(y);
  Vector z = y;
  mult(A, x, y);  
  REQUIRE(two_norm(z-y) < 1.e-12);
}

template <typename Mat>
void do_sing_t_test(const Mat& A) {

  Vector x(5), y(5);
  unitize(x);
  randomize(y);
  Vector z = y;
  mult(x, A, y);  
  REQUIRE(two_norm(z-y) < 1.e-12);
}



TEST_CASE("Identity", "[Eye]") {
  SECTION("COO"){
    do_eye_test(read_coomatrix("../data/eye5.mmio"));
  }
  SECTION("CSR"){
    do_eye_test(read_csrmatrix("../data/eye5.mmio"));
  }
  SECTION("CSC"){
    do_eye_test(read_cscmatrix("../data/eye5.mmio"));
  }

#ifdef __583
  SECTION("AOS"){
    do_eye_test(read_aosmatrix("../data/eye5.mmio"));
  }
#endif
}

TEST_CASE("Singular", "[Sing]") {
  SECTION("COO"){
    do_sing_test<COOMatrix>(read_coomatrix("../data/sing5.mmio"));
  }
  SECTION("CSR"){
    do_sing_test<CSRMatrix>(read_csrmatrix("../data/sing5.mmio"));
  }
  SECTION("CSC"){
    do_sing_test<CSCMatrix>(read_cscmatrix("../data/sing5.mmio"));
  }

#ifdef __583
  SECTION("AOS"){
    do_sing_test<AOSMatrix>(read_aosmatrix("../data/sing5.mmio"));
  }
#endif
}


TEST_CASE("Singular Transpose", "[Sing_t]") {
  SECTION("COO"){
    do_sing_t_test<COOMatrix>(read_coomatrix("../data/sing5_t.mmio"));
  }
  SECTION("CSR"){
    do_sing_t_test<CSRMatrix>(read_csrmatrix("../data/sing5_t.mmio"));
  }
  SECTION("CSC"){
    do_sing_t_test<CSCMatrix>(read_cscmatrix("../data/sing5_t.mmio"));
  }

#ifdef __583
  SECTION("AOS"){
    do_sing_t_test<AOSMatrix>(read_aosmatrix("../data/sing5_t.mmio"));
  }
#endif
}

TEST_CASE("Sherman", "[Sherman]") {

  COOMatrix ACOO = read_coomatrix("../data/sherman4.mtx");
  CSRMatrix ACSR = read_csrmatrix("../data/sherman4.mtx");
  CSCMatrix ACSC = read_cscmatrix("../data/sherman4.mtx");

#ifdef __583
  AOSMatrix AAOS = read_aosmatrix("../data/sherman4.mtx");
#endif

  SECTION("I/O") {
    REQUIRE(ACOO.num_rows() == ACSR.num_rows());
    REQUIRE(ACOO.num_cols() == ACSR.num_cols());
    REQUIRE(ACOO.num_rows() == ACSC.num_rows());
    REQUIRE(ACOO.num_cols() == ACSC.num_cols());

#ifdef __583
    REQUIRE(ACOO.num_rows() == AAOS.num_rows());
    REQUIRE(ACOO.num_cols() == AAOS.num_cols());
#endif
  }

  SECTION("zero x") {

    Vector x(ACOO.num_cols());

    Vector yCOO = mult(ACOO, x);
    Vector yCSR = mult(ACSR, x);

    REQUIRE(two_norm(yCOO - yCSR) < 1.e-9);
    Vector yCSC = mult(ACSC, x);
    REQUIRE(two_norm(yCOO - yCSC) < 1.e-9);

#ifdef __583
    Vector yAOS = mult(AAOS, x);
    REQUIRE(two_norm(yCOO - yAOS) < 1.e-9);
#endif
  }

  SECTION("Random x") {
    Vector x(ACOO.num_cols());
    randomize(x);

    Vector yCOO = mult(ACOO, x);
    Vector yCSR = mult(ACSR, x);
    REQUIRE(two_norm(yCOO - yCSR) < 1.e-9);

    Vector yCSC = mult(ACSC, x);
    REQUIRE(two_norm(yCOO - yCSC) < 1.e-9);

#ifdef __583
    Vector yAOS = mult(AAOS, x);
    REQUIRE(two_norm(yCOO - yAOS) < 1.e-9);
#endif
  }
}


TEST_CASE("Sherman Transpose", "[Sherman_t]") {

  COOMatrix ACOO = read_coomatrix("../data/sherman4.mtx");
  CSRMatrix ACSR = read_csrmatrix("../data/sherman4.mtx");
  CSCMatrix ACSC = read_cscmatrix("../data/sherman4.mtx");

#ifdef __583
  AOSMatrix AAOS = read_aosmatrix("../data/sherman4.mtx");
#endif

  SECTION("I/O") {
    REQUIRE(ACOO.num_rows() == ACSR.num_rows());
    REQUIRE(ACOO.num_cols() == ACSR.num_cols());
    REQUIRE(ACOO.num_rows() == ACSC.num_rows());
    REQUIRE(ACOO.num_cols() == ACSC.num_cols());

#ifdef __583
    REQUIRE(ACOO.num_rows() == AAOS.num_rows());
    REQUIRE(ACOO.num_cols() == AAOS.num_cols());
#endif
  }

  SECTION("zero x") {

    Vector x(ACOO.num_cols());

    Vector yCOO = mult(x, ACOO);
    Vector yCSR = mult(x, ACSR);

    REQUIRE(two_norm(yCOO - yCSR) < 1.e-9);
    Vector yCSC = mult(x, ACSC);
    REQUIRE(two_norm(yCOO - yCSC) < 1.e-9);

#ifdef __583
    Vector yAOS = mult(x, AAOS);
    REQUIRE(two_norm(yCOO - yAOS) < 1.e-9);
#endif
  }

  SECTION("Random x") {
    Vector x(ACOO.num_cols());
    randomize(x);

    Vector yCOO = mult(x, ACOO);
    Vector yCSR = mult(x, ACSR);
    REQUIRE(two_norm(yCOO - yCSR) < 1.e-9);

    Vector yCSC = mult(x, ACSC);
    REQUIRE(two_norm(yCOO - yCSC) < 1.e-9);

#ifdef __583
    Vector yAOS = mult(x, AAOS);
    REQUIRE(two_norm(yCOO - yAOS) < 1.e-9);
#endif
  }
}
