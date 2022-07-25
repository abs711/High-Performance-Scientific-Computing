#!/bin/bash

. ./common.bash

export SMALL=/gscratch/amath/amath583/data/celebA/celebA_gray_lowres.262781_55_45_32.bin
export MED=/gscratch/amath/amath583/data/celebA/celebA_gray_lowres.202599_109_89_32.bin
export LARGE=/gscratch/amath/amath583/data/celebA/celebA_gray_lowres.202599_218_178_32.bin

export IMAGES=500
export FACES=8

make clean
make 
/bin/rm verify.txt slurm-verify.out
touch verify.txt  slurm-verify.out

printf "time\tgflops/s\n" | tee -a verify.txt

job=`sbatch --nodes=1 relay.bash ./eigenfaces_seq.exe -i ${SMALL} -n ${IMAGES} -f ${FACES} | awk '{ print $4 }'`
wait_for_job "${job}" verify

job=`sbatch --nodes=1 relay.bash ./eigenfaces_opt.exe -i ${SMALL} -n ${IMAGES} -f ${FACES} | awk '{ print $4 }'`
wait_for_job "${job}" verify

job=`sbatch --nodes=1 --cpus-per-task=20 relay.bash ./eigenfaces_par.exe -i ${SMALL} -n ${IMAGES} -f ${FACES} | awk '{ print $4 }'`
wait_for_job "${job}" verify

# See note in assignment if you are using dgemm in your mpi
job=`MKL_NUM_THREADS=10 sbatch --nodes=4 --cpus-per-task=10 relay.bash mpirun ./eigenfaces_mpi.exe -i ${SMALL} -n ${IMAGES} -f ${FACES} | awk '{ print $4 }'`
wait_for_job "${job}" verify

diff -q mean_face_seq_500_55_45.bmp mean_face_opt_500_55_45.bmp | tee -a verify.txt
diff -q mean_face_seq_500_55_45.bmp mean_face_par_500_55_45.bmp | tee -a verify.txt
diff -q mean_face_seq_500_55_45.bmp mean_face_mpi_500_55_45.bmp | tee -a verify.txt

diff -q u_seq_0_500_55_45.bmp u_opt_0_500_55_45.bmp | tee -a verify.txt
diff -q u_seq_0_500_55_45.bmp u_par_0_500_55_45.bmp | tee -a verify.txt
diff -q u_seq_0_500_55_45.bmp u_mpi_0_500_55_45.bmp | tee -a verify.txt

diff -q u_seq_7_500_55_45.bmp u_opt_7_500_55_45.bmp | tee -a verify.txt
diff -q u_seq_7_500_55_45.bmp u_par_7_500_55_45.bmp | tee -a verify.txt
diff -q u_seq_7_500_55_45.bmp u_mpi_7_500_55_45.bmp | tee -a verify.txt


# Uncomment the following for 583
 job=`sbatch --nodes=1 --cpus-per-task=20 relay.bash ./eigenfaces_block.exe -i ${SMALL} -n ${IMAGES} -f ${FACES} | awk '{ print $4 }'`
 wait_for_job "${job}" verify
 diff -q mean_face_seq_500_55_45.bmp mean_face_block_500_55_45.bmp | tee -a verify.txt
 diff -q u_seq_0_500_55_45.bmp u_block_0_500_55_45.bmp | tee -a verify.txt
 diff -q u_seq_7_500_55_45.bmp u_block_7_500_55_45.bmp | tee -a verify.txt


# Uncomment the following if you are doing extra credit
 job=`sbatch --nodes=4 --cpus-per-task=10 relay.bash ./eigenfaces_dgemm.exe -i ${SMALL} -n ${IMAGES} -f ${FACES} | awk '{ print $4 }'`
 wait_for_job "${job}" verify
 diff -q mean_face_seq_500_55_45.bmp mean_face_dgemm_500_55_45.bmp | tee -a verify.txt
 diff -q u_seq_0_500_55_45.bmp u_dgemm_0_500_55_45.bmp | tee -a verify.txt
 diff -q u_seq_7_500_55_45.bmp u_dgemm_7_500_55_45.bmp | tee -a verify.txt

tar zcf verify-images.tar.gz u_*_[07]_500_55_45.bmp mean_face_*_500_55_45.bmp
