#!/bin/bash

folder="varied"

# Predefined (n, m) pairs ensuring variety and mix of sparse, moderate, and dense graphs
declare -a vertices=(32 64 128 256 512 1024 2048 4096 8192 16384 32768 4096 16384 2048 8192 128 512 1024 8192 32768)
declare -a densities=(0.2 0.15 0.1 0.1 0.1 0.05 0.05 0.005 0.05 0.001 0.0001 0.01 0.05 0.05 0.05 0.15 0.1 0.05 0.1 0.00001)

num_graphs=${#vertices[@]}

for j in $(seq 1 $num_graphs); do
    n=${vertices[$((j - 1))]}
    density=${densities[$((j - 1))]}

    # Compute number of edges m from density
    m=$(echo "scale=0; $density * $n * ($n - 1)" | bc -l | awk '{print int($1)}')

    # Compute probability p such that expected edges is close to m
    p=$(echo "scale=6; $m / ($n * ($n - 1))" | bc -l)

    echo "Generating graph $j with n = $n, m = $m (density = $density, p = $p)"
    ./gen.out $n $p $j $folder
done

echo "Graph generation compl
