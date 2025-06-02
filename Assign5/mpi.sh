#!/bin/bash

mkdir -p grav_data/result1000

export OMPI_MCA_mpi_warn_on_fork=0

total_time=0

for i in {1..10}; do
    output=$(mpirun -report-bindings ./bin/runprog)
    time=$(echo "$output" | grep -oP '\d+\.\d+')
    total_time=$(echo "$total_time + $time" | bc)
done

avg_time=$(echo "scale=6; $total_time / 10" | bc)
echo 0$avg_time
