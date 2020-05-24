## Graph Algorithms

1. Breadth-First Search
2. Depth-First Search

## Graph Inputs

AdjacencyGraph(Ligra Framework)
1. Directed/Undirected
2. Disjoint components

## Command to synthesize graph inputs using graph generator from Ligra
Parameters required are No. of vertices and output file name
The number of edges by default are 10 times the no. of vertices
Below command shows generating a graph input with 1M vertices and filename as rMat_1000000 

./rMatGraph 1000000 rMat_1000000

## Enabling parallel execution for Ligra, Compiling with OpenMP
#define environment variable, compile the code using make command

$ export OPENMP=1
$ make
g++ -fopenmp -march=native -03 -DOPENMP -o BFS BFS.C 

##Run the code with different inputs

./BFS -r 1 ../inputs/rMat_1000000
