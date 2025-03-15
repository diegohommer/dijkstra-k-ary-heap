#include <iostream>
#include <sstream>
#include <unordered_map> 
#include <vector>

struct Node {
    int vertex, dist;
};

class Graph {
	public:
		void read_dimacs(std::istream& in) {
			std::string line="", dummy;
			while (line.substr(0,4) != "p sp")
			getline(in,line);

			std::stringstream linestr;
			linestr.str(line);
			linestr >> dummy >> dummy >> n >> m;
			this->resize(n);
			unsigned i=0;
			while (i++ < m) {
				getline(in,line);
				if (line.substr(0,2) == "a ") {
					std::stringstream arc(line);
					unsigned u,v,w;
					char ac;
					arc >> ac >> u >> v >> w;
					this->add_edge(u-1,v-1,w); // process edge (u,v) with weight w
				}
			}
		}

		std::vector<Node> get_neighbours(int vertex){
			return adjacency_list[vertex];
		}

		int get_total_vertices(){
			return n;
		}

	private:
		std::vector<std::vector<Node>> adjacency_list;
		unsigned n, m;

		void add_edge(int origin, int destiny, int weight){
			adjacency_list[origin].push_back(Node{destiny,weight});
		}

		void resize(unsigned n){
			adjacency_list.resize(n);
		}
};
