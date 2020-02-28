#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


int main() {
	int q;
	cin >> q;

	map<int, vector<string>> routes;

	for (int i = 0; i < q; ++i) {
		int n;
		cin >> n;
		vector<string> stops(n);

		for (int s = 0; s < n; ++s) {
			cin >> stops[s];
		}

		bool exist = false;
		for (const auto& bus : routes) {
			if (bus.second == stops) {
				cout << "Already exists for " << bus.first << endl;
				exist = true;
			}
		}
		if (exist == false) {
			routes[routes.size() + 1] = stops;
			cout << "New bus " << routes.size() << endl;
		}
	}
    return 0;
}
