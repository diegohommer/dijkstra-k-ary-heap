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
    Graph();
    Graph(int n, int m);
    void read_dimacs(std::istream& in);
    std::vector<Edge> get_neighbours(int vertex);
    int get_total_vertices();
    int get_total_edges();
    void add_edge(int origin, int destiny, int weight);
    void add_symetric_edge(int vertex1, int vertex2, int weight);

private:
    std::vector<std::vector<Edge>> adjacency_list;
    unsigned num_vertices_;
    unsigned num_edges_;

    void resize(unsigned n);
};

#endif // GRAPH_H
