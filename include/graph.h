#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <sstream>
#include <unordered_map> 
#include <vector>

struct Edge {
    int vertex;
    int dist;
};

class Graph {
public:
    void read_dimacs(std::istream& in);
    std::vector<Edge> get_neighbours(int vertex);
    int get_total_vertices();
    int get_total_edges();

private:
    std::vector<std::vector<Edge>> adjacency_list;
    unsigned num_vertices_;
    unsigned num_edges_;

    void add_edge(int origin, int destiny, int weight);
    void resize(unsigned n);
};

#endif // GRAPH_H
