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
void zeroize(Vector& x);
void unitize(Vector& x);
void randomize(Vector& x, double scale = 1.0, double mean = 0.0);

double one_norm(const Vector& x);
double two_norm(const Vector& x);
double inf_norm(const Vector& x);
double p_norm(const Vector& x);

Vector operator+(const Vector& x, const Vector& y);
Vector operator-(const Vector& x, const Vector& y);

Vector& operator*=(Vector& x, double alpha);
Vector& operator+=(Vector& x, double alpha);
Vector& operator+=(Vector& x, const Vector& y);
Vector& operator-=(Vector& x, const Vector& y);

// For PS5
double two_norm_r(const Vector& x);
double two_norm_s(const Vector& x);

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
Vector mult(const Matrix& A, const Vector& x);
void   mult(const Matrix& A, const Vector& x, Vector& y);

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

#endif    //  AMATH_583_AMATH583_HPP
