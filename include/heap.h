#ifndef KHEAP_H
#define KHEAP_H

#include <vector>
#include <limits>
#include <math.h>

struct HeapNode {
    int vertex;
    int dist;
    bool operator<(const HeapNode& other) const {
        return dist < other.dist;  
    }
};

class KHeap {
public:
    KHeap(int total_vertices, int new_k, bool count_sifts);

    int get_vertex_dist(int vertex);
    HeapNode deletemin();
    void update(int vertex, int dist);
    void insert(int vertex, int dist);
    int get_size();
        
    const std::vector<double>& get_insert_r_values() const { return insert_r_values; }
    const std::vector<double>& get_deletemin_r_values() const { return deletemin_r_values; }
    const std::vector<double>& get_update_r_values() const { return update_r_values; }
private:
    int k;
    std::vector<double> insert_r_values;
    std::vector<double> deletemin_r_values;
    std::vector<double> update_r_values;
    bool count_sifts;
    std::vector<HeapNode> heap;
    std::vector<int> pos;

    void swap_nodes(int index, int index2);
    int heapify_up(int index);
    int heapify_down(int index);
    double logk(double n);
};

#endif // KHEAP_H
