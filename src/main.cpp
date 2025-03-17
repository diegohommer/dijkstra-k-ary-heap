#include <chrono>
#include <fstream>
#include "aux/dijkstra.cpp"

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        std::cerr << "Error: Invalid number of arguments!" << std::endl;
        return 1; 
    }

    // Read source and destiny vertices from argv
    int source = std::stoi(argv[1]) - 1; 
    int target = std::stoi(argv[2]) - 1; 

    // Read DIMACS graph from stdin
    Graph graph;
    graph.read_dimacs(std::cin);

    // Setup output file
    std::ofstream output ("../outputs/optimal_k_tests.csv", std::ios::trunc);
    output << "k   n   m   I   D   U   T(ms)" << std::endl;

    for(int i = 1; i <= 50; i++){
        int inserts = 0, deletemins = 0, updates = 0;
        std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
        for(int _ = 0; _ < 30; _++){
            DijkstraResult result = dijkstra(graph, source, target, i);
            inserts += result.inserts;
            deletemins += result.deletemins;
            updates += result.updates;
        }
        int T = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-t).count();
    
        output << i << " "
               << graph.get_total_vertices() << " "
               << graph.get_total_edges() << " "
               << inserts << " "
               << deletemins << " "
               << updates << " "
               << T << std::endl;
    }
    output.close();

    // if (shortest_path == std::numeric_limits<int>::max()) {
    //     std::cout << "inf" << std::endl;
    // } else {
    //     std::cout << shortest_path << std::endl;
    // }
    
    return 0;
}
