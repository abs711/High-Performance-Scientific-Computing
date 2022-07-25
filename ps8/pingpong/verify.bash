#!/bin/bash

make clean

make pingpong.exe
sbatch --nodes=2 pingpong.bash 2
sbatch --nodes=4 pingpong.bash 2
sbatch --nodes=2 pingpong.bash 8
sbatch --nodes=2 pingpong.bash 64

make ring.exe
sbatch --nodes=2 ring.bash 2
sbatch --nodes=4 ring.bash 2
sbatch --nodes=4 ring.bash 8
sbatch --nodes=4 ring.bash 64
sbatch --nodes=16 ring.bash 64

