#!/bin/bash

value=6250
count=8
repeat=100

for ((i=1; i<=count; i++)); do
    sum=0
    max=""
    min=""
    
    for ((j=1; j<=repeat; j++)); do
        result=$(mpirun  -rf rankfile -report-bindings ./bin/runprog "$value")
        #result=$(mpirun ./bin/runprog "$value")
        sum=$(echo "$sum + $result" | bc)

        if [[ -z "$max" || $(echo "$result > $max" | bc) -eq 1 ]]; then
            max=$result
        fi
        
        if [[ -z "$min" || $(echo "$result < $min" | bc) -eq 1 ]]; then
            min=$result
        fi
    done
    
    avg=$(echo "scale=6; $sum / $repeat" | bc)
    echo "Value: $value, Average: $avg, Max: $max, Min: $min"
    
    value=$((value * 2))
done
