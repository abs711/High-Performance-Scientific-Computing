#!/bin/bash
 
. verify-opts.bash
 
for DEFS in "${THEDEFS[@]}"; do
  for OPTS in "${THEOPTS[@]}"; do
    make clean
    for TARGET in "${THETARGETS[@]}"; do
 	make ${TARGET}  DEFS="${DEFS}" OPTS="${OPTS}"
        ./${TARGET}
    done
  done
done
