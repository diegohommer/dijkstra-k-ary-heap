CXX = g++
CXXFLAGS = -std=c++17 -O2 -fopenmp -Iinclude  

SRC = src/main.cpp src/dijkstra/dijkstra.cpp src/dijkstra/graph.cpp src/dijkstra/heap.cpp
EXEC = main.out

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

clean:
	rm -f $(EXEC)

.PHONY: clean
