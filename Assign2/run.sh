#!/bin/bash

# Initial number of threads
threads=1

# Maximum number of threads (256)
max_threads=256

# Repeat until the number of threads exceeds the maximum
while [ $threads -le $max_threads ]; do
    # Set OMP_NUM_THREADS
    export OMP_NUM_THREADS=$threads

    # execution
    echo "Running with $OMP_NUM_THREADS threads"
    ./bin/runprog

    # Double the number of threads
    threads=$((threads * 2))
done


#!/bin/bash

# # 引数チェック
# if [ -z "$1" ]; then
#     echo "Usage: $0 <num_threads>"
#     exit 1
# fi

# # 引数でスレッド数を設定
# export OMP_NUM_THREADS=$1

# # 実行
# echo "Running with $OMP_NUM_THREADS threads"
# ./bin/runprog

