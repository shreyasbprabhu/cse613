#!/bin/bash  
#SBATCH --job-name="task1d_roadNet-PA"  
#SBATCH --output="results/task1d_roadNet-PA.%j.%N.out"  
#SBATCH -e "results/task1d_roadNet-PA.%j.%N.err"  
#SBATCH --partition=compute  
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=24
#SBATCH --export=ALL  
#SBATCH -t 03:10:00  

#Run the job using mpirun_rsh  
./par-det-cc <test/roadNet-PA-in.txt 
