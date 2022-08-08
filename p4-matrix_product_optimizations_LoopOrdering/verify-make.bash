#!/bin/bash
 
. verify-opts.bash
 
for DEFS in "${ALLDEFS[@]}"; do
    for OPTS in "${ALLOPTS[@]}"; do
	make clean
	make mmult_ps3.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make mmult.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make mmult_trans.exe  DEFS="${DEFS}" OPTS="${OPTS}"
    done
done
