#include <chrono>
#include <fstream>
#include <filesystem>
#include "aux/dijkstra.cpp"

void run_optimal_k_tests(int source, int target){
    const std::string k_tests_folder = "../tests/k_tests/test_";
    const int num_tests = 15; 

    // Read all graphs into memory
    std::vector<Graph> graphs;
    for (int j = 1; j <= num_tests; j++) {
        std::ifstream input(k_tests_folder + std::to_string(j) + ".csv");
        Graph graph;
        graph.read_dimacs(input);
        graphs.push_back(graph);
    }

    // Setup output file
    std::ofstream output ("../outputs/optimal_k_tests.csv", std::ios::trunc);
    output << " k   I   D   U   T(ms) " << std::endl;

    // Run Dijkstra tests/benchmarks
    for (int k = 2; k <= 128; k += 1) {
        int inserts = 0, deletemins = 0, updates = 0;
        auto start = std::chrono::high_resolution_clock::now(); // Start timer

        #pragma omp parallel for reduction(+:inserts, deletemins, updates)
        for (int j = 0; j < num_tests; j++) {
            DijkstraResult result = dijkstra(graphs[j], source, target, k);
            inserts += result.inserts;
            deletemins += result.deletemins;
            updates += result.updates;
        }


        auto end = std::chrono::high_resolution_clock::now(); 
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Write results to the output file
        output << k << ","
               << inserts << ","
               << deletemins << ","
               << updates << ","
               << duration << "\n";
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
