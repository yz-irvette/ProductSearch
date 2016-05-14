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

map<string, string> features;

int main() {
	FILE* fp = fopen("../../data/feature/feature_freq", "r");
	int a = -1;
	while (!feof(fp)) {
		char in_a[50], in_b[50];
		float weight;
		fscanf(fp, "\"%[^\"]\",\"%[^\"]\"\n", in_a, in_b);
		a = (a + 1) % 3;
		if (a != 0) continue;
		string a(in_a);
		string b(in_b);
		string parent_b = b;
		while (features.find(a) != features.end()) {
			a = features[a];
		}
		while (parent_b != a && features.find(parent_b) != features.end()) {
			b = parent_b;
			parent_b = features[parent_b];
			features[b] = a;
		}
		if (parent_b != a) {
			features[parent_b] = a;
		}
		//printf("%s, %s\n", a.c_str(), parent_b.c_str());
	}
	fclose(fp);

	//printf("%d\n", features.size());

	for (map<string, string>::iterator it = features.begin(); it != features.end(); it++) {
		string parent = it->second;
		while (features.find(parent) != features.end()) {
			parent = features[parent];
		}
		printf("\"%s\",\"%s\"\n", (it->first).c_str(), parent.c_str());
	}
	return 0;
}