//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH_583_AMATH583_HPP
#define AMATH_583_AMATH583_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

// ----------------------------------------------------------------
//
// Vector arithmetic
//
// ----------------------------------------------------------------
void   zeroize(Vector& x);
void   randomize(Vector& x);
double one_norm(const Vector& x);
double two_norm(const Vector& x);
double inf_norm(const Vector& x);
double p_norm(const Vector& x);

Vector operator+(const Vector& x, const Vector& y);
Vector operator-(const Vector& x, const Vector& y);

Vector& operator*=(double alpha, const Vector& x);
Vector& operator+=(const Vector& x, const Vector& y);
Vector& operator-=(const Vector& x, const Vector& y);

// ----------------------------------------------------------------
//
// Matrix arithmetic
//
// ----------------------------------------------------------------
void   zeroize(Matrix& x);
void   randomize(Matrix& x);
double one_norm(const Matrix& x);
double two_norm(const Matrix& x);
double inf_norm(const Matrix& x);
double f_norm(const Matrix& x);

Matrix operator+(const Matrix& x, const Matrix& y);
Matrix operator-(const Matrix& x, const Matrix& y);

Matrix& operator*=(double alpha, const Matrix& x);
Matrix& operator+=(const Matrix& x, const Matrix& y);
Matrix& operator-=(const Matrix& x, const Matrix& y);

// ----------------------------------------------------------------
//
// Matrix-vector operations
//
// ----------------------------------------------------------------
Vector operator*(const Matrix& A, const Vector& x);
void   matvec(const Matrix& A, const Vector& x, Vector& y);

// ----------------------------------------------------------------
//
// Matrix-matrix operations
//
// ----------------------------------------------------------------
Matrix operator*(const Matrix& A, const Matrix& B);
void   matmat(const Matrix& A, const Vector& B, Matrix& C);

void   copy(const Matrix& A, Matrix& At);
Matrix copy(const Matrix& A);
void   transpose(const Matrix& A, Matrix& At);
Matrix transpose(const Matrix& A);

void mult_0(const Matrix& A, const Matrix& B, Matrix& C);
void mult_1(const Matrix& A, const Matrix& B, Matrix& C);
void mult_2(const Matrix& A, const Matrix& B, Matrix& C);
void mult_3(const Matrix& A, const Matrix& B, Matrix& C);
void mult_trans_0(const Matrix& A, const Matrix& B, Matrix& C);
void mult_trans_1(const Matrix& A, const Matrix& B, Matrix& C);
void mult_trans_2(const Matrix& A, const Matrix& B, Matrix& C);
void mult_trans_3(const Matrix& A, const Matrix& B, Matrix& C);
void mult_trans_4(const Matrix& A, Matrix& C);
void mult_trans_5(const Matrix& A, const Matrix& B, Matrix& C);

void   mult_ijk(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_ikj(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_jik(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_jki(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_kij(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_kji(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_trans_ijk(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_trans_ikj(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_trans_jik(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_trans_jki(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_trans_kij(const Matrix& A, const Matrix& B, Matrix& C);
void   mult_trans_kji(const Matrix& A, const Matrix& B, Matrix& C);

#endif    //  AMATH_583_AMATH583_HPP
