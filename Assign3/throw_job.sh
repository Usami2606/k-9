#!/bin/bash

mkdir -p report/p2p report/allgather

#sbatch -p bdw2-mixed -N 1 -n 2 --ntasks-per-core=2 -o ./report/p2p/out%J_p2p_samecpu -e ./report/p2p/err%J_p2p_samecpu p2p.sh
sbatch -p bdw2-mixed -N 1 -n 2 --ntasks-per-core=1 -o ./report/p2p/out%J_p2p_samenode -e ./report/p2p/err%J_p2p_samenode p2p.sh
#sbatch -p bdw2-mixed -N 2 -n 2 --ntasks-per-core=1 -o ./report/p2p/out%J_p2p_othernode -e ./report/p2p/err%J_p2p_othernode p2p.sh
#sbatch -p bdw2-mixed -N 1 -n 8 --ntasks-per-core=2 -o ./report_allgather/out%J_allgather_samecpu -e ./report/err%J_allgather_samecpu allgather.sh
#sbatch -p bdw2_mixed -N 2 -n 4 --ntasks-per-core=2 -o ./report_allgather/out%J_allgather_othernode -e /report/err%J_allgather_othernode allgather.sh
