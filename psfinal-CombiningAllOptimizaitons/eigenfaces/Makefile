#
# This file is part of the course materials for AMATH 483/583 at the University of Washington,
# Spring 2021
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
# 

TARGETS	 := eigenfaces_seq.exe eigenfaces_opt.exe eigenfaces_par.exe eigenfaces_block.exe eigenfaces_mpi.exe eigenfaces_dgemm.exe
TESTS    := test.exe

include ../include/Make_mpi.inc


# The following 4 (yes 4) lines must be in all the subdirectory makefiles
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
eigenfaces_seq.o: eigenfaces_seq.cpp ../include/amath583.hpp \
 ../include/Matrix.hpp ../include/Vector.hpp main.hpp ../include/CImg.h \
 ../include/Timer.hpp ../include/face_db.hpp ../include/amath583.hpp \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_lapack.h \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_types.h
eigenfaces_opt.o: eigenfaces_opt.cpp ../include/amath583.hpp \
 ../include/Matrix.hpp ../include/Vector.hpp main.hpp ../include/CImg.h \
 ../include/Timer.hpp ../include/face_db.hpp ../include/amath583.hpp \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_lapack.h \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_types.h
eigenfaces_par.o: eigenfaces_par.cpp ../include/amath583.hpp \
 ../include/Matrix.hpp ../include/Vector.hpp main.hpp ../include/CImg.h \
 ../include/Timer.hpp ../include/face_db.hpp ../include/amath583.hpp \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_lapack.h \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_types.h
eigenfaces_block.o: eigenfaces_block.cpp ../include/amath583.hpp \
 ../include/Matrix.hpp ../include/Vector.hpp main.hpp ../include/CImg.h \
 ../include/Timer.hpp ../include/face_db.hpp ../include/amath583.hpp \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_lapack.h \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_types.h
eigenfaces_mpi.o: eigenfaces_mpi.cpp ../include/CImg.h \
 /mmfs1/sw/intel/oneAPI/2021.1.0.2659/mpi/2021.1.1/include/mpi.h \
 /mmfs1/sw/intel/oneAPI/2021.1.0.2659/mpi/2021.1.1/include/mpio.h \
 /mmfs1/sw/intel/oneAPI/2021.1.0.2659/mpi/2021.1.1/include/mpi.h \
 /mmfs1/sw/intel/oneAPI/2021.1.0.2659/mpi/2021.1.1/include/mpicxx.h \
 ../include/Timer.hpp ../include/amath583.hpp ../include/Matrix.hpp \
 ../include/Vector.hpp ../include/face_db.hpp ../include/amath583.hpp \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_lapack.h \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_types.h
eigenfaces_dgemm.o: eigenfaces_dgemm.cpp ../include/amath583.hpp \
 ../include/Matrix.hpp ../include/Vector.hpp \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_cblas.h \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_types.h \
 main.hpp ../include/CImg.h ../include/Timer.hpp ../include/face_db.hpp \
 ../include/amath583.hpp \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_lapack.h
test.o: test.cpp ../include/catch.hpp ../include/amath583.hpp \
 ../include/Matrix.hpp ../include/Vector.hpp eigenfaces_seq.cpp main.hpp \
 eigenfaces_opt.cpp eigenfaces_par.cpp eigenfaces_block.cpp \
 eigenfaces_dgemm.cpp \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_cblas.h \
 /sw/intel/oneAPI/2021.1.0.2659/mkl/2021.1.1//include/mkl_types.h
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
