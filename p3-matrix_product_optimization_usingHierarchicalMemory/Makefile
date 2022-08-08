#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#

CXX             := c++

OPTS            := -Ofast -march=native # -DNDEBUG
LANG            := -std=c++11
PICKY           := -Wall
CXXFLAGS        := $(LANG) $(OPTS) $(PICKY) 

.PHONY		: clean all

LIBS		:=
OS		:= $(shell uname -s)
ifeq ($(OS),Linux)
	LIBS	+= -lpthread
endif

hello.exe	: hello.cpp
		  $(CXX) $(CXXFLAGS) hello.cpp -o hello.exe

goodbye.exe	: goodbye.cpp
		  $(CXX) $(CXXFLAGS) goodbye.cpp -o goodbye.exe

repeat.exe	: repeat.cpp
		  $(CXX) $(CXXFLAGS) repeat.cpp -o repeat.exe

main.exe	: main.cpp
		  $(CXX) $(CXXFLAGS) main.cpp -o main.exe

timing0.exe	: timing.cpp
		  $(CXX) $(LANG) $(PICKY) -O0 timing.cpp -o timing0.exe

timing3.exe	: timing.cpp
		  $(CXX) $(LANG) $(PICKY) -O3 timing.cpp -o timing3.exe

efficiency0.exe	: efficiency.cpp
		  $(CXX) $(LANG) $(PICKY) -O0 -Rpass=.* efficiency.cpp -o efficiency0.exe

efficiency3.exe	: efficiency.cpp
		  $(CXX) $(LANG) $(PICKY) -O3 -Rpass=.* efficiency.cpp -o efficiency3.exe

efficiencyfast.exe	: efficiency.cpp
		  $(CXX) $(LANG) $(PICKY) -Ofast efficiency.cpp -o efficiencyfast.exe		  

float_vs_double0.exe 	: float_vs_double.cpp
		  $(CXX) $(LANG) $(PICKY) -O0 -Rpass=.* float_vs_double.cpp -o float_vs_double0.exe

float_vs_double3.exe 	: float_vs_double.cpp
		  $(CXX) $(LANG) $(PICKY) -O3 -Rpass=.* float_vs_double.cpp -o float_vs_double3.exe

mnist.o		: mnist.cpp Matrix.hpp amath583.hpp
		  $(CXX) $(CXXFLAGS) -Wno-char-subscripts -c mnist.cpp -o mnist.o

mnist.exe	: mnist.o amath583.o
		  $(CXX) $(CXXFLAGS) mnist.o amath583.o -o mnist.exe

mmtime.o	: mmtime.cpp Matrix.hpp amath583.hpp
		  $(CXX) $(CXXFLAGS) -c mmtime.cpp -o mmtime.o

mmtime.exe	: mmtime.o amath583.o
		  $(CXX) $(CXXFLAGS) -Rpass=.* mmtime.o amath583.o -o mmtime.exe

amath583.o 	: amath583.cpp amath583.hpp Vector.hpp
		  $(CXX) $(CXXFLAGS) -c amath583.cpp -o amath583.o

catch.o		: catch.cpp catch.hpp
		  $(CXX) $(CXXFLAGS) -c catch.cpp -o catch.o

test_mult.exe 	: catch.o test_mult.o amath583.o
		  $(CXX) $(CXXFLAGS) catch.o test_mult.o amath583.o -o test_mult.exe

test_mult.o 	: catch.hpp test_mult.cpp amath583.hpp Matrix.hpp
		  $(CXX) $(CXXFLAGS) -c test_mult.cpp -o test_mult.o

test_operator.exe 	: catch.o test_operator.o amath583.o
		  $(CXX) $(CXXFLAGS) catch.o test_operator.o amath583.o -o test_operator.exe

test_operator.o : catch.hpp test_operator.cpp amath583.hpp Matrix.hpp
		  $(CXX) $(CXXFLAGS) -c test_operator.cpp -o test_operator.o

test_transpose.exe 	: catch.o test_transpose.o amath583.o
		  $(CXX) $(CXXFLAGS) catch.o test_transpose.o amath583.o -o test_transpose.exe

test_transpose.o 	: catch.hpp test_transpose.cpp amath583.hpp Matrix.hpp
		  $(CXX) $(CXXFLAGS) -c test_transpose.cpp -o test_transpose.o

test_mult_trans.exe 	: catch.o test_mult_trans.o amath583.o
		  $(CXX) $(CXXFLAGS) catch.o test_mult_trans.o amath583.o -o test_mult_trans.exe

test_mult_trans.o 	: catch.hpp test_mult_trans.cpp amath583.hpp Matrix.hpp
		  $(CXX) $(CXXFLAGS) -c test_mult_trans.cpp -o test_mult_trans.o

test_mult_trans_0.exe 	: catch.o test_mult_trans_0.o amath583.o
		  $(CXX) $(CXXFLAGS) catch.o test_mult_trans_0.o amath583.o -o test_mult_trans_0.exe

test_mult_trans_0.o 	: catch.hpp test_mult_trans_0.cpp amath583.hpp Matrix.hpp  test_mult_trans.hpp
		  $(CXX) $(CXXFLAGS) -c test_mult_trans_0.cpp -o test_mult_trans_0.o

test_mult_trans_1.exe 	: catch.o test_mult_trans_1.o amath583.o
		  $(CXX) $(CXXFLAGS) catch.o test_mult_trans_1.o amath583.o -o test_mult_trans_1.exe

test_mult_trans_1.o 	: catch.hpp test_mult_trans_1.cpp amath583.hpp Matrix.hpp  test_mult_trans.hpp
		  $(CXX) $(CXXFLAGS) -c test_mult_trans_1.cpp -o test_mult_trans_1.o

test_mult_trans_2.exe 	: catch.o test_mult_trans_2.o amath583.o
		  $(CXX) $(CXXFLAGS) catch.o test_mult_trans_2.o amath583.o -o test_mult_trans_2.exe

test_mult_trans_2.o 	: catch.hpp test_mult_trans_2.cpp amath583.hpp Matrix.hpp  test_mult_trans.hpp
		  $(CXX) $(CXXFLAGS) -c test_mult_trans_2.cpp -o test_mult_trans_2.o

test_mult_trans_3.exe 	: catch.o test_mult_trans_3.o amath583.o
		  $(CXX) $(CXXFLAGS) catch.o test_mult_trans_3.o amath583.o -o test_mult_trans_3.exe

test_mult_trans_3.o 	: catch.hpp test_mult_trans_3.cpp amath583.hpp Matrix.hpp  test_mult_trans.hpp
		  $(CXX) $(CXXFLAGS) -c test_mult_trans_3.cpp -o test_mult_trans_3.o

test_mult_trans_4.exe 	: catch.o test_mult_trans_4.o amath583.o
		  $(CXX) $(CXXFLAGS) catch.o test_mult_trans_4.o amath583.o -o test_mult_trans_4.exe

test_mult_trans_4.o 	: catch.hpp test_mult_trans_4.cpp amath583.hpp Matrix.hpp  test_mult_trans.hpp
		  $(CXX) $(CXXFLAGS) -c test_mult_trans_4.cpp -o test_mult_trans_4.o

test_mult_trans_5.exe 	: catch.o test_mult_trans_5.o amath583.o
		  $(CXX) $(CXXFLAGS) catch.o test_mult_trans_5.o amath583.o -o test_mult_trans_5.exe

test_mult_trans_5.o : catch.hpp test_mult_trans_5.cpp amath583.hpp Matrix.hpp  test_mult_trans.hpp
		  $(CXX) $(CXXFLAGS) -c test_mult_trans_5.cpp -o test_mult_trans_5.o


ALL = hello.exe goodbye.exe repeat.exe main.exe timing0.exe timing3.exe efficiency0.exe efficiency3.exe \
      float_vs_double0.exe float_vs_double3.exe mnist.exe mmtime.exe test_transpose.exe test_transpose.o \
      test_mult_trans.exe test_mult_trans.o test_mult.exe test_mult.o test_operator.exe test_operator.o amath583.o \
      mnist.o mmtime.o catch.o \
      test_mult_trans_0.exe test_mult_trans_0.o test_mult_trans_1.exe test_mult_trans_1.o \
      test_mult_trans_2.exe test_mult_trans_2.o test_mult_trans_3.exe test_mult_trans_3.o \
      test_mult_trans_4.exe test_mult_trans_4.o test_mult_trans_5.exe test_mult_trans_5.o

EXE = hello.exe goodbye.exe repeat.exe main.exe timing0.exe timing3.exe efficiency0.exe efficiency3.exe \
      float_vs_double0.exe float_vs_double3.exe mnist.exe mmtime.exe test_transpose.exe  \
      test_mult_trans.exe test_mult.exe test_operator.exe \
      test_mult_trans_0.exe test_mult_trans_1.exe  \
      test_mult_trans_2.exe test_mult_trans_3.exe  \
      test_mult_trans_4.exe test_mult_trans_5.exe 


all: $(EXE)

clean		:
		  /bin/rm -f $(ALL)
		  /bin/rm -f mnist_similarity*.bmp mnist_0.bmp 
		  /bin/rm -rf *.exe.dSYM a.out

ps3.tar.gz	: CImg.h			Vector.hpp		efficiency.cpp		mmtime.cpp		test_mult_trans.cpp	test_mult_trans_3.cpp	timing.cpp \
	Makefile		amath583.cpp		float_vs_double.cpp	mnist.cpp		test_mult_trans.hpp	test_mult_trans_4.cpp	train-images.idx3-ubyte \
	Matrix.hpp		amath583.hpp		goodbye.cpp		mnist.hpp		test_mult_trans_0.cpp	test_mult_trans_5.cpp	verify.bash \
	Questions.rst		catch.cpp		hello.cpp		repeat.cpp		test_mult_trans_1.cpp	test_operator.cpp \
	Timer.hpp		catch.hpp		main.cpp		test_mult.cpp		test_mult_trans_2.cpp	test_transpose.cpp
	tar zcvf ps3.tar.gz \
	CImg.h			Vector.hpp		efficiency.cpp		mmtime.cpp		test_mult_trans.cpp	test_mult_trans_3.cpp	timing.cpp \
	Makefile		amath583.cpp		float_vs_double.cpp	mnist.cpp		test_mult_trans.hpp	test_mult_trans_4.cpp	train-images.idx3-ubyte \
	Matrix.hpp		amath583.hpp		goodbye.cpp		mnist.hpp		test_mult_trans_0.cpp	test_mult_trans_5.cpp	verify.bash \
	Questions.rst		catch.cpp		hello.cpp		repeat.cpp		test_mult_trans_1.cpp	test_operator.cpp \
	Timer.hpp		catch.hpp		main.cpp		test_mult.cpp		test_mult_trans_2.cpp	test_transpose.cpp