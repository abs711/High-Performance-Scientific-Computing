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
#DEBUG		:= -fsanitize=address -g -O0 -fno-omit-frame-pointer
PROFILE		:= 
LANG            := -std=c++11
PICKY           := -Wall

# Leave undefined if 483, defined if 583
# DEFS		:= 
DEFS		:= -D__583


CXXFLAGS	+= $(LANG) $(DEFS) $(OPTS) $(DEBUG) $(PROFILE) $(PICKY)

TESTS		:= matvec_test.exe matmat_test.exe 
TARGETS		:= matvec.exe matmat.exe
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

matvec_test.exe	: matvec_test.o $(LOBJ)
matvec.exe	: matvec.o $(LOBJ)
matmat_test.exe	: matmat_test.o $(LOBJ)
matmat.exe	: matmat.o $(LOBJ)

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
matvec.o: matvec.cpp COOMatrix.hpp Matrix.hpp Vector.hpp CSRMatrix.hpp \
  CSCMatrix.hpp AOSMatrix.hpp amath583.hpp amath583sparse.hpp Timer.hpp
matmat.o: matmat.cpp COOMatrix.hpp Matrix.hpp Vector.hpp CSRMatrix.hpp \
  CSCMatrix.hpp AOSMatrix.hpp amath583.hpp amath583sparse.hpp Timer.hpp
matvec_test.o: matvec_test.cpp catch.hpp COOMatrix.hpp Matrix.hpp \
  Vector.hpp CSRMatrix.hpp amath583.hpp amath583IO.hpp AOSMatrix.hpp \
  CSCMatrix.hpp amath583sparse.hpp
matmat_test.o: matmat_test.cpp catch.hpp COOMatrix.hpp Matrix.hpp \
  Vector.hpp CSRMatrix.hpp amath583.hpp amath583IO.hpp AOSMatrix.hpp \
  CSCMatrix.hpp amath583sparse.hpp
amath583.o: amath583.cpp amath583.hpp Matrix.hpp Vector.hpp
amath583IO.o: amath583IO.cpp amath583IO.hpp COOMatrix.hpp Matrix.hpp \
  Vector.hpp CSRMatrix.hpp AOSMatrix.hpp CSCMatrix.hpp
amath583sparse.o: amath583sparse.cpp Matrix.hpp Vector.hpp COOMatrix.hpp \
  CSRMatrix.hpp AOSMatrix.hpp CSCMatrix.hpp amath583sparse.hpp
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
