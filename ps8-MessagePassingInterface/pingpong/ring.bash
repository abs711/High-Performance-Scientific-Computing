#!/bin/bash

#SBATCH --job-name=ring
#SBATCH --account=amath
#SBATCH --partition=ckpt
#SBATCH --time=00:00:15   		# Time limit hrs:min:sec

mpirun ./ring.exe ${*}
