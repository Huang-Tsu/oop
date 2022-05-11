#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <climits>	//for INT_MAX
#define  OLD 0
#define  NEW 1
#define  WEIGHT_CNT 2
using namespace std;

class Graph{
	public:
		Graph(int row_length, int tot_dest_nodes);
		vector< vector<map<int, int> > > node_adj_list_;	//weight_type<node_id<adj_node_id, adj_node_weight> >
		vector<int> distance_;
		vector< vector< map< int, int> > > route_table_;
		vector<int> dest_;
		void BellmanFord();
		void InitNodes(int destination);
		void Relax(int start, int end, int dest, int weight_type);
};

int main(){
	int link, node1, node2, old_w, new_w;
	int tot_nodes, tot_dest_nodes, tot_links, destination;
	int i, j;
	
			//input data
		//input total number of data
	cin>>tot_nodes>>tot_dest_nodes>>tot_links;
	Graph graph(tot_nodes, tot_dest_nodes);

		//input total destination nodes
	for(i=0; i<tot_dest_nodes; i++){
		cin>>destination;
		graph.dest_[i] = destination;

			//init nodes route_table
		for(j=0; j<tot_nodes; j++){
				graph.route_table_[OLD][j][destination] = graph.route_table_[NEW][j][destination] = -1;
		}
	}
		//input all links
	for(i=0; i<tot_links; i++){
		cin>>link>>node1>>node2>>old_w>>new_w;
		graph.node_adj_list_[OLD][node1][node2] = old_w;
		graph.node_adj_list_[OLD][node2][node1] = old_w;
		graph.node_adj_list_[NEW][node1][node2] = new_w;
		graph.node_adj_list_[NEW][node2][node1] = new_w;
	}

	graph.BellmanFord();

			//output
		//output of old weight
	int next_node_of_new_weight;
	int next_node_of_old_weight;
	int dest_node;
	for(int node_now=0; node_now<tot_nodes; node_now++){
		cout<<node_now<<'\n';
		for(i=0; i<tot_dest_nodes; i++){
			dest_node = graph.dest_[i];
			if(node_now != dest_node){
				cout<<graph.dest_[i]<<" "<<graph.route_table_[OLD][node_now][dest_node]<<'\n';
			}
		}
	}
		//output of new weight
	int counter;
	for(int node_now=0; node_now<tot_nodes; node_now++){
		counter = 0;
		for(i=0; i<tot_dest_nodes; i++){
			dest_node = graph.dest_[i];
			next_node_of_old_weight = graph.route_table_[OLD][node_now][dest_node];
			next_node_of_new_weight = graph.route_table_[NEW][node_now][dest_node];
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

	return 0;
	
}
void Graph::BellmanFord(){
	int dest_cnt = dest_.capacity();
	unsigned int node_cnt = distance_.capacity();
	int adj_node;
	map<int, int>::iterator iter;


	for(int weight=0; weight<WEIGHT_CNT; weight++){
		for(int dest=0; dest<dest_cnt; dest++){
			this->InitNodes(dest_[dest]);	

			for(int k=0; k<node_cnt-1; k++){	//run at most n-1 times, because each time will find at least one more shortest path's link.
				for(int node=0; node<node_cnt; node++){	//each time, relax() every adjacent_node of every node
					for(iter=node_adj_list_[weight][node].begin(); iter!=node_adj_list_[weight][node].end(); iter++){	//對第j node之所有link relax
						adj_node = iter->first;
						this->Relax(node, adj_node, dest_[dest], weight);
					}
				}
			}

		}
	}
}
void Graph::Relax(int start, int end, int dest, int weight_type){		//start:start point(node) of a link, end:end point(node) of a link
	if(distance_[start] != (1<<32)-1){
	unsigned int link_weight 					= node_adj_list_[weight_type][start][end];
	unsigned int test_weight 					= distance_[start]+link_weight;
	unsigned int next_node_of_end  		= route_table_[weight_type][end][dest];
		if((test_weight==distance_[end] && start<next_node_of_end) ||
				test_weight<distance_[end]){
			route_table_[weight_type][end][dest] = start;
			distance_[end] = test_weight;
		}
	}
}
void Graph::InitNodes(int destination){
	int len = distance_.capacity();
	for(int i=0; i<len; i++)
		distance_[i] = (1<<32)-1;

	distance_[destination] = 0;
}
Graph::Graph(int row_length, int tot_dest_nodes){

	vector< map<int, int> > route_table_row_length(row_length);
	route_table_.assign(WEIGHT_CNT, route_table_row_length);
	node_adj_list_.assign(WEIGHT_CNT, route_table_row_length);

	int nodes_cnt = row_length;

	dest_.reserve(tot_dest_nodes);

	distance_.reserve(nodes_cnt);
}

