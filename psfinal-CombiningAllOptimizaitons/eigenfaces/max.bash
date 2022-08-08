#!/bin/bash

. ./common.bash

# 2.5G, 7.4G, 30G
export SMALL="-i /gscratch/amath/amath583/data/celebA/celebA_gray_lowres.262781_55_45_32.bin -n 262781"
export MED="-i /gscratch/amath/amath583/data/celebA/celebA_gray_lowres.202599_109_89_32.bin -z 109x89 -n 202599"
export LARGE="-i /gscratch/amath/amath583/data/celebA/celebA_gray_lowres.202599_218_178_32.bin -z 218x178 -n 202599"

make clean
make eigenfaces_mpi.exe
/bin/rm max.txt slurm-max.out
touch max.txt slurm-max.out

# Uncomment one of these
#export ARGS="${SMALL}"
export ARGS="${MED}"
#export ARGS="${LARGE}"

printf "time\tgflops/s\n" | tee -a max.txt

# See note in assignment if you are using dgemm in your mpi
# You will need to set MKL_NUM_THREADS to same number as cpus-per-task
# Start with reasonable values and gradually increase to 8 nodes by 40 cpus-per-task (and from SMALL to MED)
export MKL_NUM_THREADS=20
export NODES=4
job=`sbatch --time 5:00 --nodes=8 --cpus-per-task=${MKL_NUM_THREADS} relay.bash mpirun ./eigenfaces_mpi.exe ${ARGS} | awk '{ print $4 }'`
wait_for_job "${job}" max
