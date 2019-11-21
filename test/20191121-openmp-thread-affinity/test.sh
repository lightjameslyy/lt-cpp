#!/usr/bin/bash

for nthrds in 4 8 16
do
    export OMP_NUM_THREADS=${nthrds}
    export GOMP_CPU_AFFINITY=0-63
    echo "omp threads: ${nthrds}"
    #yhrun -n 1 -N 1 -c ${nthrds} ./main.bin
    ./main.bin
done
