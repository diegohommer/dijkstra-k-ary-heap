#include "heap.h"

KHeap::KHeap(int total_vertices, int new_k) : pos(total_vertices, -1), k(new_k) {}

int KHeap::get_vertex_dist(int vertex){
    if (pos[vertex] == -1) { 
        return std::numeric_limits<int>::max(); 
    }
    return heap[pos[vertex]].dist;
}

HeapNode KHeap::deletemin(){
    HeapNode min = heap.front();
    swap_nodes(0, heap.size()-1);
    pos[min.vertex] = -1;
    heap.pop_back();
    heapify_down(0);
    return min;
}

void KHeap::update(int vertex, int dist){
    int vertex_index = pos[vertex];
    heap[vertex_index] = HeapNode{vertex,dist};
    heapify_up(vertex_index);
}

void KHeap::insert(int vertex, int dist){
    heap.push_back(HeapNode{vertex,dist});
    pos[vertex] = heap.size()-1;
    heapify_up(heap.size()-1);
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

void KHeap::heapify_up(int index) {
    while(index > 0){
        int parent = (index - 1) / k;

        if(heap[index] < heap[parent]){
            swap_nodes(index,parent);
            index = parent;
        }else{
            break;
        }
    }
}

void KHeap::heapify_down(int index) {
    while(true){
        int min = index;

        for (int i = 1; i <= k; i++) {
            int child = (k * index) + i;
            if (child < heap.size() && heap[child] < heap[min]) {
                min = child;
            }
        }

        if(min != index){
            swap_nodes(index,min);
            index = min;
        }else{
            break;
        }
    }
}
