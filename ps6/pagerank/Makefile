#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#



TARGETS		:= pagerank.exe
TESTS		:= 

include ../include/Make.inc  # DRY -- logic moved to include file


# The following 4 (yes 4) lines must be in all the subdirectory makefiles
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
pagerank.o: pagerank.cpp ../include/pagerank.hpp ../include/COOMatrix.hpp \
 ../include/Matrix.hpp ../include/Vector.hpp ../include/CSCMatrix.hpp \
 ../include/CSRMatrix.hpp ../include/Timer.hpp ../include/amath583.hpp \
 ../include/amath583IO.hpp ../include/AOSMatrix.hpp \
 ../include/amath583sparse.hpp
amath583.o: ../src/amath583.cpp ../include/amath583.hpp \
 ../include/Matrix.hpp ../include/Vector.hpp ../include/Matrix.hpp \
 ../include/Vector.hpp
amath583IO.o: ../src/amath583IO.cpp ../include/amath583IO.hpp \
 ../include/COOMatrix.hpp ../include/Matrix.hpp ../include/Vector.hpp \
 ../include/CSRMatrix.hpp ../include/AOSMatrix.hpp \
 ../include/CSCMatrix.hpp ../include/COOMatrix.hpp \
 ../include/CSRMatrix.hpp ../include/Matrix.hpp ../include/Vector.hpp \
 ../include/AOSMatrix.hpp ../include/CSCMatrix.hpp
amath583sparse.o: ../src/amath583sparse.cpp ../include/Matrix.hpp \
 ../include/Vector.hpp ../include/COOMatrix.hpp ../include/Matrix.hpp \
 ../include/Vector.hpp ../include/CSRMatrix.hpp ../include/AOSMatrix.hpp \
 ../include/CSCMatrix.hpp ../include/amath583sparse.hpp \
 ../include/AOSMatrix.hpp ../include/COOMatrix.hpp \
 ../include/CSCMatrix.hpp ../include/CSRMatrix.hpp
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
