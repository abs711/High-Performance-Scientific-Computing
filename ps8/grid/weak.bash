#!/bin/bash

echo "Weak scaling tests"
make clean
make grid.exe

for size in 128 256 512 1024 2048
do

/bin/rm -f weak${size}.out.txt
touch weak${size}.out.txt

printf "${size}\n" | tee -a weak${size}.out.txt
printf "size\tprocs\ttime\n" | tee -a weak${size}.out.txt
for nodes in 1 2 4 8 16 
do
    echo ${nodes} nodes
    let "xsize = ${size} * ${nodes}"

    job=`sbatch --nodes ${nodes} grid.bash -m 128 -j -x $xsize -y $size | awk '{ print $4 }'`

    echo job ${job}

  while [ `squeue -h -j${job} -r | wc -l` == "1" ]
  do
      printf "."
      sleep 2
  done
  printf "\n"
  time=`fgrep elapsed slurm-${job}.out | awk '{print $5}'`
  printf "${size}\t${nodes}\t${time}\n" | tee -a weak${size}.out.txt

done

done

python3 plot.py weak128.out.txt weak256.out.txt weak512.out.txt weak1024.out.txt weak2048.out.txt
mv time.pdf weak.pdf
