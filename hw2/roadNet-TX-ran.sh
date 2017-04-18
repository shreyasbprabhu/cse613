#!/bin/bash  
#SBATCH --job-name="task1d_roadNet-TX"  
#SBATCH --output="results/task1d_roadNet-TX.%j.%N.out"  
#SBATCH -e "results/task1d_roadNet-TX.%j.%N.err"  
#SBATCH --partition=compute  
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=24
#SBATCH --export=ALL  
#SBATCH -t 03:10:00  

#Run the job using mpirun_rsh  
./par-ran-cc <test/roadNet-TX-in.txt 
