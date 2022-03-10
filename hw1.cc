#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

class Node{
	public:
		map<int, pair<int, int>> adj_list_;
		int cost;
		map<int, int> route_table_;
};

int main(){
	int tot_nodes, tot_dis_nodes, tot_links;
	int skip, node1, node2, old_w, new_w;
	int i;
			map<int, pair<int, int>>::iterator iter;
	
	cin>>tot_nodes>>tot_dis_nodes>>tot_links;
	Node nodes[tot_nodes];
	int dis_nodes[tot_dis_nodes];

	for(i=0; i<tot_dis_nodes; i++)
		cin>>dis_nodes[i];
	for(i=0; i<tot_links; i++){
		cin>>skip>>node1>>node2>>old_w>>new_w;
		nodes[node1].adj_list_[node2] = pair<int, int>(old_w, new_w);
		nodes[node2].adj_list_[node1] = pair<int, int>(old_w, new_w);
	}

		/* input debugger
		for(i=0; i<tot_nodes; i++){
			cout<<"node:"<<i<<" neighbour:\n";
			for(iter=nodes[i].adj_list_.begin(); iter!=nodes[i].adj_list_.end(); iter++){
				cout<<iter->first<<'\t'<<iter->second.first<<' '<<iter->second.second<<'\n';
			}
			nodes[node1].adj_list_[node2] = pair<int, int>(old_w, new_w);
		}
		*/
	
}
