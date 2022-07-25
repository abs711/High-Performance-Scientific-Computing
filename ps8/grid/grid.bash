#!/bin/bash

#SBATCH --account=amath
#SBATCH --partition=ckpt
#SBATCH --job-name=mpi-grid		# Job name
#SBATCH --time=00:05:00   		# Time limit hrs:min:sec
#SBATCH --ntasks-per-node=1		# How many tasks on each node
#SBATCH --cpus-per-task=1		# Number of cores per MPI rank
#SBATCH --distribution=cyclic:cyclic 	# Distribute tasks cyclically on nodes and sockets

echo "Starting parallel grid"

mpirun ./grid.exe -p ${*}

echo "Done with parallel grid"
