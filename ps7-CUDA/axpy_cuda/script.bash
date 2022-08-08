#!/bin/bash


make clean
make all




for program in cu_axpy_1; do
    /bin/rm -f ${program}.txt
    printf "\n"
    printf "=== ${program} ===\n"
    printf "N\tgflops\n" > ${program}.txt
    for size in 20 21 22 23 ; do
      printf "${size}\t" >> ${program}.txt
	./${program}.exe ${size} | fgrep flop | awk '{print $8}' >> ${program}.txt

    done
done



for program in cu_axpy_2 cu_axpy_3 seq_axpy omp_axpy cu_axpy_t ; do
    /bin/rm -f ${program}.txt
    printf "\n"
    printf "=== ${program} ===\n"
    printf "N\tgflops\n" > ${program}.txt
    for size in 20 21 22 23 24 25 26 27; do
      printf "${size}\t" >> ${program}.txt
	./${program}.exe ${size} | fgrep flop | awk '{print $8}' >> ${program}.txt

    done
done


