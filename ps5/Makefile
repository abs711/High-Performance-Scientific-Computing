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

OPTS            := -Ofast -march=native -DNDEBUG
#DEBUG		:= -g -O0 -fno-omit-frame-pointer -fsanitize=address
#PROFILE	:= -g -fno-omit-frame-pointer
LANG            := -std=c++17
PICKY           := -Wall

OS              := $(shell uname -s)
ifeq ($(OS),Linux)
        LIBS    += -lpthread
endif

CXXFLAGS	+= $(LANG) $(DEFS) $(OPTS) $(DEBUG) $(PROFILE) $(PICKY)

TESTS		:= norm_test.exe pnorm_test.exe fnorm_test.exe cnorm_test.exe rnorm_test.exe \
			   matvec_test.exe pmatvec_test.exe pagerank_test.exe 
TARGETS		:= bonnie_and_clyde.exe bonnie_and_clyde_function_object.exe norm_order.exe \
			   pnorm.exe fnorm.exe cnorm.exe rnorm.exe \
			   matvec.exe pmatvec.exe pagerank.exe 
SOURCES		:= $(TARGETS:.exe=.cpp) $(TESTS:.exe=.cpp) amath583.cpp amath583IO.cpp amath583sparse.cpp 
HEADERS		:= $(SOURCES:.cpp=.hpp)
OBJECTS		:= $(SOURCES:.cpp=.o)
PCHS		:= $(HEADERS:=.gch)

LSRC		:= amath583.cpp amath583IO.cpp amath583sparse.cpp 
LOBJ		:= $(LSRC:.cpp=.o)


.PHONY		: defreport optreport clean depend all

all		: $(TARGETS)

%.exe        	: %.o
		  $(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

%.o 		: %.cpp
		  $(CXX) -c $(CXXFLAGS) $< -o $@

%.s 		: %.cpp
		  $(CXX) -S $(CXXFLAGS) $<


norm_order.exe	  : norm_order.o    $(LOBJ)

pnorm.exe         : pnorm.o         $(LOBJ)
fnorm.exe         : fnorm.o         $(LOBJ)
cnorm.exe         : cnorm.o         $(LOBJ)
rnorm.exe         : rnorm.o         $(LOBJ)

matvec.exe        : matvec.o        $(LOBJ)
pmatvec.exe       : pmatvec.o       $(LOBJ)
pagerank.exe	  : pagerank.o      $(LOBJ)

norm_test.exe	  : norm_test.o     $(LOBJ)
pnorm_test.exe	  : pnorm_test.o    $(LOBJ)
fnorm_test.exe	  : fnorm_test.o    $(LOBJ)
cnorm_test.exe	  : cnorm_test.o    $(LOBJ)
rnorm_test.exe	  : rnorm_test.o    $(LOBJ)

matvec_test.exe   : matvec_test.o   $(LOBJ)
pmatvec_test.exe  : pmatvec_test.o  $(LOBJ)
pagerank_test.exe : pagerank_test.o $(LOBJ)


defreport	:
		  $(CXX) -dM -E -x c++ /dev/null

optreport	:
		  echo 'int;' | $(CXX) -xc++ $(CXXFLAGS) - -o /dev/null -\#\#\#

clean		:
		  /bin/rm -f $(TESTS) $(TARGETS) $(OBJECTS) $(PCHS) Matrix.s a.out *~ Makefile.bak

depend		: 
	@ $(CXX) -MM $(LANG) $(INCLUDES) $(SOURCES) > makedep
	@ echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	@ echo '$$r makedep' >>eddep
	@ echo 'w' >>eddep
	@ cp Makefile Makefile.bak
	@ ed - Makefile < eddep
	@ /bin/rm eddep makedep
	@ echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	@ echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	@ echo '# see make depend above' >> Makefile

# The following 4 (yes 4) lines must be in all the subdirectory makefiles
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
bonnie_and_clyde.o: bonnie_and_clyde.cpp
bonnie_and_clyde_function_object.o: bonnie_and_clyde_function_object.cpp
norm_order.o: norm_order.cpp Vector.hpp amath583.hpp Matrix.hpp
pnorm.o: pnorm.cpp pnorm.hpp Timer.hpp Vector.hpp amath583.hpp Matrix.hpp \
  norm_utils.hpp
fnorm.o: fnorm.cpp fnorm.hpp Timer.hpp Vector.hpp amath583.hpp Matrix.hpp \
  norm_utils.hpp
cnorm.o: cnorm.cpp cnorm.hpp Timer.hpp Vector.hpp amath583.hpp Matrix.hpp \
  norm_utils.hpp
rnorm.o: rnorm.cpp rnorm.hpp Timer.hpp Vector.hpp amath583.hpp Matrix.hpp \
  norm_utils.hpp
matvec.o: matvec.cpp COOMatrix.hpp Matrix.hpp Vector.hpp CSCMatrix.hpp \
  CSRMatrix.hpp Timer.hpp amath583.hpp amath583sparse.hpp AOSMatrix.hpp
pmatvec.o: pmatvec.cpp COOMatrix.hpp Matrix.hpp Vector.hpp CSCMatrix.hpp \
  CSRMatrix.hpp Timer.hpp amath583.hpp amath583sparse.hpp AOSMatrix.hpp
pagerank.o: pagerank.cpp pagerank.hpp COOMatrix.hpp Matrix.hpp Vector.hpp \
  CSCMatrix.hpp CSRMatrix.hpp Timer.hpp amath583.hpp amath583IO.hpp \
  AOSMatrix.hpp amath583sparse.hpp
norm_test.o: norm_test.cpp catch.hpp Vector.hpp amath583.hpp Matrix.hpp
pnorm_test.o: pnorm_test.cpp catch.hpp pnorm.hpp Timer.hpp Vector.hpp \
  amath583.hpp Matrix.hpp norm_utils.hpp
fnorm_test.o: fnorm_test.cpp catch.hpp fnorm.hpp Timer.hpp Vector.hpp \
  amath583.hpp Matrix.hpp norm_utils.hpp
cnorm_test.o: cnorm_test.cpp catch.hpp cnorm.hpp Timer.hpp Vector.hpp \
  amath583.hpp Matrix.hpp norm_utils.hpp
rnorm_test.o: rnorm_test.cpp catch.hpp rnorm.hpp Timer.hpp Vector.hpp \
  amath583.hpp Matrix.hpp norm_utils.hpp
matvec_test.o: matvec_test.cpp catch.hpp COOMatrix.hpp Matrix.hpp \
  Vector.hpp CSCMatrix.hpp CSRMatrix.hpp amath583.hpp amath583IO.hpp \
  AOSMatrix.hpp amath583sparse.hpp
pmatvec_test.o: pmatvec_test.cpp catch.hpp COOMatrix.hpp Matrix.hpp \
  Vector.hpp CSCMatrix.hpp CSRMatrix.hpp amath583.hpp amath583IO.hpp \
  AOSMatrix.hpp amath583sparse.hpp
pagerank_test.o: pagerank_test.cpp pagerank.hpp COOMatrix.hpp Matrix.hpp \
  Vector.hpp CSCMatrix.hpp CSRMatrix.hpp Timer.hpp amath583.hpp \
  amath583IO.hpp AOSMatrix.hpp amath583sparse.hpp catch.hpp
amath583.o: amath583.cpp amath583.hpp Matrix.hpp Vector.hpp
amath583IO.o: amath583IO.cpp amath583IO.hpp COOMatrix.hpp Matrix.hpp \
  Vector.hpp CSRMatrix.hpp AOSMatrix.hpp CSCMatrix.hpp
amath583sparse.o: amath583sparse.cpp Matrix.hpp Vector.hpp COOMatrix.hpp \
  CSRMatrix.hpp AOSMatrix.hpp CSCMatrix.hpp amath583sparse.hpp
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
