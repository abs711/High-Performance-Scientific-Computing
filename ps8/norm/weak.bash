#!/bin/bash

echo "Weak scaling tests"
make clean
make mpi_norm.exe

for size in 20 21 22 23
do

    /bin/rm -f weak${size}.out.txt
    touch weak${size}.out.txt
    
    printf "${size}\n" | tee -a weak${size}.out.txt
    printf "size\tprocs\ttime\tms_per\tgflops\n" | tee -a weak${size}.out.txt
    let "xsize = ${size}"
    for nodes in 1 2 4 8 16 
    do
	echo $nodes nodes
	
	job=`sbatch --nodes=${nodes} mpi_norm.bash ${xsize} | awk '{ print $4 }'`
	
	echo job ${job}
	
	while [ `squeue -h -j${job} -r | wc -l` == "1" ]
	do
	    printf "."
	    sleep 2
	done
	printf "\n"
	time=`fgrep elapsed slurm-${job}.out | awk '{print $5}'`
	gflops=`fgrep gflops slurm-${job}.out | awk '{print $6}'`
	ms_per=`fgrep msec_per slurm-${job}.out | awk '{print $5}'`
	printf "${size}\t${nodes}\t${time}\t${ms_per}\t${gflops}\n" | tee -a weak${size}.out.txt
	
	let "xsize = ${xsize} + 1"
	
    done
    
done

python3 plot.py weak20.out.txt weak21.out.txt weak22.out.txt weak23.out.txt
mv time.pdf weak.pdf
