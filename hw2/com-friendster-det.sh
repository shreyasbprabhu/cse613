#!/bin/bash  
#SBATCH --job-name="task1d_com-friendster"  
#SBATCH --output="results/task1d_com-friendster.%j.%N.out"  
#SBATCH -e "results/task1d_com-friendster.%j.%N.err"  
#SBATCH --partition=compute  
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=24
#SBATCH --export=ALL  
#SBATCH -t 03:10:00  

#Run the job using mpirun_rsh  
./par-det-cc <test/com-friendster-in.txt 
