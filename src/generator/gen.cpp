/**
 * \file gen.cpp
 *   \author Marcus Ritt <mrpritt@inf.ufrgs.br>
 *   \date Time-stamp: <2024-07-23 13:03:31 ritt>
 */

#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace boost;

// information stored in vertices
struct VertexInformation {
  unsigned component;
};

// information stored in edges
struct EdgeInformation {
  unsigned weight;
};

const unsigned maxweight = 1000;

// graph is an adjacency list represented by vectors
typedef adjacency_list<vecS, vecS, directedS, VertexInformation, EdgeInformation> Graph;
typedef graph_traits<Graph>::vertex_descriptor Node;
typedef graph_traits<Graph>::edge_descriptor Edge;

int main(int argc, char *argv[]) {
  assert(argc == 5);
  unsigned n = atoi(argv[1]);
  double p = atof(argv[2]);
  std::string i = argv[3];
  std::string folder = argv[4];

  srand48(time(0));

  // (1) generate random graph
  Graph g;

  for (unsigned i = 0; i < n; i++)
    add_vertex(g);

  for (unsigned i = 0; i < n; i++)
    for (unsigned j = 0; j < n; j++)
      if (i != j && drand48() < p) {
        Edge e = add_edge(i, j, g).first;
        g[e].weight = lrand48() % maxweight;
      }

  // (2) print example path
  unsigned src = lrand48() % num_vertices(g);
  unsigned dst = lrand48() % num_vertices(g);

  vector<unsigned> dist(n);
  vector<unsigned> pred(n);
  dijkstra_shortest_paths(g, src, weight_map(get(&EdgeInformation::weight, g)).distance_map(&dist[0]).predecessor_map(&pred[0]));
  cerr << "Distance between " << src + 1 << " and " << dst + 1 << " is " << dist[dst] << endl;

  // (3) Generate dynamic filename
  std::string filename = "../data/graphs/" + folder + "/test_" + i + ".csv";
  
  // Open file for writing
  std::ofstream output(filename);
  if (!output) {
      std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
      return 1;
  }

  // Write to the file
  output << "p sp " << num_vertices(g) << " " << num_edges(g) << std::endl;
  for (auto [eb, ee] = edges(g); eb != ee; eb++)
      output << "a " << source(*eb, g) + 1 << " " << target(*eb, g) + 1 << " " << g[*eb].weight << std::endl;

  output.close();
  std::cout << "Output written to " << filename << std::endl;
}
