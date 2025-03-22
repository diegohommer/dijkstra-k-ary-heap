#!/bin/bash

# Fixed number of vertices
n=32768
folder="fixed_vertices"
j=1

# Start with sqrt(2)^20 and increase by a consistent factor for each step
initial_m=$(echo "scale=0; 2^(20)" | bc -l)  # Starting m = sqrt(2)^20
factor=$(echo "scale=6; sqrt(2)" | bc)  # Factor to increase m in each step (sqrt(2))

# Generate graphs with unique steps between m values
m=$initial_m
for (( k=20; k<=29; k++ )); do
    m=$(echo "scale=0; $m * $factor" | bc)
    p=$(echo "scale=6; $m / ($n * $n)" | bc)
    floored_m=$(printf "%.0f" "$m")
    echo "Generating graph with n = $n, p = $p (m = $floored_m)"
    ./gen.out $n $p $j $folder
    ((j++))
done
