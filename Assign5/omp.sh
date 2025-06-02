#!/bin/bash

# スレッド数のリスト
thread_list=(1 2 4 8 16 20 22 24 26 27 28 29 30 32 36)

# 結果格納用ディレクトリ
mkdir -p grav_data/result1000
export OMPI_MCA_mpi_warn_on_fork=0

# 各スレッド数で実行
for threads in "${thread_list[@]}"; do
    export OMP_NUM_THREADS=$threads
    #echo "Running with $OMP_NUM_THREADS threads"

    total_time=0
    for i in {1..10}; do
        # 実行と出力取得（例: "Time: 1.234 s" 形式を想定）
        output=$(mpirun ./bin/runprog)
        #echo "Run $i: $output"

        # 実行時間を抽出（例：Time: 1.234 s → 1.234）
        time=$(echo "$output" | grep -oP '\d+\.\d+')
        total_time=$(echo "$total_time + $time" | bc)
    done

    # 平均を計算
    avg_time=$(echo "scale=10; $total_time / 10" | bc)
    printf "Average time for %2d threads: %.8f s\n" "$threads" "$avg_time"
    printf "%d %.8f\n" "$threads" "$avg_time" >> grav_data/result1000/avg_times.txt


    # 結果を保存
    echo "$threads $avg_time" >> grav_data/result1000/avg_times.txt
done
