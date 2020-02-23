#include <iostream>
#include <string>
#include <vector>
using namespace std;

void AvgTemp(const vector<int>& d){
	int sum = 0;
	vector<int> r;
	for (auto i : d) {
		sum += i;
	}
	double avg = sum / d.size();
	for (int i = 0; i < d.size(); ++i) {
		if (d[i] > avg) {
			r.push_back(i);
		}
	}

	cout << r.size() << endl;
	for (auto i : r) {
		cout << i << " ";
	}
}

int main() {
	int n;
	cin >> n;
	vector<int> days(n);
	for (int i = 0; i < n; ++i){
		cin >> days[i];
	}
	AvgTemp(days);
    return 0;
}
