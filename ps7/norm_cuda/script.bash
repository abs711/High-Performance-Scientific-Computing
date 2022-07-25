#!/bin/bash

make clean
make all

for program in cu_norm_0 cu_norm_1 cu_norm_2 cu_norm_3 cu_norm_4 ; do
    /bin/rm -f ${program}.txt
    printf "\n"
    printf "=== ${program} ===\n"
    printf "N\tgflops\n" > ${program}.txt
    for size in 20 21 22 23 24 25 26 27; do
      printf "${size}\t" >> ${program}.txt
	./${program}.exe ${size} | fgrep flop | awk '{print $8}' >> ${program}.txt

    done
done


