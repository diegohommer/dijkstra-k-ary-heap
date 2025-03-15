#include <array>
#include <vector>
#include <limits>
#include <unordered_map>

struct Node {
    int vertex, dist;
    bool operator<(const Node& other) const {
        return dist < other.dist;  
    }
};

class KHeap {
    public:
        static const int k = 3;

        KHeap(int total_vertices) : pos(total_vertices, -1){}

        int get_vertex_dist(int vertex){
            if (pos[vertex] == -1) { 
                return std::numeric_limits<int>::max(); 
            }
            return heap[pos[vertex]].dist;
        }

        Node deletemin(){
            Node min = heap.front();
            pos[min.vertex] = -1;
            swap_nodes(0, heap.size()-1);
            heap.pop_back();
            sift_down(0);
            return min;
        }

        void update(int vertex, int dist){
            int vertex_index = pos[vertex];
            heap[vertex_index] = Node{vertex,dist};
            sift_up(vertex_index);
            sift_down(vertex_index);
        }

        void insert(int vertex, int dist){
            heap.push_back(Node{vertex,dist});
            pos[vertex] = heap.size()-1;
            sift_up(heap.size()-1);
        }

        int get_size(){
            return heap.size();
        }

    private:
        std::vector<Node> heap;
        std::vector<int> pos;

        void swap_nodes(int index, int index2){
            int v1 = heap[index].vertex;
            int v2 = heap[index2].vertex;

            std::swap(heap[index], heap[index2]);   // Swap head distances
            std::swap(pos[v1], pos[v2]);            // Swap hash indexes
        }
        
        void sift_up(int index) {
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

        void sift_down(int index) {
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
};