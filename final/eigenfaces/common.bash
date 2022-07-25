#!/bin/bash

function wait_for_job() {

    job=${1}

    echo job ${job}
	
    while [ `squeue -h -j${job} -r | wc -l` == "1" ]
    do
	printf "."
	sleep 2
    done
    printf "\n"
    time=`fgrep covariance slurm-${job}.out | awk '{print $5}'`
    gflops=`fgrep Gflops slurm-${job}.out | awk '{print $4}'`

    printf "${time}\t${gflops}\n" | tee -a ${2}.txt
    echo "#================================================================" >> slurm-${2}.out
    echo "# slurm-${job}.out" >> slurm-${2}.out
    echo "" >> slurm-${2}.out
    cat slurm-${job}.out >> slurm-${2}.out
    echo "" >> slurm-${2}.out
    echo "" >> slurm-${2}.out
}
