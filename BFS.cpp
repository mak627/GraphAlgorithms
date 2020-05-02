#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>

using namespace std;

class Graph{
		int numNodes;
		list<int> *adjlist;
	public:
		void createGraph(int n);
		void BFS(int start);	
};

void Graph::createGraph(int n){
	numNodes = n;
	adjlist = new list<int>[n];
	string line;
	int node,edge;
	//istringstream iss;

	ifstream inputG("input.txt");
	if (inputG.is_open()){
    	while ( getline (inputG,line) )
    	{
      	//iss.str(line);
	istringstream iss(line);
	iss>>node;
	while(iss >> edge){
		adjlist[node].push_back(edge);	
	}
	std::cout << node << endl;
	for(auto it = adjlist[node].cbegin(); it != adjlist[node].cend();++it){
		std::cout << *it << endl;
	}
    	}
	inputG.close();
	}
	else cout << "Bad input file";
}

void Graph::BFS(int start){
	
	int *Parents =  new int[numNodes];
	bool *visited = new bool[numNodes];
	list<int> queue;
	
	for(int i = 0; i < numNodes; i++){ 
        Parents[i] = -1;
        visited[i] = false;
	}
	visited[start] = true;	
	queue.push_back(start);
	
	while(!queue.empty()){
		int node = queue.front();
		queue.pop_front();
		
	for (auto it = adjlist[node].cbegin(); it != adjlist[node].cend();++it){ 
            if (!visited[*it]) 
            { 
                visited[*it] = true;
		Parents[*it] = node;
                queue.push_back(*it); 
            } 
        }		
	}
	for(int i=0;i<numNodes;i++){
	std::cout << Parents[i] << ' ';	
	}
}

int main(){
		
	Graph G;
	G.createGraph(5);
	G.BFS(0); 
	return 0;
}
