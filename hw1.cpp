#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <climits>
using namespace std;

class Node{
	public:
		map<int, pair<int, int> > adj_list_;	//<adj_node, link_weight<old_weight, new_weight>>
		pair<int, int> cost_;								//old_weight, new_weight;
		map<int, pair<int, int> > route_table_; //<destination, next<old_weight, new_weight>>
};

int g_tot_nodes, g_tot_dest_nodes, g_tot_links;
Node *g_nodes;

void BellmanFord(int destinaiton);
void Relax(int from, int to, int dest);
void InitNodes(int destination);

int main(){
	int skip, node1, node2, old_w, new_w;
	int i;
	
			//input data
		//input total number of data
	cin>>g_tot_nodes>>g_tot_dest_nodes>>g_tot_links;
	g_nodes = new Node[g_tot_nodes];
	int dest_nodes[g_tot_dest_nodes];

		//input total distance nodes
	for(i=0; i<g_tot_dest_nodes; i++){
		cin>>dest_nodes[i];

			//init nodes route_table
		for(int j=0; j<g_tot_nodes; j++){
				g_nodes[j].route_table_[dest_nodes[i]] = {-1, -1};
		}
	}
		//input all links
	for(i=0; i<g_tot_links; i++){
		cin>>skip>>node1>>node2>>old_w>>new_w;
		g_nodes[node1].adj_list_[node2] = {old_w, new_w};
		g_nodes[node2].adj_list_[node1] = {old_w, new_w};
	}


	for(i=0; i<g_tot_dest_nodes; i++){
		BellmanFord(dest_nodes[i]);
	}

			//output
		//output of old weight
	int next_node_of_new_weight;
	int next_node_of_old_weight;
	int dest_node;
	for(int node_now=0; node_now<g_tot_nodes; node_now++){
		cout<<node_now<<'\n';
		for(int i=0; i<g_tot_dest_nodes; i++){
			dest_node = dest_nodes[i];
			if(node_now != dest_nodes[i]){
				next_node_of_old_weight = g_nodes[node_now].route_table_[dest_node].first;
				cout<<dest_node<<" "<<next_node_of_old_weight<<'\n';
			}
		}
	}
		//output of new weight
	int counter;
	for(int node_now=0; node_now<g_tot_nodes; node_now++){
		counter = 0;
		for(i=0; i<g_tot_dest_nodes; i++){
			dest_node = dest_nodes[i];
			next_node_of_old_weight = g_nodes[node_now].route_table_[dest_node].first;
			next_node_of_new_weight = g_nodes[node_now].route_table_[dest_node].second;
			if(node_now != dest_node &&
				 next_node_of_new_weight != next_node_of_old_weight){
				if(counter == 0){
					counter ++;
					cout<<node_now<<'\n';
				}
				cout<<dest_node<<" "<<next_node_of_new_weight<<'\n';
			}
		}
	}
	delete [] g_nodes;

	return 0;
	
}
void BellmanFord(int destination){
	int i, j;
	map<int, pair<int, int>>::iterator iter;

	InitNodes(destination);	
	for(i=0; i<g_tot_nodes-1; i++){	//run at most n-1 times, because each time will find at least one more shortest path's link.
		for(j=0; j<g_tot_nodes; j++){	//each time, relax() every adjacent_node of every node
			for(iter=g_nodes[j].adj_list_.begin(); iter!=g_nodes[j].adj_list_.end(); iter++){	//對第j node之所有link relax
				Relax(j, iter->first, destination);
			}
		}
	}
}
void Relax(int start, int end, int dest){		//start:start point(node) of a link, end:end point(node) of a link
	int start_weight 					= g_nodes[start].cost_.first;
	int end_weight 						= g_nodes[end].cost_.first;
	int link_weight 					= g_nodes[start].adj_list_[end].first;
	int test_weight 					= start_weight+link_weight;
	int next_node_of_end  		= g_nodes[end].route_table_[dest].first;

		//for old_weight of a link
	if(start_weight != INT_MAX){	//if node_weight==INT_MAX, this node has not yet build a path from dest
		if((test_weight==end_weight && start<next_node_of_end) || //node id of start < node if of next_node_of_end
				test_weight<end_weight ) {
				g_nodes[end].route_table_[dest].first = start;	//set the next node of end be start
				g_nodes[end].cost_.first = test_weight;			//set the weight of end be test_weight(weight of start + weight of link)
		}
	}
		//for new_weight of a link
	if(start_weight != INT_MAX){  //if node_weight==INT_MAX, this node has not yet build a path from dest
			//set weight to new weight
		link_weight 					= g_nodes[start].adj_list_[end].second;
		end_weight 						= g_nodes[end].cost_.second;
		start_weight 					= g_nodes[start].cost_.second;
		test_weight 					= start_weight+link_weight;
		next_node_of_end			= g_nodes[end].route_table_[dest].second;
		if((test_weight==end_weight && start<next_node_of_end) || //node id of start < node if of next_node_of_end
				test_weight<end_weight ) {
				g_nodes[end].route_table_[dest].second = start;	//set the next node of end be start
				g_nodes[end].cost_.second = start_weight+link_weight;//set the weight of end be test_weight(weight of start + weight of link)
		}
	}
}
void InitNodes(int destination){
	for(int i=0; i<g_tot_nodes; i++)
		g_nodes[i].cost_.first = g_nodes[i].cost_.second = INT_MAX;

	g_nodes[destination].cost_.first = g_nodes[destination].cost_.second = 0;
}
