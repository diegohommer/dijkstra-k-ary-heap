# Dijkstra Algorithm Benchmarking and Testing

## Overview
This project implements and benchmarks Dijkstra's algorithm using various test cases and optimizations. It supports different testing scenarios, including correctness tests, benchmarking for optimal parameters, and performance evaluation on varying graph structures.

## Directory Structure
```
include/   # Header files
src/       # Source files
  ├── dijkstra/  # Implementation of Dijkstra's algorithm and supporting data structures
  ├── generator/ # Graph generation utilities
obj/       # Compiled object files
data/
  ├── graphs/  # DIMACS Graphs for testing
  ├── outputs/ # Output .csv files from running tests
  ├── plots/   # Plot .pngs from running one of the plot.py functions
bin/       # Executable binaries and bash scripts for generating DIMACS test graphs
```

## Compilation
The project is built using `g++` with OpenMP support for parallel computing. Below are the key compiler settings:

- **Compiler:** `g++`
- **Flags:** `-std=c++17 -O2 -fopenmp -Iinclude`

### Source Files
- **Main Execution:** `src/main.cpp`, `src/memory_utils.cpp`, `src/dijkstra/dijkstra.cpp`, `src/dijkstra/graph.cpp`, `src/dijkstra/heap.cpp`
- **Graph Generator:** `src/generator/gen.cpp`

### Object and Executable Files
- **Main Object Files:** `obj/main.o`, `obj/memory_utils.o`, `obj/dijkstra/dijkstra.o`, `obj/dijkstra/graph.o`, `obj/dijkstra/heap.o`
- **Generator Object Files:** `obj/gen.o`
- **Executables:**
  - Main program: `bin/main.out`
  - Graph generator: `bin/gen.out`

## Build Instructions
To compile the project, run:
```sh
make
```

To clean all compiled files:
```sh
make clean
```

## Features
- **Correctness Testing**
  - Validates Dijkstra's algorithm on a predefined graph and ensures computed distances match expected results.
- **Performance Benchmarking**
  - Evaluates performance for different values of `k` and measures execution time.
- **Memory Usage Analysis**
  - Tracks memory usage during execution on scaled graphs.
- **Graph Scaling Tests**
  - Tests Dijkstra's algorithm on graphs with fixed vertices and edges to observe performance trends.
- **Regular Execution**
  - Runs Dijkstra's algorithm on a user-provided DIMACS graph. The program receives two parameters: the source vertex and the destination vertex. The graph is provided through standard input.

## Output Files
Results of benchmarking and tests are saved in the `./data/outputs/` directory:
- `dijkstra_sifts.csv` - SIFTs analysis results
- `dijkstra_ops.csv` - Operation count results
- `optimal_k_tests.csv` - Benchmarking results for different `k` values
- `dijkstra_<graph_name>.csv` - Test results for specific graphs

## Dependencies
- GCC with C++17 support
- OpenMP for parallel execution
- Make for build automation

## Authors
Diego Hommerding Amorim.
Developed as part of an academic project for benchmarking Dijkstra’s algorithm.

