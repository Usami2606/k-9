#!/bin/bash

mkdir -p report/p2p report/allgather

#sbatch -p bdw1-mixed -N 1 -n 2 --ntasks-per-core=2 -o ./report/p2p/out%J_p2p_samecpu -e ./report/p2p/err%J_p2p_samecpu p2p.sh
#sbatch -p bdw1-mixed -N 1 -n 2 --ntasks-per-core=1 -o ./report/p2p/out%J_p2p_samenode -e ./report/p2p/err%J_p2p_samenode p2p.sh
#sbatch -p bdw1-mixed -N 2 -n 2 --ntasks-per-core=1 -o ./report/p2p/out%J_p2p_othernode -e ./report/p2p/err%J_p2p_othernode p2p.sh
#sbatch -p bdw-mixed -N 1 -n 8 --ntasks-per-core=2 -o ./report/allgather/out%J_allgather_samecpu -e ./report/allgather/err%J_allgather_samecpu allgather.sh
#sbatch -p bdw-mixed -N 2 -n 8 --ntasks-per-core=2 -o ./report/allgather/out%J_allgather_othernode -e ./report/allgather/err%J_allgather_othernode allgather.sh
sbatch -p bdw-mixed -N 3 -n 8 --ntasks-per-core=2 -o ./report/allgather/out%J_allgather_othernode -e ./report/allgather/err%J_allgather_othernode allgather.sh

#sbatch -p bdw1-mixed -N 1 -n 2 --ntasks-per-core=2 -o ./report/p2p/out%J_p2p_samecpu -e ./report/p2p/err%J_p2p_samecpu p2p.sh
#sbatch -p bdw1-mixed -N 1 -n 2 --ntasks-per-core=1 -o ./report/p2p/out%J_p2p_samecpu -e ./report/p2p/err%J_p2p_samecpu p2p.sh
#sbatch -p bdw1-mixed -N 2 -n 2 --ntasks-per-core=1 -o ./report/p2p/out%J_p2p_othernode -e ./report/p2p/err%J_p2p_othernode p2p.sh