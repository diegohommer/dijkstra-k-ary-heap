#include "heap.h"
#include <iostream>

KHeap::KHeap(int total_vertices, int new_k, bool count_sifts) : pos(total_vertices, -1), k(new_k), count_sifts(count_sifts) {}

int KHeap::get_vertex_dist(int vertex){
    if (pos[vertex] == -1) { 
        return std::numeric_limits<int>::max(); 
    }
    return heap[pos[vertex]].dist;
}

HeapNode KHeap::deletemin(){
    HeapNode min = heap.front();
    swap_nodes(0, heap.size() - 1);
    pos[min.vertex] = -1;
    heap.pop_back();

    if (heap.size() > 1) {
        int sift_down_count = heapify_down(0);
        if (count_sifts) {
            double r = static_cast<double>(sift_down_count) / logk(heap.size());
            deletemin_r_values.push_back(r);
        }
    }

    return min;
}

void KHeap::update(int vertex, int dist){
    int vertex_index = pos[vertex];
    heap[vertex_index] = HeapNode{vertex, dist};
    int sift_up_count = heapify_up(vertex_index);

    if (count_sifts) {
        double r = static_cast<double>(sift_up_count) / logk(heap.size());
        update_r_values.push_back(r);
    }
}

void KHeap::insert(int vertex, int dist){
    heap.push_back(HeapNode{vertex, dist});
    pos[vertex] = heap.size() - 1;

    if (heap.size() > 1) {
        int sift_up_count = heapify_up(heap.size() - 1);
        if (count_sifts) {
            double r = static_cast<double>(sift_up_count) / logk(heap.size());
            insert_r_values.push_back(r);
        }
    }
}

int KHeap::get_size(){
    return heap.size();
}

void KHeap::swap_nodes(int index, int index2){
    int v1 = heap[index].vertex;
    int v2 = heap[index2].vertex;

    std::swap(heap[index], heap[index2]);   // Swap head distances
    std::swap(pos[v1], pos[v2]);            // Swap hash indexes
}

int KHeap::heapify_up(int index) {
    int sift_counter = 0;
    while(index > 0){
        int parent = (index - 1) / k;

        if(heap[index] < heap[parent]){
            swap_nodes(index,parent);
            if(count_sifts) sift_counter++;
            index = parent;
        }else{
            break;
        }
    }
    return sift_counter;
}

int KHeap::heapify_down(int index) {
    int sift_counter = 0;
    while (index < heap.size()){
        int min = index;

        for (int i = 1; i <= k; i++) {
            int child = (k * index) + i;
            if (child < heap.size() && heap[child] < heap[min]) {
                min = child;
            }
        }

        if(min != index){
            swap_nodes(index,min);
            if(count_sifts) sift_counter++;
            index = min;
        }else{
            break;
        }
    }
    return sift_counter;
}

double KHeap::logk(double n) {
    return ceil(std::log(n) / std::log(this->k));
}
