#include <chrono>
#include <fstream>
#include <filesystem>
#include "dijkstra.h"
#include <omp.h>

void run_optimal_k_tests(int source, int target){
    const std::string k_tests_folder = "./tests/fixed_vertices/test_";
    const int num_tests = 15; 

    // Read all graphs into memory
    std::vector<Graph> graphs;
    for (int j = 1; j <= num_tests; j++) {
        std::ifstream input(k_tests_folder + std::to_string(j) + ".csv");
        Graph graph;
        graph.read_dimacs(input);
        graphs.push_back(graph);
    }

    // MonoThread program for more time consistency
    omp_set_num_threads(1);

    // Setup output file
    std::ofstream output("./outputs/optimal_k_tests.csv", std::ios::trunc);
    output << "k, Avg_T(ms)" << std::endl;

    // Run Dijkstra tests/benchmarks
    for (int k = 2; k <= 128; k += 1) {
        long long total_duration = 0;
        int repetitions = 30;

        for (int repeats = 0; repeats < repetitions; repeats++) {
            auto start = std::chrono::high_resolution_clock::now();

            for (int j = 0; j < num_tests; j++) {
                dijkstra(graphs[j], source, target, k); // Run Dijkstra, ignore operation counts
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            total_duration += duration;
        }

        double avg_duration = static_cast<double>(total_duration) / repetitions;

        // Write results to the output file
        output << k << "," << avg_duration << "\n";
        std::cout << "k=" << k << " tested, Avg Time: " << avg_duration << "ms" << std::endl << std::flush;
    }
}

int main(int argc, char const *argv[])
{    
    if (argc != 3) {
        std::cerr << "Error: Invalid number of arguments!" << std::endl;
        return 1; 
    }

    // Read source and destiny vertices from argv
    int source = std::stoi(argv[1]) - 1; 
    int target = std::stoi(argv[2]) - 1; 

    run_optimal_k_tests(source, target);
    
    // if (shortest_path == std::numeric_limits<int>::max()) {
    //     std::cout << "inf" << std::endl;
    // } else {
    //     std::cout << shortest_path << std::endl;
    // }
    
    return 0;
}
