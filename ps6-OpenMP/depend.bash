#!/bin/bash

find . -name \*~ -exec rm {} \;

for SUBDIR in hello_omp matvec norm pagerank test; do
 cd ${SUBDIR}
 make clean
 make depend CXX=c++
 make clean
 cd ..
done


