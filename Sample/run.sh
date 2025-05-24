#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 <num_threads> <num_procs>"
    exit 1
fi

# 引数でスレッド数とプロセス数を設定
export OMP_NUM_THREADS=$1
NUM_PROCS=$2

# Execution
echo "Running with $OMP_NUM_THREADS threads and $NUM_PROCS MPI processes"
mpirun -np $NUM_PROCS --mca mpi_warn_on_fork 0 ./bin/runprog
