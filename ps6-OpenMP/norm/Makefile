#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#


TARGETS		:= norm_seq.exe norm_parfor.exe \
		   norm_block_critical.exe norm_block_reduction.exe norm_cyclic_critical.exe norm_cyclic_reduction.exe

TESTS		:= 

include ../include/Make.inc  # DRY -- logic moved to include file


# The following 4 (yes 4) lines must be in all the subdirectory makefiles
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
norm_seq.o: norm_seq.cpp ../include/norms.hpp ../include/Timer.hpp \
 ../include/Vector.hpp ../include/amath583.hpp ../include/Matrix.hpp \
 ../include/norm_utils.hpp
norm_parfor.o: norm_parfor.cpp ../include/norm_utils.hpp \
 ../include/Timer.hpp ../include/Vector.hpp ../include/amath583.hpp \
 ../include/Matrix.hpp ../include/norms.hpp
norm_block_critical.o: norm_block_critical.cpp ../include/norm_utils.hpp \
 ../include/Timer.hpp ../include/Vector.hpp ../include/amath583.hpp \
 ../include/Matrix.hpp ../include/norms.hpp
norm_block_reduction.o: norm_block_reduction.cpp \
 ../include/norm_utils.hpp ../include/Timer.hpp ../include/Vector.hpp \
 ../include/amath583.hpp ../include/Matrix.hpp ../include/norms.hpp
norm_cyclic_critical.o: norm_cyclic_critical.cpp \
 ../include/norm_utils.hpp ../include/Timer.hpp ../include/Vector.hpp \
 ../include/amath583.hpp ../include/Matrix.hpp ../include/norms.hpp
norm_cyclic_reduction.o: norm_cyclic_reduction.cpp \
 ../include/norm_utils.hpp ../include/Timer.hpp ../include/Vector.hpp \
 ../include/amath583.hpp ../include/Matrix.hpp ../include/norms.hpp
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
