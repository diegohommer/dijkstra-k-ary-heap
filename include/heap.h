#ifndef KHEAP_H
#define KHEAP_H

#include <vector>
#include <limits>

struct HeapNode {
    int vertex;
    int dist;
    bool operator<(const HeapNode& other) const {
        return dist < other.dist;  
    }
};

class KHeap {
public:
    KHeap(int total_vertices, int new_k);

    int get_vertex_dist(int vertex);
    HeapNode deletemin();
    void update(int vertex, int dist);
    void insert(int vertex, int dist);
    int get_size();
private:
    int k;
    std::vector<HeapNode> heap;
    std::vector<int> pos;

    void swap_nodes(int index, int index2);
    void heapify_up(int index);
    void heapify_down(int index);
};

#endif // KHEAP_H
