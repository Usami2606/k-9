#!/bin/bash
mkdir -p report/mpi
export OMP_NUM_THREADS=24
sbatch -p bdw-mixed -N 1 -n 1 --ntasks-per-core=1 -o ./report/mpi/out%J_mpi -e ./report/mpi/err%J_mpi hybrid.sh