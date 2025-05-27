#!/bin/bash

# initial value
value=256

# Repeat Count
count=12

# Loop and run the executable file
for ((i=1; i<=count; i++)); do
    mpirun ./bin/runprog "$value"
    value=$((value * 2))
done
