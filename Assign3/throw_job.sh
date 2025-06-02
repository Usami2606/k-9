#!/bin/bash

mkdir -p report/p2p report/allgather report/circle

# p2p
sbatch -p bdw-mixed -N 1 -n 2 --ntasks-per-core=2 -o ./report/p2p/out%J_p2p_samecpu -e ./report/p2p/err%J_p2p_samecpu p2p.sh
#sbatch -p bdw-mixed -N 1 -n 2 --ntasks-per-core=1 -o ./report/p2p/out%J_p2p_samenode -e ./report/p2p/err%J_p2p_samenode p2p.sh
#sbatch -p bdw-mixed -N 2 -n 2 --ntasks-per-core=1 -o ./report/p2p/out%J_p2p_othernode -e ./report/p2p/err%J_p2p_othernode p2p.sh

# allgather
#sbatch -p bdw-mixed -N 1 -n 8 --ntasks-per-core=2 -o ./report/allgather/out%J__allgather_1node -e ./report/allgather/err%J_allgather_1node allgather.sh
#sbatch -p bdw-mixed -N 2 -n 8 --ntasks-per-core=2 -o ./report/allgather/out%J__allgather_2node -e ./report/allgather/err%J_allgather_2node allgather.sh
#sbatch -p bdw-mixed -N 4 -n 8 --ntasks-per-core=2 -o ./report/allgather/out%J__allgather_4node -e ./report/allgather/err%J_allgather_4node allgather.sh

# circle
#sbatch -p bdw-mixed -N 1 -n 8 --ntasks-per-core=2 -o ./report/circle/out%J_cicle_1node -e ./report/circle/err%J_circle_1node circle.sh
#sbatch -p bdw-mixed -N 2 -n 8 --ntasks-per-core=2 -o ./report/circle/out%J_circle_2node -e ./report/circle/err%J_circle_2node circle.sh
#sbatch -p bdw-mixed -N 4 -n 8 --ntasks-per-core=2 -o ./report/circle/out%J_circle_4node -e ./report/circle/err%J_circle_4node circle.sh