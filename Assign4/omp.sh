#!/bin/bash

# list of threads
thread_list=(1 2 4 8 16 20 22 24 26 27 28 29 30 32 64 128)

mkdir -p grav_data/result1000
export OMPI_MCA_mpi_warn_on_fork=0

for threads in "${thread_list[@]}"; do
    export OMP_NUM_THREADS=$threads
    #echo "Running with $OMP_NUM_THREADS threads"

    total_time=0
    for i in {1..10}; do
        output=$(./bin/runprog)
        #echo "Run $i: $output"
        time=$(echo "$output" | grep -oP '\d+\.\d+')
        total_time=$(echo "$total_time + $time" | bc)
    done

    # caluculate avarage time
    avg_time=$(echo "scale=10; $total_time / 10" | bc)
    printf "Average time for %2d threads: %.8f s\n" "$threads" "$avg_time"
    printf "%d %.8f\n" "$threads" "$avg_time" >> grav_data/result1000/avg_times.txt

    echo "$threads $avg_time" >> grav_data/result1000/avg_times.txt
done
