#!/bin/bash
 
# "-DHOISTED" 

. verify-opts.bash
 
for DEFS in "${ALLDEFS[@]}"; do
    make clean
    make mmult_ps3.exe mmult.exe mmult_trans.exe  DEFS="${DEFS}" 
    ./mmult_ps3.exe
    ./mmult.exe
    ./mmult_trans.exe
done
