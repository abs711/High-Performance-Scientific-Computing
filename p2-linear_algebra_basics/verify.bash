#!/bin/bash 
#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#

function do_test() {
    echo "=== Testing $1 ==="
    eval $1
    if [ $? = 0 ]; then
	echo "+++ $1 Passed +++"
    else
	echo "--- $1 Failed ---"
    fi
}


do_test "make clean"

do_test "make assert3.exe"
do_test "./assert3.exe"

do_test "make test_zeroize.exe"
do_test "./test_zeroize.exe"

do_test "make test_norms.exe"
do_test "./test_norms.exe"

do_test "make test_dot.exe"
do_test "./test_dot.exe"

do_test "make test_norm_d.exe"
do_test "./test_norm_d.exe"

do_test "make test_matrix_norms.exe"
do_test "./test_matrix_norms.exe"

do_test "make test_f_norm.exe"
do_test "./test_f_norm.exe"

do_test "make julia.exe"
do_test "./julia.exe"
if [ -e "julia.bmp" ]; then
    echo "+++ julia.bmp found +++"
else
    echo "--- julia.bmp not found ---"
fi




    
