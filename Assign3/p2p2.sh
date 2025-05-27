#!/bin/bash

# initial value
value=6250

# 繰り返し回数
count=8

for ((i=1; i<=count; i++)); do
    mpirun ./bin/runprog "$value"
    value=$((value * 2))
done
