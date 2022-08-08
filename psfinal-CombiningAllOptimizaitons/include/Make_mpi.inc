# -*- mode:Makefile -*-
#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2021
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#

CXX	    	:= c++
MPICXX		:= mpicxx
# MPICXX          := mpiicpc -no-multibyte-chars

MKL		:= /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1/

# Maximum optimization effort: -Ofast -march=native -DNDEBUG
OPTS        	:= -Ofast -march=native -DNDEBUG
DEBUG		:= # -g -O0 -fsanitize=address
PROFILE		:= 
LANG        	:= -std=c++14
PICKY       	:= -Wall
DIAG		:= # -Rpass=.*
INCLUDES	:= -I../include -I$(MKL)/include
LIBS		:= -L$(MKL)/lib/intel64 -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5

VPATH		= ../include:../src

CXXFLAGS	+= $(DEFS) $(XDEFS) $(OPTS) $(DEBUG) $(PROFILE) $(LANG) $(PICKY) $(DIAG) $(INCLUDES) 

ifeq (, $(shell which ${CXX}))
  CXX := c++
  ifeq (, $(shell which ${CXX}))
  CXX := g++
  ifeq (, $(shell which ${CXX}))
  CXX := g++-9
  ifeq (, $(shell which ${CXX}))
  $(error "No ${CXX} in $(PATH) -- set CXX to an appropriate compiler in Makefile")
  endif
  endif
  endif
endif

CXXVERSION 	:= $(shell ${CXX} --version | head -1)

ifeq 'g++' '$(findstring g++, $(CXXVERSION))'
  CXXFAM := gnu
endif

ifeq 'clang' '$(findstring clang, $(CXXVERSION))'
  CXXFAM := clang
endif

OS		:= $(shell uname -s)

ifeq ($(OS),Darwin)
ifeq ($(CXXFAM),clang)
  XDEFS     += -Xpreprocessor
  LIBS		+= -lpthread -lomp
endif
ifeq ($(CXXFAM),gnu)
  LIBS		+= -L/usr/local/lib -lomp
endif
endif

XDEFS		+= -fopenmp

ifeq ($(OS),Linux)
ifeq ($(CXXFAM),clang)
	LIBS	+= -lpthread
endif
endif

SOURCES		= $(TARGETS:.exe=.cpp) $(TESTS:.exe=.cpp) 
OBJECTS		= $(SOURCES:.cpp=.o)   $(LOBJ)
HEADERS		= $(SOURCES:.cpp=.hpp) $(LINC)
PCHS		= $(HEADERS:=.gch)

$SHELL		= bash

LSRC		:= amath583.cpp amath583IO.cpp amath583sparse.cpp
LINC		:= amath583.hpp amath583IO.hpp
XSRC		:= ../src/amath583.cpp ../src/amath583IO.cpp ../src/amath583sparse.cpp
LOBJ		:= $(LSRC:.cpp=.o)


.PHONY		: defreport optreport clean depend all verify %.test
.SUFFIXES	: .exe .test
.PRECIOUS   : %.o
.DEFAULT_GOAL = all

all		: $(TARGETS) $(TESTS)

ALLTESTS	:= $(TARGETS:.exe=.test) $(TESTS:.exe=.test)

verify		: $(ALLTESTS)

%.test		: %.exe
		  ./$^

%.exe   	: %.o $(LOBJ)
		  $(MPICXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

%.o 		: %.cpp
		  $(MPICXX) -c $(CXXFLAGS) $< -o $@

%.s 		: %.cpp
		  $(MPICXX) -S $(CXXFLAGS) $<

defreport	:
		  $(MPICXX) -dM -E -x c++ /dev/null

optreport	:
		  echo 'int;' | $(MPICXX) -xc++ $(CXXFLAGS) - -o /dev/null -\#\#\#

clean		:
		  /bin/rm -f $(TARGETS) $(TESTS) $(OBJECTS) $(PCHS) Matrix.s a.out *~ Makefile.bak makedep slurm-[0-7]*.out

depend		: 
	@ $(MPICXX) -MM -x c++ $(LANG) $(INCLUDES) $(SOURCES) $(XSRC) > makedep
	@ echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	@ echo '$$r makedep' >>eddep
	@ echo 'w' >>eddep
	@ cp Makefile Makefile.bak
	@ ed - Makefile < eddep
	@ /bin/rm eddep makedep
	@ echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	@ echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	@ echo '# see make depend above' >> Makefile

