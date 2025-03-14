#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <limits>
#include <iostream>
using namespace boost;

#include "heap.cpp"

typedef adjacency_list<vecS, vecS, directedS> Graph;

int dijkstra(Graph graph, int source_vertex, int destiny_vertex){
    int num_verts = num_vertices(graph);

    // Initialize distance map
    std::vector<bool> visited(num_verts, false);

    // Initialize priority queue
    KHeap priority_queue(num_verts);
    priority_queue.insert(source_vertex, 0);

    while(priority_queue.get_size() > 0){
        Node min_node = priority_queue.deletemin();
        int u = min_node.vertex;
        int dist_u = min_node.dist;
        visited[u] = true;

        

    }
    



    return 0;
}


// 1 ds := 0; dv := ∞, ∀v ∈ V \ {s}
// 2 visited(v) := false, ∀v ∈ V
// 3 Q := ∅
// 4 insert(Q, (s, 0))
// 5 while Q̸ = ∅ do
// 6 v := deletemin(Q)
// 7 visited(v) := true
// 8 for u ∈ N+(v) do
// 9 if not visited(u) then
// 10 if du = ∞ then
// 11 du := dv + dvu
// 12 insert(Q, (u, du))
// 13 else if dv + dvu < du
// 3Na hipótese razoável que m ≥ n.
// 9
