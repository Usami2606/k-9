#!/bin/bash

value=4096
count=10

for ((i=1; i<=count; i++)); do
    sum=0

    result=$(mpirun  -rf rankfile -report-bindings ./bin/runprog "$value")
    #result=$(mpirun -report-bindings ./bin/runprog "$value")
    echo "$result"
    
    value=$((value * 2))
done
