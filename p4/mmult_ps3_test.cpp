
#define CATCH_CONFIG_MAIN    // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Matrix.hpp"
#include "amath583.hpp"

void basic_mult(const Matrix& A, const Matrix& B, Matrix& C) {
  REQUIRE(C.num_rows() == A.num_rows());
  REQUIRE(C.num_cols() == B.num_cols());
  REQUIRE(A.num_cols() == B.num_rows());

  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      for (size_t k = 0; k < A.num_cols(); ++k) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
}

void basic_mult_trans(const Matrix& A, const Matrix& B, Matrix& C) {
  REQUIRE(C.num_rows() == A.num_rows());
  REQUIRE(C.num_cols() == B.num_rows());
  REQUIRE(A.num_cols() == B.num_cols());

  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      for (size_t k = 0; k < A.num_cols(); ++k) {
        C(i, j) += A(i, k) * B(j, k);
      }
    }
  }
}

TEST_CASE("ijk multiply", "[mult_ijk]") {
  for (size_t m = 6; m <= 66; m += 10) {
    for (size_t n = 6; n <= 66; n += 6) {
      for (size_t k = 6; k <= 66; k += 20) {
        Matrix A(m, k);
        Matrix B(k, n);
        Matrix C(m, n);
        Matrix C0(m, n);
        Matrix C_good(m, n);
        randomize(A);
        randomize(B);
        randomize(C0);

        Matrix Bt = transpose(B);

        copy(C0, C);
        basic_mult(A, B, C);
        copy(C, C_good);
        REQUIRE(f_norm(C - C_good) < 1.e-9 * f_norm(C));

        SECTION("mult_0") {
          copy(C0, C);
          mult_0(A, B, C);
          REQUIRE(f_norm(C - C_good) < 1.e-9 * f_norm(C));
        }
        SECTION("mult_1") {
          copy(C0, C);
          mult_1(A, B, C);
          REQUIRE(f_norm(C - C_good) < 1.e-9 * f_norm(C));
        }
        SECTION("mult_2") {
          copy(C0, C);
          mult_2(A, B, C);
          REQUIRE(f_norm(C - C_good) < 1.e-9 * f_norm(C));
        }
        SECTION("mult_3") {
          copy(C0, C);
          mult_3(A, B, C);
          REQUIRE(f_norm(C - C_good) < 1.e-9 * f_norm(C));
        }
        SECTION("mult_trans_0") {
          copy(C0, C);
          mult_trans_0(A, Bt, C);
          REQUIRE(f_norm(C - C_good) < 1.e-9 * f_norm(C));
        }
        SECTION("mult_trans_1") {
          copy(C0, C);
          mult_trans_1(A, Bt, C);
          REQUIRE(f_norm(C - C_good) < 1.e-9 * f_norm(C));
        }
        SECTION("mult_trans_2") {
          copy(C0, C);
          mult_trans_2(A, Bt, C);
          REQUIRE(f_norm(C - C_good) < 1.e-9 * f_norm(C));
        }
        SECTION("mult_trans_3") {
          copy(C0, C);
          mult_trans_3(A, Bt, C);
          REQUIRE(f_norm(C - C_good) < 1.e-9 * f_norm(C));
        }
      }
    }
  }
}
