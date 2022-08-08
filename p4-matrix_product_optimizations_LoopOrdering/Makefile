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
DEFS		:= 

CXXFLAGS	+= $(LANG) $(DEFS) $(OPTS) $(DEBUG) $(PROFILE) $(PICKY) 

TESTS		:= mmult_ps3_test.exe mmult_test.exe mmult_trans_test.exe 
TARGETS		:= bandwidth.exe roofline.exe cpuinfo583.exe mmult_ps3.exe mmult.exe mmult_trans.exe 
SOURCES		:= $(TARGETS:.exe=.cpp) $(TESTS:.exe=.cpp) amath583.cpp
HEADERS		:= $(SOURCES:.cpp=.hpp)
OBJECTS		:= $(SOURCES:.cpp=.o)
PCHS		:= $(HEADERS:=.gch)


.PHONY		: defreport optreport clean depend all

all		: $(TARGETS)

%.exe        	: %.o
		  $(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

%.o 		: %.cpp
		  $(CXX) -c $(CXXFLAGS) $< -o $@

%.s 		: %.cpp
		  $(CXX) -S $(CXXFLAGS) $<

mmult_ps3_test.exe	: mmult_ps3_test.o amath583.o
mmult_test.exe		: mmult_test.o amath583.o
mmult_trans_test.exe	: mmult_trans_test.o amath583.o

mmult_ps3.exe	: mmult_ps3.o amath583.o
mmult.exe	: mmult.o amath583.o
mmult_trans.exe	: mmult_trans.o amath583.o

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
bandwidth.o: bandwidth.cpp Timer.hpp kernels.hpp
roofline.o: roofline.cpp Timer.hpp kernels.hpp
cpuinfo583.o: cpuinfo583.cpp
mmult_ps3.o: mmult_ps3.cpp Matrix.hpp amath583.hpp Vector.hpp Timer.hpp
mmult.o: mmult.cpp Matrix.hpp amath583.hpp Vector.hpp Timer.hpp
mmult_trans.o: mmult_trans.cpp Matrix.hpp amath583.hpp Vector.hpp \
  Timer.hpp
mmult_ps3_test.o: mmult_ps3_test.cpp catch.hpp Matrix.hpp amath583.hpp \
  Vector.hpp
mmult_test.o: mmult_test.cpp catch.hpp Matrix.hpp amath583.hpp Vector.hpp
mmult_trans_test.o: mmult_trans_test.cpp catch.hpp Matrix.hpp \
  amath583.hpp Vector.hpp
amath583.o: amath583.cpp amath583.hpp Matrix.hpp Vector.hpp
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
