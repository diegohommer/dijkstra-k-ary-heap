#!/bin/bash

# Fixed number of vertices
n=5000
j=1

# Sparse graphs (m ~ 10n)
for i in $(seq 1 5); do
    p=$(echo "scale=6; $i * 0.00001" | bc)  # p = 0.00001, 0.00002, ..., 0.00005
    echo "Generating sparse graph with p = $p"
    ./gen $n $p $j
    j=$((j + 1))
done

# Mid-density graphs (m ~ 10n^1.5)
for i in $(seq 1 5); do
    p=$(echo "scale=6; $i * 0.001" | bc)  # p = 0.001, 0.002, ..., 0.005
    echo "Generating mid-density graph with p = $p"
    ./gen $n $p $j
    j=$((j + 1))
done

# Dense graphs (m ~ 0.1n^2)
for i in $(seq 1 5); do
    p=$(echo "scale=6; $i * 0.02" | bc)  # p = 0.02, 0.04, ..., 0.1
    echo "Generating dense graph with p = $p"
    ./gen $n $p $j
    j=$((j + 1))
done