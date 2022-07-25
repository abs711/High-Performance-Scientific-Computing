//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH_583_AMATH583SPARSE_HPP
#define AMATH_583_AMATH583SPARSE_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

#include "AOSMatrix.hpp"
#include "COOMatrix.hpp"
#include "CSCMatrix.hpp"
#include "CSRMatrix.hpp"

// ----------------------------------------------------------------
//
// COOMatrix operations
//
// ----------------------------------------------------------------
void piscetize(COOMatrix& A, size_t xpoints, size_t ypoints);

double one_norm(const COOMatrix& A);
double two_norm(const COOMatrix& A);
double inf_norm(const COOMatrix& A);
double f_norm(const COOMatrix& A);

void mult(const COOMatrix& A, const Vector& x, Vector& y);
void mult(const Vector& x, const COOMatrix& A, Vector& y);
void mult(const COOMatrix& A, const Matrix& B, Matrix& C);

Vector mult(const COOMatrix& A, const Vector& x);
Vector mult(const Vector& x, const COOMatrix& A);
Matrix mult(const COOMatrix& A, const Matrix& B);

void mult(const COOMatrix& A, const Vector& x, Vector& y, size_t parts);
void mult(const Vector& x, const COOMatrix& A, Vector& y, size_t parts);
void mult(const COOMatrix& A, const Matrix& B, Matrix& C, size_t parts);

Vector mult(const COOMatrix& A, const Vector& x, size_t parts);
Vector mult(const Vector& x, const COOMatrix& A, size_t parts);
Matrix mult(const COOMatrix& A, const Matrix& B, size_t parts);

// ----------------------------------------------------------------
//
// CSRMatrix operations
//
// ----------------------------------------------------------------
void piscetize(CSRMatrix& A, size_t xpoints, size_t ypoints);

double one_norm(const CSRMatrix& A);
double two_norm(const CSRMatrix& A);
double inf_norm(const CSRMatrix& A);
double f_norm(const CSRMatrix& A);

void mult(const CSRMatrix& A, const Vector& x, Vector& y);
void mult(const CSRMatrix& A, const Matrix& x, Matrix& y);
void mult(const Vector& x, const CSRMatrix& A, Vector& y);

Vector mult(const CSRMatrix& A, const Vector& x);
Matrix mult(const CSRMatrix& A, const Matrix& x);
Vector mult(const Vector& x, const CSRMatrix& A);

void mult(const CSRMatrix& A, const Vector& x, Vector& y, size_t parts);
void mult(const CSRMatrix& A, const Matrix& x, Matrix& y, size_t parts);
void mult(const Vector& x, const CSRMatrix& A, Vector& y, size_t parts);

Vector mult(const CSRMatrix& A, const Vector& x, size_t parts);
Matrix mult(const CSRMatrix& A, const Matrix& x, size_t parts);
Vector mult(const Vector& x, const CSRMatrix& A, size_t parts);

// ----------------------------------------------------------------
//
// CSCMatrix operations
//
// ----------------------------------------------------------------
void piscetize(CSCMatrix& A, size_t xpoints, size_t ypoints);

double one_norm(const CSCMatrix& A);
double two_norm(const CSCMatrix& A);
double inf_norm(const CSCMatrix& A);
double f_norm(const CSCMatrix& A);

void mult(const CSCMatrix& A, const Vector& x, Vector& y);
void mult(const CSCMatrix& A, const Matrix& x, Matrix& y);
void mult(const Vector& x, const CSCMatrix& A, Vector& y);

Vector mult(const CSCMatrix& A, const Vector& x);
Matrix mult(const CSCMatrix& A, const Matrix& x);
Vector mult(const Vector& x, const CSCMatrix& A);

void mult(const CSCMatrix& A, const Vector& x, Vector& y, size_t parts);
void mult(const CSCMatrix& A, const Matrix& x, Matrix& y, size_t parts);
void mult(const Vector& x, const CSCMatrix& A, Vector& y, size_t parts);

Vector mult(const CSCMatrix& A, const Vector& x, size_t parts);
Matrix mult(const CSCMatrix& A, const Matrix& x, size_t parts);
Vector mult(const Vector& x, const CSCMatrix& A, size_t parts);

// ----------------------------------------------------------------
//
// AOSMatrix operations
//
// ----------------------------------------------------------------
void piscetize(AOSMatrix& A, size_t xpoints, size_t ypoints);

double one_norm(const AOSMatrix& A);
double two_norm(const AOSMatrix& A);
double inf_norm(const AOSMatrix& A);
double f_norm(const AOSMatrix& A);

void mult(const AOSMatrix& A, const Vector& x, Vector& y);
void mult(const AOSMatrix& A, const Matrix& x, Matrix& y);
void mult(const Vector& x, const AOSMatrix& A, Vector& y);

Vector mult(const AOSMatrix& A, const Vector& x);
Matrix mult(const AOSMatrix& A, const Matrix& x);
Vector mult(const Vector& x, const AOSMatrix& A);

#endif    //  AMATH_583_AMATH583SPARSE_HPP
