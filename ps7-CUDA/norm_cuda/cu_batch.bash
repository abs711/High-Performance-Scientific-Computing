#!/bin/bash

#SBATCH --account=amath
#SBATCH --partition=gpu-rtx6k
#SBATCH --nodes=1
#SBATCH --cpus-per-task=20
#SBATCH --time=00:05:00
#SBATCH --gres=gpu:rtx6k

bash script.bash
