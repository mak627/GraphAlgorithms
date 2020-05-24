#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Graph{
		int numNodes, numEdges;
		vector<int> Parents;
		vector<bool> visited;
		vector<int> *adjlist;
		void DFS_R(int node);
	public:
		void createGraph(bool isUndirected);
		void DFS(int start);
		void returnPath(int src, int dest);	
};

void Graph::createGraph(bool isUndirected){
	
	int count=0;
	int buffer_start, buffer_end; 
	string line;
	vector<int> offset, edgelist;

	ifstream inputG("rMat_1000000");
	//ifstream inputG("input_disconn.txt");
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
	/*for (int i = 0; i<numNodes;i++){
		cout << "Edgelist of node" << i << ": ";
		for(int neighbor: adjlist[i])
			cout << neighbor << ' ';
		cout << endl;
	}*/
}

void Graph::DFS_R(int node){
	
	visited[node] = true;
	//cout << node << ' ';
	for (auto it = adjlist[node].cbegin(); it != adjlist[node].cend();++it){ 
            	if (!visited[*it]) {
			Parents[*it] = node; 
                	DFS_R(*it);
            	} 
        }
}

void Graph::DFS(int start){
	
	for(int i = 0; i < numNodes; i++){ 
        Parents.push_back(-1);
        visited.push_back(false);
	}
	//cout << "Depth First Traversal from Node" << start << ": ";
	DFS_R(start);
	cout << endl;

	/*for(int i=0;i<numNodes;i++){
	std::cout << Parents[i] << ' ';	
	}
	cout << endl;*/
}

void Graph:: returnPath(int src, int dest){
	DFS(src);
	vector<int> path;
	for(int at = dest; at!=-1; at=Parents[at])
		path.push_back(at);
	std::reverse(path.begin(),path.end());
	cout << "Path from node" << src << " to node" << dest << ": ";
	if(path.front()==src)
		for(int i: path) cout << i << ' ';
	else
		cout << "NOT_FOUND";
	cout << endl;
}

int main(){
		
	Graph G;
	G.createGraph(false);
	//Get start time
	auto start = high_resolution_clock::now();
	G.DFS(1);
	//G.returnPath(0,1);
	//Get end time
	auto end = high_resolution_clock::now();
	auto time_diff = end - start;
	cout << duration<double,milli> (time_diff).count() << "ms" << endl; 
	return 0;
}
