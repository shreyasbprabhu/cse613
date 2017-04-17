#!/bin/bash  
#SBATCH --job-name="task1d_com-amazon"  
#SBATCH --output="results/task1d_com-amazon.%j.%N.out"  
#SBATCH -e "results/task1d_com-amazon.%j.%N.err"  
#SBATCH --partition=compute  
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=24
#SBATCH --export=ALL  
#SBATCH -t 03:10:00  

#Run the job using mpirun_rsh  
./par-det-cc <test/com-amazon-in.txt 
