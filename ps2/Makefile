#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#

CXX       := c++

OPTS      := -g -O0 -DNDEBUG
LANG      := -std=c++11
PICKY     := -Wall

CXXFLAGS  := $(LANG) $(OPTS) $(PICKY)

.PHONY	  : clean all

all		  : julia.exe test_norms.exe test_zeroize.exe test_dot.exe test_norm_d.exe \
		    test_matrix_norms.exe test_f_norm.exe \
		    assert0.exe assert1.exe assert2.exe assert3.exe

LIBS		:=
OS		:= $(shell uname -s)
ifeq ($(OS),Linux)
	LIBS	+= -lpthread
endif

julia.exe 	: julia.o amath583.o
		  $(CXX) $(CXXFLAGS) julia.o -o julia.exe $(LIBS)

julia.o 	: julia.cpp amath583.hpp Vector.hpp
	   	  $(CXX) $(CXXFLAGS) -Wno-char-subscripts -c julia.cpp -o julia.o

test_norms.exe 	: test_norms.o amath583.o
		  $(CXX) $(CXXFLAGS) test_norms.o amath583.o -o test_norms.exe

test_norms.o 	: test_norms.cpp amath583.hpp Vector.hpp
		  $(CXX) $(CXXFLAGS) -c test_norms.cpp -o test_norms.o

test_zeroize.exe 	: test_zeroize.o amath583.o
		  $(CXX) $(CXXFLAGS) test_zeroize.o amath583.o -o test_zeroize.exe

test_zeroize.o 	: test_zeroize.cpp amath583.hpp Vector.hpp
		  $(CXX) $(CXXFLAGS) -c test_zeroize.cpp -o test_zeroize.o

test_dot.exe 	: test_dot.o amath583.o
		  $(CXX) $(CXXFLAGS) test_dot.o amath583.o -o test_dot.exe

test_dot.o 	: test_dot.cpp amath583.hpp Vector.hpp
		  $(CXX) $(CXXFLAGS) -c test_dot.cpp -o test_dot.o

test_norm_d.exe : test_norm_d.o amath583.o
		  $(CXX) $(CXXFLAGS) test_norm_d.o amath583.o -o test_norm_d.exe

test_norm_d.o 	: test_norm_d.cpp amath583.hpp Vector.hpp
		  $(CXX) $(CXXFLAGS) -c test_norm_d.cpp -o test_norm_d.o

test_matrix_norms.exe 	: test_matrix_norms.o amath583.o
		  $(CXX) $(CXXFLAGS) test_matrix_norms.o amath583.o -o test_matrix_norms.exe

test_matrix_norms.o 	: test_matrix_norms.cpp amath583.hpp Matrix.hpp
		  $(CXX) $(CXXFLAGS) -c test_matrix_norms.cpp -o test_matrix_norms.o

test_f_norm.exe 	: test_f_norm.o amath583.o 
		  $(CXX) $(CXXFLAGS) test_f_norm.o amath583.o -o test_f_norm.exe

test_f_norms.o : test_f_norm.cpp amath583.hpp Matrix.hpp
		  $(CXX) $(CXXFLAGS) -c test_f_norm.cpp -o test_f_norm.o

amath583.o 	: amath583.cpp amath583.hpp Vector.hpp Matrix.hpp
		  $(CXX) $(CXXFLAGS) -c amath583.cpp -o amath583.o

assert0.exe	: assert0.cpp
		  $(CXX) $(CXXFLAGS) assert0.cpp -o assert0.exe

assert1.exe	: assert1.cpp
		  $(CXX) $(CXXFLAGS) assert1.cpp -o assert1.exe

assert2.exe	: assert2.cpp
		  $(CXX) $(CXXFLAGS) assert2.cpp -o assert2.exe

assert3.exe	: assert3.cpp
		  $(CXX) $(CXXFLAGS) assert3.cpp -o assert3.exe

clean		:
		  /bin/rm -f *~ julia.bmp julia.exe julia.o \
		    test_norms.exe test_zeroize.exe test_dot.exe test_norm_d.exe \
		    test_matrix_norms.exe test_f_norm.exe \
		    assert0.exe assert1.exe assert2.exe assert3.exe 
		  /bin/rm -f test_norms.o test_zeroize.o test_dot.o test_norm_d.o \
		    test_matrix_norms.o test_f_norm.o \
		    assert0.o assert1.o assert2.o assert3.o \
		    amath583.o 
		  /bin/rm -rf *.exe.dSYM
ps2.tar.gz	: CImg.h Makefile Matrix.hpp Vector.hpp amath583.cpp amath583.hpp assert0.cpp assert1.cpp  assert2.cpp assert3.cpp\
		  catch.hpp julia.cpp test_dot.cpp test_f_norm.cpp test_matrix_norms.cpp test_norm_d.cpp test_norms.cpp \
		  test_zeroize.cpp verify.bash Questions.rst
		  tar zcvf ps2.tar.gz \
	 	  CImg.h Makefile Matrix.hpp Vector.hpp amath583.cpp amath583.hpp assert0.cpp assert1.cpp  assert2.cpp assert3.cpp \
		  catch.hpp julia.cpp test_dot.cpp test_f_norm.cpp test_matrix_norms.cpp test_norm_d.cpp test_norms.cpp \
		  test_zeroize.cpp verify.bash \
		  Questions.rst
