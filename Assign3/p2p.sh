#!/bin/bash

# initial value
value=256

# 繰り返し回数
count=12

# ループして ./a.out を実行
for ((i=1; i<=count; i++)); do
    mpirun ./bin/runprog "$value"
    value=$((value * 2))
done
