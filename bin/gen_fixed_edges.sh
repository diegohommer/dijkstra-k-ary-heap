#!/bin/bash

# Fixed number of edges
m=1048576
j=1

# Number of vertices (n) to test
vertices=($(seq 1024 1024 20480)) 

# Generate graphs with fixed m and varying n
for n in "${vertices[@]}"; do
    p=$(echo "scale=6; $m / ($n * $n)" | bc)  # p = m / n^2
    echo "Generating graph with n = $n, p = $p (m = $m)"
    ./gen.out $n $p $j
    j=$((j + 1))
done