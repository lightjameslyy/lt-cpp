#!/usr/bin/bash

for nthrds in 10 20 30 40; do
for scale in 20 22 24 26; do
    ./main.bin $nthrds $scale > t${nthrds}_s${scale}.log
done
done
