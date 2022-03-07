#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Node{
	public:
		vector<int> adj_list;
		map<int, int> route_table;
		int old_weight;
		int new_weight;
};

int main(){
	int tot_nodes, tot_dis_nodes, tot_links;
	int input;
	int i;
	
	cin>>tot_nodes>>tot_dis_nodes>>tot_links;
	Node nodes[tot_nodes];
	vector<int> dis_nodes(tot_dis_nodes);

	for(i=0; i<tot_dis_nodes; i++){
		cin>>input;
		dis_nodes.push_back(input);
	}

}
