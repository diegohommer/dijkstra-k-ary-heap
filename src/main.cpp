#include <chrono>
#include <fstream>
#include <filesystem>
#include <cassert>

#include <omp.h>
#include "dijkstra.h"
#include "memory_utils.h"

const int OPTIMAL_K = 8;

/**
 * @brief Tests the correctness of the Dijkstra algorithm implementation.
 *
 * Runs Dijkstra's algorithm on a predefined graph and compares the computed shortest distances
 * from vertex 0 to all other vertices with the expected results. If any computed distance does
 * not match the expected value, the program will terminate with an assertion error.
 * Example graph available at <https://www.researchgate.net/figure/Example-Graph-for-dynamic-Dijkstra-algorithm_fig5_323578961>
 */
void run_correctness_test() {
    Graph graph(8,28);

    graph.add_symetric_edge(0, 1, 2);
    graph.add_symetric_edge(0, 3, 7);
    graph.add_symetric_edge(0, 5, 12);
    graph.add_symetric_edge(0, 6, 2);
    graph.add_symetric_edge(1, 2, 1);
    graph.add_symetric_edge(1, 3, 4);
    graph.add_symetric_edge(1, 4, 3);
    graph.add_symetric_edge(1, 6, 5);
    graph.add_symetric_edge(2, 4, 4);
    graph.add_symetric_edge(2, 6, 4);
    graph.add_symetric_edge(3, 4, 4);
    graph.add_symetric_edge(3, 7, 5);
    graph.add_symetric_edge(4, 7, 7);
    graph.add_symetric_edge(5, 7, 3);

    int true_min_distances[8] = {0, 2, 3, 6, 5, 12, 2, 11};
    for(int i = 0; i < 8; i++){
        int result_min_distance = dijkstra(graph, 0, i, OPTIMAL_K, false).shortest_distance;
        assert(result_min_distance == true_min_distances[i]);
    }
};

void run_sifts_test(int source, int target){
    const std::string varied_folder = "./data/graphs/varied/test_";
    const int num_tests = 18;

    // Read all graphs into memory
    std::vector<Graph> graphs;
    for (int j = 1; j <= num_tests; j++) {
        std::ifstream input(varied_folder + std::to_string(j) + ".csv");
        Graph graph;
        graph.read_dimacs(input);
        graphs.push_back(graph);
    }

    // Setup output file
    std::ofstream output("./data/outputs/djikstra_sifts.csv", std::ios::trunc);
    output << "n,m,Insert_r_average,Deletemin_r_average,Update_r_average,All_r_valid" << std::endl;

    for (int j = 0; j < num_tests; j++) {
        // Run Dijkstra with count_sifts enabled
        DijkstraResult result = dijkstra(graphs[j], source, target, OPTIMAL_K, true);

        // Vectors to store r values for all graphs
        bool all_r_valid = true;

        // Check if all r values are <= 1 and compute average
        double insert_r_average = 0.0;
        if (!result.insert_r_values.empty()) {
            for (double r : result.insert_r_values) {
                if (r > 1.0 || r < 0.0) all_r_valid = false;
                insert_r_average += r;
            }
            insert_r_average /= result.insert_r_values.size();
        }
    
        double deletemin_r_average = 0.0;
        if (!result.deletemin_r_values.empty()) {
            for (double r : result.deletemin_r_values) {
                if (r > 1.0 || r < 0.0) all_r_valid = false;
                deletemin_r_average += r;
            }
            deletemin_r_average /= result.deletemin_r_values.size();
        }
    
        double update_r_average = 0.0;
        if (!result.update_r_values.empty()) {
            for (double r : result.update_r_values) {
                if (r > 1.0 || r < 0.0) all_r_valid = false;
                update_r_average += r;
            }
            update_r_average /= result.update_r_values.size();
        }
    
        // Write results to the output file
        output << graphs[j].get_total_vertices() << "," 
               << graphs[j].get_total_edges() << ","
               << insert_r_average << "," 
               << deletemin_r_average << "," 
               << update_r_average << "," 
               << (all_r_valid ? "Yes" : "No") << std::endl;
    }
}

/**
 * @brief Benchmarks Dijkstra's algorithm for different values of `k`.
 *
 * Reads graphs from `./data/graphs/varied/test_*.csv`, runs Dijkstra for `k` values from 2 to 128,
 * and records the average execution time over 30 repetitions. Results are saved to `./data/outputs/optimal_k_tests.csv`.
 *
 * @param source Source vertex for Dijkstra.
 * @param target Target vertex for Dijkstra.
 *
 * @note
 * - Sets OpenMP threads to 1 for consistent timing.
 * - Overwrites `./data/outputs/optimal_k_tests.csv` if it exists.
 */
void run_optimal_k_tests(int source, int target);void run_optimal_k_tests(int source, int target){
    const std::string varied_folder = "./data/graphs/varied/test_";
    const int num_tests = 18; 

    // Read all graphs into memory
    std::vector<Graph> graphs;
    for (int j = 1; j <= num_tests; j++) {
        std::ifstream input(varied_folder + std::to_string(j) + ".csv");
        Graph graph;
        graph.read_dimacs(input);
        graphs.push_back(graph);
    }

    // MonoThread program for more time consistency
    omp_set_num_threads(1);

    // Setup output file
    std::ofstream output("./data/outputs/optimal_k_tests.csv", std::ios::trunc);
    output << "k, Avg_T(ms)" << std::endl;

    // Run Dijkstra tests/benchmarks
    for (int k = 2; k <= 128; k += 1) {
        long long total_duration = 0;
        int repetitions = 30;

        for (int repeats = 0; repeats < repetitions; repeats++) {
            auto start = std::chrono::high_resolution_clock::now();

            for (int j = 0; j < num_tests; j++) {
                dijkstra(graphs[j], source, target, k, false); // Run Dijkstra, ignore operation counts
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
};

/**
 * @brief Benchmarks Dijkstra's algorithm, recording Inserts, Delemins, Updates, average execution time and average memory usage.
 *
 * Reads graph from `./data/graphs/scaled/<graph_name>*.gr`, runs Dijkstra on it over 30 repetitions, 
 * and records the number of Inserts (I), Delemins (D), Updates (U), average execution time (T) in milliseconds and average memory usage (Mem) in bytes. 
 * Results are saved to `./data/outputs/dijkstra_<graph_name>.csv`.
 *
 * @param source Source vertex for Dijkstra.
 * @param target Target vertex for Dijkstra.
 * @param graph_name Name of the file containing the DIMACS graph.
 *
 * @note
 * - Uses a single OpenMP thread for consistent timing.
 * - Overwrites the output file if it exists.
 */
void run_scaled_test(int source, int target, const std::string& graph_name){
    const int repetitions = 30;

    // MonoThread program for more time consistency
    omp_set_num_threads(1);

    // Setup output file
    std::ofstream output("./data/outputs/dijkstra_" + graph_name + ".csv", std::ios::trunc);
    output << "n, m, I, D, U, T(ms), Mem(Bytes)" << std::endl;

    std::ifstream input("./data/graphs/scaled/" + graph_name + ".gr");

    Graph graph;
    graph.read_dimacs(input);

    long long total_duration = 0;
    long long total_memory = 0;
    int inserts = 0, deletemins = 0, updates = 0;

    for (int repetition = 0; repetition < repetitions; repetition++){
        size_t mem_before = memory_used(true);  

        auto start = std::chrono::high_resolution_clock::now();
        DijkstraResult result = dijkstra(graph, source, target, OPTIMAL_K, false);
        auto end = std::chrono::high_resolution_clock::now();

        size_t mem_after = memory_used(true);  
        size_t mem_usage = (mem_after > mem_before) ? (mem_after - mem_before) : 0;

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        total_duration += duration;
        total_memory += mem_usage;
        inserts += result.inserts;
        deletemins += result.deletemins;
        updates += result.updates;
    }

    std::cout << "Graph " << graph_name << " Tested!" << std::endl;
    output << graph.get_total_vertices() << ","
           << graph.get_total_edges() << ","
           << inserts / repetitions << ","
           << deletemins / repetitions << ","
           << updates / repetitions << ","
           << total_duration / repetitions << ","
           << total_memory / repetitions << std::endl;
};

/**
 * @brief Benchmarks Dijkstra's algorithm, recording Inserts, Delemins, Updates, and average execution time.
 *
 * Reads graphs from `./data/graphs/<folder_name>/test_*.csv`, runs Dijkstra on each graph over 30 repetitions, 
 * and records the number of Inserts (I), Delemins (D), Updates (U), and average execution time (T) in milliseconds. 
 * Results are saved to `./data/outputs/dijkstra_<folder_name>.csv`.
 *
 * @param source Source vertex for Dijkstra.
 * @param target Target vertex for Dijkstra.
 * @param folder_name Name of the folder containing the graph files.
 *
 * @note
 * - Uses a single OpenMP thread for consistent timing.
 * - Overwrites the output file if it exists.
 */
void run_dijkstra_fixed_tests(int source, int target, std::string folder_name){
    const int num_tests = 10; 
    const int repetitions = 30;

    // MonoThread program for more time consistency
    omp_set_num_threads(1);

    // Setup output file
    std::ofstream output("./data/outputs/dijkstra_" + folder_name + ".csv", std::ios::trunc);
    output << "n, m, I, D, U, T(ms)" << std::endl;

    for (int j = 1; j <= num_tests; j++) {
        long long total_duration = 0;
        int inserts = 0, deletemins = 0, updates = 0;

        std::ifstream input("./data/graphs/" + folder_name + "/test_" + std::to_string(j) + ".csv");
        Graph graph;
        graph.read_dimacs(input);

        for (int repetition = 0; repetition < repetitions; repetition++){
            auto start = std::chrono::high_resolution_clock::now();
            DijkstraResult result = dijkstra(graph, source, target, OPTIMAL_K, false);
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            total_duration += duration; 
            inserts += result.inserts;
            deletemins += result.deletemins;
            updates += result.updates;
        }

        std::cout << "Graph " << std::to_string(j) << " Tested!" << std::endl;
        output << graph.get_total_vertices() << ","
               << graph.get_total_edges() << ","
               << inserts / repetitions << ","
               << deletemins /repetitions << ","
               << updates / repetitions << ","
               << total_duration / repetitions << std::endl;
    }
};

/**
 * @brief Runs Dijkstra's algorithm benchmarking on fixed vertex graphs.
 *
 * Calls `run_dijkstra_fixed_tests` with the `"fixed_vertices"` folder name for the graph files.
 *
 * @param source Source vertex for Dijkstra.
 * @param target Target vertex for Dijkstra.
 */
void run_dijkstra_fixed_v_tests(int source, int target){
    run_dijkstra_fixed_tests(source, target, "fixed_vertices");
};

/**
 * @brief Runs Dijkstra's algorithm benchmarking on fixed edge graphs.
 *
 * Calls `run_dijkstra_fixed_tests` with the `"fixed_edges"` folder name for the graph files.
 *
 * @param source Source vertex for Dijkstra.
 * @param target Target vertex for Dijkstra.
 */
void run_dijkstra_fixed_e_tests(int source, int target){
    run_dijkstra_fixed_tests(source, target, "fixed_edges");
}

/**
 * @brief Runs Dijkstra's algorithm on a graph read from stdin and computes the shortest path.
 *
 * Reads a graph in DIMACS format from standard input, then computes and prints the shortest path 
 * between the specified source and target vertices. If the vertices are out of bounds or the path 
 * is not found, appropriate error messages are displayed.
 *
 * @param source Source vertex for Dijkstra.
 * @param target Target vertex for Dijkstra.
 * 
 * @return 0 on success, -1 if there are invalid vertex indices.
 */
int run_dijkstra(int source, int target){
    // Read graph from stdin
    Graph graph;
    graph.read_dimacs(std::cin);

    if(source >= graph.get_total_vertices() || target >= graph.get_total_vertices()){
        std::cout << "Out of bounds vertex! Range is 0 to" + std::to_string(graph.get_total_vertices()-1) << std::endl;
        return -1;
    }

    int shortest_path = dijkstra(graph,source,target,OPTIMAL_K, false).shortest_distance;
    
    if (shortest_path == std::numeric_limits<int>::max()) {
        std::cout << "inf" << std::endl;
    } else {
        std::cout << shortest_path << std::endl;
    }

    return 0;
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

    run_sifts_test(source, target);
    return 0;

    //return run_dijkstra(source, target);
}
