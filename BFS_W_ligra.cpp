#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Graph{
		int numNodes, numEdges;
		vector<int> offset, edgelist, wgtlist;
		vector<pair<uint,uint>> *adjlist;
	public:
		void createGraph(bool isUndirected);
			
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

//TO-DO Implement BFS function for weighted graph

int main(){
		
	Graph G;
	G.createGraph(false); 
	return 0;
}
