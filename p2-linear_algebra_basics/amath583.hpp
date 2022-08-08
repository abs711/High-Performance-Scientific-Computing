//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_HPP
#define AMATH583_HPP

#include "Matrix.hpp"
#include "Vector.hpp"
#include <cstddef>

void   zeroize(Vector& x);
double one_norm(const Vector& x);
double two_norm(const Vector& x);
double inf_norm(const Vector& x);
double dot(const Vector& x, const Vector& y);
double two_norm_d(const Vector& x);
// Also need to add dot()
// and optionally two_norm_d()


double one_norm(const Matrix& x);
double inf_norm(const Matrix& A);
double f_norm(const Matrix& A);

// 583 need to add inf_norm for matrix
// and optionally f_norm for matrix

#endif    // AMATH583_HPP
