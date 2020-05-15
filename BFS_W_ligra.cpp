#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph{
		int numNodes, numEdges;
		vector<int> offset, edgelist, wgtlist, Parents;
		vector<pair<uint,uint>> *adjlist;
	public:
		void createGraph(bool isUndirected);
		void BFS_W(int start);
			
};
//read weighted graph from input file and store in a data structure
void Graph::createGraph(bool isUndirected){
	
	int count=0;
	int buffer_start, buffer_end; 
	string line;

	ifstream inputG("input_W_ligra.txt");
	if (inputG.is_open()){
	while(getline (inputG,line)){
		++count;
		if(count==1) continue;
		else if(count==2) {numNodes = stoi(line); continue;}
		else if(count==3) {numEdges = stoi(line); continue;}
		else {
			if(count >= 4 && count <= (numNodes+3)){offset.push_back(stoi(line));}
			else if(count > (numNodes+3) && count <= (numEdges+numNodes+3)){edgelist.push_back(stoi(line));}
			else {wgtlist.push_back(stoi(line));}		
		};
	}
	cout << "No. of Nodes = " << numNodes << endl;
	cout << "No. of Edges = " << numEdges << endl;
	inputG.close();
	}
	else cout << "Bad input file";
	adjlist = new vector<pair<uint,uint>>[numNodes];
	for(int vid=0; vid<numNodes;vid++){
		buffer_start = offset.at(vid);
		if(vid==(numNodes-1)) buffer_end = numEdges;
		else buffer_end = offset.at(vid+1);
		if(buffer_start == buffer_end) continue;
		else{
			for(int eid=buffer_start;eid<buffer_end;eid++){
			adjlist[vid].push_back(pair<uint,uint>(edgelist.at(eid),wgtlist.at(eid)));
			if(isUndirected) adjlist[edgelist.at(eid)].push_back(pair<uint,uint>(vid,wgtlist.at(eid)));
			}
		}
	}
	for (int i = 0; i<numNodes;i++){
		cout << "Edgelist of node" << i << ": ";
		for(auto& neighbor: adjlist[i])
			cout << neighbor.first << '-' << neighbor.second << ' ';
		cout << endl;
	}
}

//Incomplete BFS function for weighted graph
void Graph::BFS_W(int start){
	
	//bool visited[numNodes];
	int distance[numNodes];
	fill_n(distance, numNodes, 999);
	distance[start] = 0;
	priority_queue<pair<int,int>, vector<int>, greater<int>> pqueue;
	pqueue.push(start);
	
	for(int i = 0; i < numNodes; i++){ 
        Parents.push_back(-1);
        //visited[i] = falsse;
	}
	//visited[start] = true;
	
	while(!pqueue.empty()){
		int node = pqueue.top();
		pqueue.pop();
		cout << node << endl;
		/*for (auto& neighbor: adjlist[node]){
            		if(distance[neighbor.first] > distance[node] + neighbor.second){
				 distance[neighbor.first] = distance[node] + neighbor.second;
            		}
        	}*/		
	}
	/*for(int i=0;i<numNodes;i++)	std::cout << Parents[i] << ' ';
	cout << endl;*/
}

int main(){
		
	Graph G;
	G.createGraph(false);
	G.BFS_W(0); 
	return 0;
}
