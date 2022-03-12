#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <climits>
using namespace std;

class Node{
	public:
		map<int, pair<int, int>> adj_list_;
		int cost_ = INT_MAX;
		map<int, int> route_table_;
		void Relax(int from_node, int to_node);
};

int g_tot_nodes, g_tot_dis_nodes, g_tot_links;
Node *g_nodes;

void BellmanFord(int distance, int old_or_new_weight);
int main(){
	int skip, node1, node2, old_w, new_w;
	int i;
			//map<int, pair<int, int>>::iterator iter;
	
			//input data
		//input total number of data
	cin>>g_tot_nodes>>g_tot_dis_nodes>>g_tot_links;
	g_nodes = new Node[g_tot_nodes];
	int dis_nodes[g_tot_dis_nodes];
		//input total distance nodes
	for(i=0; i<g_tot_dis_nodes; i++){
		cin>>dis_nodes[i];
			//init nodes route_table
		for(int j=0; j<g_tot_nodes; j++){
				g_nodes[j].route_table_[dis_nodes[i]] = -1;
		}
	}
		//input all links
	for(i=0; i<g_tot_links; i++){
		cin>>skip>>node1>>node2>>old_w>>new_w;
		g_nodes[node1].adj_list_[node2] = {old_w, new_w};
		g_nodes[node2].adj_list_[node1] = {old_w, new_w};
	}

		/*
		for(i=0; i<tot_nodes; i++){
			cout<<"node:"<<i<<" neighbour:\n";
			for(iter=nodes[i].adj_list_.begin(); iter!=nodes[i].adj_list_.end(); iter++){
				cout<<iter->first<<'\t'<<iter->second.first<<' '<<iter->second.second<<'\n';
			}
			nodes[node1].adj_list_[node2] = pair<int, int>(old_w, new_w);
		}
		*/
	
}
void BellmanFord(int distance, int old_or_new_w){
	int i;
	map<int, pair<int, int>>::iterator iter;
	for(i=0; i<g_tot_nodes; i++){
		for(iter=g_nodes[i].adj_list_.begin(); iter!=g_nodes[i].adj_list_.end(); iter++){
			g_nodes[i].Relax(
		}
	}
	
}
void Node::Relax(int from_node, int to_node){

}
