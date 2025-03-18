#include <vector>
#include <limits>
#include <iostream>

#include "graph.cpp"
#include "heap.cpp"

struct DijkstraResult {
    int shortest_distance;
    int inserts;
    int deletemins;
    int updates;
};

DijkstraResult dijkstra(Graph graph, int source_vertex, int destiny_vertex, int k){
    int num_verts = graph.get_total_vertices();
    int inserts = 0, deletemins = 0, updates = 0;

    // Initialize distance map
    std::vector<bool> visited(num_verts, false);
    std::vector<int> distances(num_verts, std::numeric_limits<int>::max());
    distances[0] = 0;

    // Initialize priority queue
    KHeap priority_queue(num_verts,k);
    priority_queue.insert(source_vertex, 0);
    inserts++;

    while (priority_queue.get_size() > 0) {
        // Extract the node with the minimum distance
        HeapNode current = priority_queue.deletemin();
        int v = current.vertex;
        int v_min = current.dist;
        deletemins++;

        visited[v] = true;
    
        // Process each neighbor of the current vertex
        for (const Edge& edge : graph.get_neighbours(v)) {
            int u = edge.vertex;
            int weight = edge.dist;
    
            if (!visited[u]) {
                int u_min = priority_queue.get_vertex_dist(u);
    
                if (u_min == std::numeric_limits<int>::max()) {  
                    priority_queue.insert(u, v_min + weight);
                    inserts++;
                } else if (v_min + weight < u_min) {  
                    priority_queue.update(u, v_min + weight);
                    updates++;
                }
            }
        }
    }

    return DijkstraResult{distances[destiny_vertex],inserts,deletemins,updates};
}
