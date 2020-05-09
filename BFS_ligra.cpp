#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Graph{
		int numNodes, numEdges;
		vector<int> offset, edgelist, Parents;
		vector<int> *adjlist;
	public:
		void createGraph(bool isUndirected);
		void BFS(int start);
		void returnPath(int src, int dest);	
};

void Graph::createGraph(bool isUndirected){
	
	int count=0;
	int buffer_start, buffer_end; 
	string line;
	//bool isUndirected = false;

	ifstream inputG("input_ligra.txt");
	if (inputG.is_open()){
	while(getline (inputG,line)){
		++count;
		if(count==1) continue;
		else if(count==2) {numNodes = stoi(line); continue;}
		else if(count==3) {numEdges = stoi(line); continue;}
		else {
			if(count >= 4 && count <= (numNodes+3)){offset.push_back(stoi(line));}
			else if(count > (numNodes+3) && count <= (numEdges+numNodes+3)){edgelist.push_back(stoi(line));}		
		};
	}
	cout << "No. of Nodes = " << numNodes << endl;
	cout << "No. of Edges = " << numEdges << endl;
	inputG.close();
	}
	else cout << "Bad input file";
	adjlist = new vector<int>[numNodes];
	for(int vid=0; vid<numNodes;vid++){
		buffer_start = offset.at(vid);
		if(vid==(numNodes-1)) buffer_end = numEdges;
		else buffer_end = offset.at(vid+1);
		if(buffer_start == buffer_end) continue;             //node with no edges
		else{
			for(int eid=buffer_start;eid<buffer_end;eid++){
			adjlist[vid].push_back(edgelist.at(eid));
			if(isUndirected) adjlist[edgelist.at(eid)].push_back(vid);
			}
		}
	}
	for (int i = 0; i<numNodes;i++){
		cout << "Edgelist of node" << i << ": ";
		for(int neighbor: adjlist[i])
			cout << neighbor << ' ';
		cout << endl;
	}
}

void Graph::BFS(int start){
	
	//int Parents[numNodes];
	bool visited[numNodes];
	list<int> queue;
	queue.push_back(start);
	
	for(int i = 0; i < numNodes; i++){ 
        Parents.push_back(-1);
        visited[i] = false;
	}
	visited[start] = true;
	
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
	for(int i=0;i<numNodes;i++)	std::cout << Parents[i] << ' ';
	cout << endl;
}

void Graph:: returnPath(int src, int dest){
	BFS(src);
	vector<int> path;
	for(int at = dest; at!=-1; at=Parents[at])
		path.push_back(at);
	std::reverse(path.begin(),path.end());
	cout << "Path from node" << src << " to node" << dest << ": ";
	for(int i: path) cout << i << ' ';
	cout << endl;
}

int main(){
		
	Graph G;
	G.createGraph(true); 
	G.returnPath(4,0);
	return 0;
}
