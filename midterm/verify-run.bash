#!/bin/bash
 
# "-DHOISTED" 

. verify-opts.bash
 
for DEFS in "${ALLDEFS[@]}"; do
    make clean
    make DEFS="${DEFS}" matvec_test.exe matmat_test.exe matvec.exe matmat.exe
    ./matvec_test.exe
    ./matmat_test.exe
    ./matvec.exe
    ./matmat.exe
done
