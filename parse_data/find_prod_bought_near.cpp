#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <ctime>
#include <climits>
using namespace std;

class Edge {
  public: 
	string from, to;
  	Edge (string& _from, string& _to) {
		from = _from;
		to = _to;
	}
	bool operator < (const Edge& edge) const {
		return from < edge.from || from == edge.from && to < edge.to;
	}
};

class Item {
public:
	string name;
	int day, month, year;
	Item (string& _name, int& _day, int& _month, int& _year) {
		name = _name;
		day = _day, month = _month, year = _year;
	}
};

deque<Item> last;
map<Edge, int> transaction;

int main() {
	FILE* fp = fopen("buy_order.csv", "r");
	string* last_person = NULL;
	while (fp != NULL && !feof(fp)) {
		char in_a[50], in_b[50], in_c[50];
		int day, month, year;
		fscanf(fp, "\"%[^\"]\",\"%[^\"]\",\"%d/%d/%d\",\"%[^\"]\"\r\n", in_a, in_b, &month, &day, &year, in_c);
		string prod(in_a);
		string person(in_b);
		Item current(prod, day, month, year);
		if (last_person != NULL && person != *last_person) {
			while (!last.empty()) {
				last.pop_front();
			}
		} else {
			while (!last.empty()) {
				Item last_item = last.front();
				if (last_item.year == year 
					&& (last_item.month == month || month - last_item.month == 1 && day < last_item.day)
					|| year - last_item.year == 1 && last_item.month == 12 
					&& month == 1 && day < last_item.day) {
					break;
				}
				last.pop_front();
			}
			for (deque<Item>::iterator it = last.begin(); it != last.end(); it++) {
				transaction[Edge(it->name,prod)]++;
			}
		}
		last.push_back(current);
		last_person = &person;
	}
	fclose(fp);	

	for (map<Edge, int>::iterator it = transaction.begin(); it != transaction.end(); it++) {
		if (it->second < 10) {
			continue;
		}
		cout << (it->first).from << "," << (it->first).to << "," << ((float) it->second)/10 << endl;
	}
	return 0;
}
