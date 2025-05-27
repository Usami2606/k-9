#!/bin/bash

value=500
count=8
repeat=10

for ((i=1; i<=count; i++)); do
    sum=0
    max=""
    min=""
    
    for ((j=1; j<=repeat; j++)); do
        result=$(mpirun ./bin/runprog "$value")
        
        # 合計に加算
        sum=$(echo "$sum + $result" | bc)
        
        # max更新
        if [[ -z "$max" || $(echo "$result > $max" | bc) -eq 1 ]]; then
            max=$result
        fi
        
        # min更新
        if [[ -z "$min" || $(echo "$result < $min" | bc) -eq 1 ]]; then
            min=$result
        fi
    done
    
    avg=$(echo "scale=6; $sum / $repeat" | bc)
    echo "Value: $value, Average: $avg, Max: $max, Min: $min"
    
    value=$((value * 2))
done
