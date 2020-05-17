#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int,int> int_pair;

class Graph{
		int numNodes, numEdges;
		vector<int> offset, edgelist, wgtlist;
		vector<pair<int,int>> *adjlist;
	public:
		void createGraph(bool isUndirected);
		void BFS_W(int start, int end);
			
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
	adjlist = new vector<pair<int,int>>[numNodes];
	for(int vid=0; vid<numNodes;vid++){
		buffer_start = offset.at(vid);
		if(vid==(numNodes-1)) buffer_end = numEdges;
		else buffer_end = offset.at(vid+1);
		if(buffer_start == buffer_end) continue;
		else{
			for(int eid=buffer_start;eid<buffer_end;eid++){
			adjlist[vid].push_back(pair<int,int>(edgelist.at(eid),wgtlist.at(eid)));
			if(isUndirected) adjlist[edgelist.at(eid)].push_back(pair<int,int>(vid,wgtlist.at(eid)));
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

//BFS function for weighted graph
void Graph::BFS_W(int start, int end){
	
	int distance[numNodes], Parents[numNodes];
	fill_n(Parents, numNodes, -1);
	fill_n(distance, numNodes, 999);
	distance[start] = 0;
	
	priority_queue<int_pair, vector<int_pair>, greater<int_pair>> pqueue;
	pqueue.push(make_pair(start,distance[start]));
	
	
	while(!pqueue.empty()){
		int node = pqueue.top().first;
		pqueue.pop();
		for (auto it = adjlist[node].cbegin(); it != adjlist[node].cend();++it){
            		if(distance[(*it).first] > distance[node] + (*it).second){
				distance[(*it).first] = distance[node] + (*it).second;
				pqueue.push(make_pair((*it).first,distance[(*it).first]));
				Parents[(*it).first] = node;
            		}
        	}		
	}
	
	vector<int> lowestCostPath;
	for(int at = end; at!=-1; at=Parents[at])
		lowestCostPath.push_back(at);
	reverse(lowestCostPath.begin(),lowestCostPath.end());
	cout << "Lowest Cost Path from node" << start << " to node" << end << ": ";
	if(lowestCostPath.front()==start)
		for(int i: lowestCostPath) cout << i << ' ';
	else
		cout << "NOT_FOUND";
	cout << endl;
}

int main(){
		
	Graph G;
	G.createGraph(false);
	G.BFS_W(0,4); 
	return 0;
}
