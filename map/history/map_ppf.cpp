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

#define WALK_PER_NODE 80
//#define NUM_DATA 1000000
#define CONTINUE_PROB 0.975
#define PRODUCT_TO_PRODUCT_RATIO 0.5

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

map<string, vector<Edge> > node_edge;
map<string, vector<string> > product_edge;
vector<string> nodes;
//map<string, string> fo_map;

string RandNextNode(string from, float random) {
	/*if (random <= next[0].total_weight) {
		return next[0].b;
	}*/
	if (product_edge.find(from) == product_edge.end() || random < PRODUCT_TO_PRODUCT_RATIO) {
		vector<Edge>& next = node_edge[from];
		random = random / PRODUCT_TO_PRODUCT_RATIO
				* (next[next.size()-1].total_weight);
		int l = 0, r = next.size() - 1;
		while (l < r) {
			if (random > next[(l+r)/2].total_weight) {
				l = (l+r)/2 + 1;
			} else if (random <= next[(l+r)/2].total_weight) {
				r = (l+r)/2;
			}
		}
		return next[l].to;
	} else {
		//return from;
		random = (random - PRODUCT_TO_PRODUCT_RATIO) / (1 - PRODUCT_TO_PRODUCT_RATIO)
				* product_edge[from].size();
		return product_edge[from][(int) random];
	}
}

int main() {
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


	fp = fopen("product.csv", "r");
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "\"%[^\"]\";\"%[^\"]%*[^\n]\n", in_a, in_b);
		string a(in_a);
		string b(in_b);
		if (node_edge.find(a) != node_edge.end() && node_edge.find(b) != node_edge.end()) {
			product_edge[a].push_back(b);
		}
	}
	fclose(fp);

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
				from = RandNextNode(from, random / CONTINUE_PROB);
				cout << " " << from;
			}
			cout << endl;
		}
	}
	return 0;
}