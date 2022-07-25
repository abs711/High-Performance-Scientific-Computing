#!/bin/bash
 
. verify-opts.bash
 
for DEFS in "${ALLDEFS[@]}"; do
    for OPTS in "${ALLOPTS[@]}"; do
	make clean

	echo make mmult_ps3_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make mmult_ps3_test.exe       DEFS="${DEFS}" OPTS="${OPTS}"
	./mmult_ps3_test.exe

	echo make mmult_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make mmult_test.exe       DEFS="${DEFS}" OPTS="${OPTS}"
	./mmult_test.exe
	
	echo make mmult_trans_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make mmult_trans_test.exe       DEFS="${DEFS}" OPTS="${OPTS}"
	./mmult_trans_test.exe
    done
done





