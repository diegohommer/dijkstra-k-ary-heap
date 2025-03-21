#!/bin/bash

folder="random"
num_graphs=15

for j in $(seq 1 $num_graphs); do
    # Random number of vertices between 1024 and 16384
    n=$((1024 + RANDOM % (16384 - 1024 + 1)))

    # Ensure a connected graph by using p >= ln(n) / n
    p_min=$(echo "scale=6; l($n) / $n" | bc -l)
    
    # Select p randomly between p_min and a denser value (e.g., 5 * p_min)
    p_max=$(echo "scale=6; 5 * $p_min" | bc -l)
    p=$(awk -v min=$p_min -v max=$p_max 'BEGIN { srand(); print min + (rand() * (max - min)) }')

    echo "Generating graph $j with n = $n and p = $p"
    ./gen.out $n $p $j $folder
done
