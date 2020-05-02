#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>

using namespace std;

int main(){
	
	int n=5;
	list<int> *adjlist = new list<int>[n];	
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
	return 0;
}
