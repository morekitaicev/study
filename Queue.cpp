#include <iostream>
#include <string>
#include <vector>
using namespace std;

void come(const int& a, vector<bool>& q) {
	int n = q.size();
	q.resize(n + a, false);
}

void worry(const int& a, vector<bool>& q) {
	q[a] = true;
}

void quiet(const int& a, vector<bool>& q) {
	q[a] = false;
}

void WorryCount(const vector<bool>& q, vector<int>& result) {
	int sum = 0;
	for (auto i : q) {
		if (i) {
			++sum;
		}
	}
	result.push_back(sum);
}


int main() {
	int n;
	cin >> n;
	vector<int> result;
	string command;
	int count;

	vector<bool> people;

	for (int i = 0; i < n; ++i) {
		string command;
		int count;
		cin >> command;

		if (command == "COME") {
			cin >> count;
			come(count, people);
			continue;
		} else if (command == "WORRY") {
			cin >> count;
			worry(count, people);
			continue;
		} else if (command == "QUIET") {
			cin >> count;
			quiet(count, people);
			continue;
		} else if (command == "WORRY_COUNT") {
			WorryCount(people, result);
			continue;
		}

	}
	for (auto i : result) {
		cout << i << endl;
	}
    return 0;
}
