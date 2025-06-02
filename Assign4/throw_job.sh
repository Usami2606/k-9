#!/bin/bash
mkdir -p report/mpi

sbatch -p bdw-mixed -N 4 -n 28 --ntasks-per-core=2 -o ./report/mpi/out%J_mpi -e ./report/mpi/err%J_mpi mpi.sh
#sbatch -p bdw-mixed -N 1 -n 6 --ntasks-per-core=1 -o ./report/mpi/out%J_mpi -e ./report/mpi/err%J_mpi hybrid.sh