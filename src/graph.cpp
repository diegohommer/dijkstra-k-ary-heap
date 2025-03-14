#include <iostream>
#include <sstream>
#include <unordered_map> 
#include <vector>

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
					this->add_edge(u,v,w); // process edge (u,v) with weight w
				}
			}
		}

	private:
		std::vector<std::unordered_map<int,int>> adjacency_list;
		unsigned m, n;

		void add_edge(int origin, int destiny, int weight){
			adjacency_list[origin][destiny] = weight;
		}

		void resize(unsigned n){
			adjacency_list.resize(n);
		}
}


