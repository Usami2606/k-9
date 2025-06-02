#!/bin/bash

# initial value
value=10

# 繰り返し回数
count=10

for ((i=1; i<=count; i++)); do
    #mpirun -rf rankfile -report-bindings bin/runprog "$value"
    mpirun -report-bindings --map-by core:pe=1 bin/runprog "$value"
    value=$((value * 1))
done
