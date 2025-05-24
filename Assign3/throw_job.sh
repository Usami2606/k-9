#!/bin/bash

mkdir -p report

#sbatch -p bdw2-mixed -N 1 -n 2 --ntasks-per-core=2 -o ./report/out%J_p2p_samecpu -e ./report/err%J_p2p_samecpu p2p.sh
#sbatch -p bdw2-mixed -N 1 -n 2 --ntasks-per-core=1 -o ./report/out%J_p2p_samenode -e ./report/err%J_p2p_samenode p2p.sh
#sbatch -p bdw2-mixed -N 2 -n 2 --ntasks-per-core=1 -o ./report/out%J_p2p_othernode -e ./report/err%J_p2p_othernode p2p.sh
sbatch -p bdw2-mixed -N 1 -n 8 --ntasks-per-core=2 -o ./report/out%J_allgather_samecpu -e ./report/err%J_allgather_samecpu allgather.sh
