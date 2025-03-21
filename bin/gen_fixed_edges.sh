#!/bin/bash

# Fixed number of edges
m=1048576
j=1
folder="fixed_edges"

# Generate graphs with n = 2^10 ... 2^19
for (( n=1024; n<=2**19; n*=2 )); do
    p=$(echo "scale=6; $m / ($n * $n)" | bc)  # p = m / n^2
    echo "Generating graph with n = $n, p = $p (m = $m)"
    ./gen.out $n $p $j $folder
    ((j++))  
done