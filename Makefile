## Directories
IDIR = include
SDIR = src
ODIR = obj
BDIR = bin

## Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -fopenmp -I$(IDIR)

## Source files
MAIN_SRC = $(SDIR)/main.cpp $(SDIR)/dijkstra/dijkstra.cpp $(SDIR)/dijkstra/graph.cpp $(SDIR)/dijkstra/heap.cpp
GEN_SRC = $(SDIR)/generator/gen.cpp

## Object files
MAIN_OBJ = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(MAIN_SRC))
GEN_OBJ = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(GEN_SRC))

## Executables
MAIN_EXEC = $(BDIR)/main.out
GEN_EXEC = $(BDIR)/gen.out

## Rules
all: $(MAIN_EXEC) $(GEN_EXEC)

$(MAIN_EXEC): $(MAIN_OBJ)
	@mkdir -p $(BDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(GEN_EXEC): $(GEN_OBJ)
	@mkdir -p $(BDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(ODIR)/%.o: $(SDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(ODIR) $(BDIR)

.PHONY: all clean