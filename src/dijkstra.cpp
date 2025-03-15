#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <limits>
#include <iostream>
using namespace boost;

#include "graph.cpp"
#include "heap.cpp"

int dijkstra(Graph graph, int source_vertex, int destiny_vertex){
    int num_verts = graph.get_total_vertices();

    // Initialize distance map
    std::vector<bool> visited(num_verts, false);

    // Initialize priority queue
    KHeap priority_queue(num_verts);
    priority_queue.insert(source_vertex, 0);

    while (priority_queue.get_size() > 0) {
        // Extract the node with the minimum distance
        Node current = priority_queue.deletemin();
        int v = current.vertex;
        int v_min = current.dist;
        visited[v] = true;
    
        // Process each neighbor of the current vertex
        for (const Node& neighbor : graph.get_neighbours(v)) {
            int u = neighbor.vertex;
            int weight = neighbor.dist;
    
            if (!visited[u]) {
                int u_min = priority_queue.get_vertex_dist(u);
    
                if (u_min == std::numeric_limits<int>::max()) {  
                    priority_queue.insert(u, v_min + weight);
                } else if (v_min + weight < u_min) {  
                    priority_queue.update(u, v_min + weight);
                }
            }
        }
    }

    return 0;
}
