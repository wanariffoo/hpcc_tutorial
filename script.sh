#!/bin/bash

#SBATCH --job-name={your-job-name}
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:05:00
#SBATCH --partition=short
#SBATCH --mem=80000
#SBATCH --workdir=/sdhome/hpclecture/{your-folder-name}/hpcc_tutorial
#SBATCH --output=/sdhome/hpclecture/{your-folder-name}/hpcc_tutorial/%j.out


module load mpi
module load intel/2018
module load intel

mpirun -n ${SLURM_NTASKS} ./bin/psfem

