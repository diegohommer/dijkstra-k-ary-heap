#include "graph.h"

void Graph::read_dimacs(std::istream& in) {
    std::string line = "", dummy;
    while (line.substr(0, 4) != "p sp")
        getline(in, line);

    std::stringstream linestr;
    linestr.str(line);
    linestr >> dummy >> dummy >> num_vertices_ >> num_edges_;
    this->resize(get_total_vertices());

    unsigned i = 0;
    while (i++ < get_total_edges()) {
        getline(in, line);
        if (line.substr(0, 2) == "a ") {
            std::stringstream arc(line);
            unsigned u, v, w;
            char ac;
            arc >> ac >> u >> v >> w;
            this->add_edge(u - 1, v - 1, w); // process edge (u,v) with weight w
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

void Graph::resize(unsigned n) {
    adjacency_list.resize(n);
}
