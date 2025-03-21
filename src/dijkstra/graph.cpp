#include "graph.h"

Graph::Graph() {};
Graph::Graph(int n, int m) : num_vertices_(n), num_edges_(m) {resize(n);};

void Graph::read_dimacs(std::istream& in) {
    std::string line="", dummy;
    while (line.substr(0,4) != "p sp")
      getline(in,line);
   
    // (1) get nodes and edges
    std::stringstream linestr;
    linestr.str(line);
    unsigned n, m;
    linestr >> dummy >> dummy >> n >> m;
    resize(n);
    unsigned i=0;
    while (getline(in,line) && i < m) {
        if (line.substr(0,2) == "a ") {
            std::stringstream arc(line);
            unsigned u,v,w;
            char ac;
            arc >> ac >> u >> v >> w;
            // processa arco (u,v) com peso w
            add_edge(u-1, v-1, w);
            ++i;
        }
    }
  }

std::vector<Edge> Graph::get_neighbours(int vertex) {
    return adjacency_list[vertex];
}

int Graph::get_total_vertices() {
    return this->num_vertices_;
}

int Graph::get_total_edges() {
    return this->num_edges_;
}

void Graph::add_edge(int origin, int destiny, int weight) {
    adjacency_list[origin].push_back(Edge{destiny, weight});
}

void Graph::add_symetric_edge(int u, int v, int weight) {
    adjacency_list[u].push_back(Edge{v, weight});
    adjacency_list[v].push_back(Edge{u, weight});
}

void Graph::resize(unsigned n) {
    adjacency_list.resize(n);
}
