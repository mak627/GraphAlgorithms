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
	public:
		void createGraph();
		void BFS(int start);
		void returnPath(int s, int e);	
};

void Graph::createGraph(){
	
	int count=0; 
	string line;

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
	cout << "VertexOffset Array: "; 
	for (int i = 0; i<offset.size();i++)
		cout << offset.at(i) << ' ';
	cout << endl;
	cout << "EdgeList Array: ";
	for (int i = 0; i<edgelist.size();i++)
		cout << edgelist.at(i) << ' ';
	cout << endl;
	inputG.close();
	}
	else cout << "Bad input file";
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
		int start = offset.at(node),end;
		if(node==(numNodes-1)) end = (numEdges-1);
		else end = offset.at(node+1);
		for (int i = start; i < end;i++){
			int neighbor = edgelist.at(i); 
            		if (!visited[neighbor]) { 
                		visited[neighbor] = true;
				Parents[neighbor] = node;
                		queue.push_back(neighbor); 
            		}
        	}		
	}
	/*for(int i=0;i<numNodes;i++){
	std::cout << Parents[i] << ' ';	
	}*/
}

void Graph:: returnPath(int s, int e){
	BFS(s);
	vector<int> path;
	for(int at = e; at!=-1; at=Parents[at])
		path.push_back(at);
	std::reverse(path.begin(),path.end());
	cout << "Path from node " << s << " to node " << e << ": ";
	for(int i: path)
		cout << i << ' ';
	cout << endl;
}

int main(){
		
	Graph G;
	G.createGraph(); 
	G.returnPath(0,4);
	return 0;
}
