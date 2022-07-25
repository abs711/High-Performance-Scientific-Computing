# -*- mode:Makefile -*-
#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#

CXX	    	:= c++
NVCC		:= nvcc

# Maximum optimization effort: -Ofast -march=native -DNDEBUG
OPTS        	:= -Ofast -march=native -DNDEBUG
DEBUG		:= # -g -O0 -fsanitize=address
PROFILE		:= 
LANG        	:= -std=c++14
PICKY       	:= -Wall
DIAG		:= # -Rpass=.*
INCLUDES	:= -I../include

CUHOME		:= /sw/cuda/11.2.2/
CUDEFS	    	:= --extended-lambda
CUOPTS      	:= -O3 -DNDEBUG
CUINCLUDES  	:= -I$(CUHOME)/samples/common/inc

VPATH		= ../include:../src

CXXFLAGS	+= $(DEFS) $(XDEFS) $(OPTS) $(DEBUG) $(PROFILE) $(LANG) $(PICKY) $(DIAG) $(INCLUDES) 
NVCCFLAGS	+= $(CUOPTS) $(CUDEBUG) $(CUINCLUDES) $(CUDEFS) $(CUDIAG) $(CUPICKY)
NVCCFLAGS   	+= $(DEFS) $(PROFILE) $(LANG) $(INCLUDES) 


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
HEADERS		= $(SOURCES:.cpp=.hpp) $(LINC)
OBJECTS		= $(SOURCES:.cpp=.o)   $(LOBJ)
PCHS		= $(HEADERS:=.gch)

CUSOURCES	= $(CUTARGETS:.exe=.cu) $(CUTESTS:.exe=.cu) 
CUOBJECTS	= $(CUSOURCES:.cu=.o)


$SHELL		= bash

LSRC		:= amath583.cpp amath583IO.cpp amath583sparse.cpp
LINC		:= $(LSRC:.cpp=.hpp)
XSRC		:= ../src/amath583.cpp ../src/amath583IO.cpp ../src/amath583sparse.cpp
LOBJ		:= $(LSRC:.cpp=.o)

.PHONY		: defreport optreport clean depend all verify %.test
.SUFFIXES	: .exe .test
.PRECIOUS   : %.o
.DEFAULT_GOAL = all

all			: $(TARGETS) $(TESTS) $(CUTARGETS) $(CUTESTS)

ALLTESTS	:= $(TARGETS:.exe=.test) $(TESTS:.exe=.test) $(CUTARGETS:.exe=.test) $(CUTESTS:.exe=.test)

verify		: $(ALLTESTS)

%.test		: %.exe
		  ./$^

%.exe   	: %.o # $(LOBJ)
		  $(NVCC) $(NVCCFLAGS) $^ -o $@ $(LIBS)

%.o 		: %.cpp
		  $(CXX) -c $(CXXFLAGS) $< -o $@

%.o     	: %.cu
		  $(NVCC) -c $(NVCCFLAGS) $< -o $@

%.s 		: %.cpp
		  $(CXX) -S $(CXXFLAGS) $<

defreport	:
		  $(CXX) -dM -E -x c++ /dev/null

optreport	:
		  echo 'int;' | $(CXX) -xc++ $(CXXFLAGS) - -o /dev/null -\#\#\#

clean		:
		  /bin/rm -f $(TARGETS) $(TESTS) $(OBJECTS) $(CUTARGETS) $(CUTESTS) $(CUOBJECTS) $(PCHS) Matrix.s a.out *~ Makefile.bak makedep

depend		: 
	@ $(CXX) -MM -x c++ $(LANG) $(INCLUDES) $(CUINCLUDES) $(SOURCES) $(CUSOURCES) $(XSRC) > makedep
	@ echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	@ echo '$$r makedep' >>eddep
	@ echo 'w' >>eddep
	@ cp Makefile Makefile.bak
	@ ed - Makefile < eddep
	@ /bin/rm eddep makedep
	@ echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	@ echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	@ echo '# see make depend above' >> Makefile

