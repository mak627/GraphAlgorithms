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
		void createGraph();
		void BFS(int start);	
};

void Graph::createGraph(){
	//numNodes = n;
	//adjlist = new list<int>[n];
	string line;
	int node,edge;

	ifstream inputG("input.txt");
	if (inputG.is_open()){
    	while ( getline (inputG,line) ){
		istringstream iss(line);
		if(line[0]=='N'){
			string n;
			iss >> n;
			iss >> numNodes;
			iss.clear();
			std::cout << "No. of Nodes = " << numNodes << endl;
			adjlist = new list<int>[numNodes];
			continue;
		}
		else{
			iss>>node;
			while(iss >> edge){
				adjlist[node].push_back(edge);	
			}
		std::cout << node << endl;
		for(auto it = adjlist[node].cbegin(); it != adjlist[node].cend();++it){
			std::cout << *it << endl;
		}
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
            	if (!visited[*it]) { 
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
	G.createGraph();
	G.BFS(0); 
	return 0;
}
