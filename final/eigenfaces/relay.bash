#!/bin/bash

#SBATCH --account=amath
#SBATCH --partition=ckpt
#SBATCH --nodes=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:02:00
#SBATCH --mem-per-cpu=4096

${*}
