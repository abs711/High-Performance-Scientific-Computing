#!/bin/bash
 
. verify-opts.bash

declare -a MVTESTS=("Identify" "Singular" "Singular Transpose" "Sherman" "Sherman Transpose")
declare -a MMTESTS=('Coordinate Matrix' 'Compressed Sparse Row Matrix' 'Compressed Sparse Column Matrix' 'Array of Structs Matrix')
 
for DEFS in "${ALLDEFS[@]}"; do
    for OPTS in "${ALLOPTS[@]}"; do
#	make clean

	echo make matvec_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make matvec_test.exe       DEFS="${DEFS}" OPTS="${OPTS}"

	./matvec_test.exe Identity

	./matvec_test.exe Singular

	./matvec_test.exe 'Singular Transpose'

	./matvec_test.exe Sherman

	./matvec_test.exe 'Sherman Transpose'

	echo make matmat_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make matmat_test.exe       DEFS="${DEFS}" OPTS="${OPTS}"

	for T in "${MMTESTS[@]}"; do
            ./matmat_test.exe "${T}"
	done
    done
done





