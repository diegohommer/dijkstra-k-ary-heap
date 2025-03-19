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
};

DijkstraResult dijkstra(Graph graph, int source_vertex, int destiny_vertex, int k);

#endif // DIJKSTRA_H
