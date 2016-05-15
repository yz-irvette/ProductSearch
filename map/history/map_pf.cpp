#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <climits>
using namespace std;

#define WALK_PER_NODE 5
//#define NUM_DATA 1000000
#define CONTINUE_PROB 0.975

class Edge {
  public: 
	string from, to;
	float total_weight;
  	Edge (string& _from, string& _to, float _total_weight) {
		from = _from;
		to = _to;
		total_weight = _total_weight;
	}
};

string RandNextNode(vector<Edge>& next, float random) {
	/*if (random <= next[0].total_weight) {
		return next[0].b;
	}*/
	int l = 0, r = next.size() - 1;
	while (l < r) {
		if (random > next[(l+r)/2].total_weight) {
			l = (l+r)/2 + 1;
		} else if (random <= next[(l+r)/2].total_weight) {
			r = (l+r)/2;
		}
	}
	return next[l].to;
}

map<string, vector<Edge> > node_edge;
vector<string> nodes;
//map<string, string> fo_map;

int main() {
	/*
	FILE* fp = fopen("shoe_fo_freq.csv", "r");
	while (fp != NULL && !feof(fp)) {
		char in_a[50], in_b[50];
		fscanf(fp, "%[^,],%[^\r]\r\n", in_a, in_b);
		//cout << string(in_a) << " " << string(in_b) << endl;
		string a(in_a);
		string b(in_b);
		fo_map[a] = b;
	}
	fclose(fp);	
	*/

	FILE* fp = fopen("individual_fo", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^|]|%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
		//if (fo_map.find(b) != fo_map.end()) {
		//	b = fo_map[b];
		//cout << a << " " << b << endl;
		Edge e_a(a, b, weight 
			+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
		node_edge[a].push_back(e_a);
		Edge e_b(b, a, weight 
			+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
		node_edge[b].push_back(e_b);
		//}
	}
	fclose(fp);

	fp = fopen("bag_fo", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^|]|%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
			Edge e_a(a, b, weight 
				+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
			node_edge[a].push_back(e_a);
			Edge e_b(b, a, weight 
				+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
			node_edge[b].push_back(e_b);
	}
	fclose(fp);

	fp = fopen("cloth_fo", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^|]|%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
			Edge e_a(a, b, weight 
				+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
			node_edge[a].push_back(e_a);
			Edge e_b(b, a, weight 
				+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
			node_edge[b].push_back(e_b);
	}
	fclose(fp);

/*
	fp = fopen("computer_fo", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^|]|%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
			Edge e_a(a, b, weight 
				+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
			node_edge[a].push_back(e_a);
			Edge e_b(b, a, weight 
				+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
			node_edge[b].push_back(e_b);
	}
	fclose(fp);
	*/

	fp = fopen("earphone_fo", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^|]|%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
			Edge e_a(a, b, weight 
				+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
			node_edge[a].push_back(e_a);
			Edge e_b(b, a, weight 
				+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
			node_edge[b].push_back(e_b);
	}
	fclose(fp);

	fp = fopen("film_fo", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^|]|%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
			Edge e_a(a, b, weight 
				+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
			node_edge[a].push_back(e_a);
			Edge e_b(b, a, weight 
				+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
			node_edge[b].push_back(e_b);
	}
	fclose(fp);

	fp = fopen("laptop_fo", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^|]|%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
			Edge e_a(a, b, weight 
				+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
			node_edge[a].push_back(e_a);
			Edge e_b(b, a, weight 
				+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
			node_edge[b].push_back(e_b);
	}
	fclose(fp);

	fp = fopen("phone_fo", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^|]|%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
			Edge e_a(a, b, weight 
				+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
			node_edge[a].push_back(e_a);
			Edge e_b(b, a, weight 
				+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
			node_edge[b].push_back(e_b);
	}
	fclose(fp);

	fp = fopen("protect_fo", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^|]|%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
			Edge e_a(a, b, weight 
				+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
			node_edge[a].push_back(e_a);
			Edge e_b(b, a, weight 
				+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
			node_edge[b].push_back(e_b);
	}
	fclose(fp);

	fp = fopen("skin_fo", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^|]|%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
			Edge e_a(a, b, weight 
				+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
			node_edge[a].push_back(e_a);
			Edge e_b(b, a, weight 
				+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
			node_edge[b].push_back(e_b);
	}
	fclose(fp);

/*
	fp = fopen("order", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "%[^,],%[^,],%f\r\n", in_a, in_b, &weight);
		string a(in_a);
		string b(in_b);
		if (weight < 8) {
			continue;
		}
		weight /= 100;
		Edge e_a(a, b, weight 
			+ (node_edge[a].size()==0 ? 0 : (node_edge[a][node_edge[a].size()-1].total_weight)));
		node_edge[a].push_back(e_a);
		Edge e_b(b, a, weight 
			+ (node_edge[b].size()==0 ? 0 : (node_edge[b][node_edge[b].size()-1].total_weight)));
		node_edge[b].push_back(e_b);
	}
	fclose(fp);
*/


	//cout << "import edge completed" << endl;
	srand((unsigned) time(NULL));
	for (map<string, vector<Edge> >::iterator it = node_edge.begin(); it != node_edge.end(); it++) {
		nodes.push_back(it->first);
	}
	int node_num = nodes.size();
	for (int i = 0; i < WALK_PER_NODE; i++) {
		random_shuffle(nodes.begin(), nodes.end());
		// ramdom a node to start
		//map<string, vector<Edge> >::iterator it = node_edge.begin();
		//advance(it, rand() % node_edge.size());
		for (int i = 0; i < node_num; i++) {
			string from = nodes[i]; 
			cout << from;
			while (true) {
				float random = ((float) rand()) / INT_MAX;
				if (random > CONTINUE_PROB) {
					break;
				}
				from = RandNextNode(node_edge[from], random / CONTINUE_PROB
					* (node_edge[from][node_edge[from].size()-1].total_weight));
				cout << " " << from;
			}
			cout << endl;
		}
	}
	return 0;
}