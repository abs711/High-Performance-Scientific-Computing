#!/bin/bash
 
. verify-opts.bash
 
for DEFS in "${ALLDEFS[@]}"; do
    for OPTS in "${ALLOPTS[@]}"; do
	make clean
	make matvec_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make matmat_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make matvec.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make matmat.exe  DEFS="${DEFS}" OPTS="${OPTS}"
    done
done
