#!/bin/bash

# Initial number of threads
threads=1

# Maximum number of threads (256)
max_threads=256

mkdir -p grav_data/result1000
mkdir -p grav_data/result1000
mkdir -p grav_data/result1000
mpirun -rf rankfile -report-bindings bin/runprog