// aux/dijkstra.h
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "heap.h"

struct DijkstraResult {
    int shortest_distance;
    int inserts;
    int deletemins;
    int updates;
    std::vector<double> insert_r_values;
    std::vector<double> deletemin_r_values;
    std::vector<double> update_r_values;
};

DijkstraResult dijkstra(Graph graph, int source_vertex, int destiny_vertex, int k, bool count_sifts);

#endif // DIJKSTRA_H
