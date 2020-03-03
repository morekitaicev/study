#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

void Add(map<string, set<string>>& list, const string& w1, const string& w2) {
	list[w1].insert(w2);
	list[w2].insert(w1);
}

void Count(map<string, set<string>>& list, const string& word) {
	int lenght = list[word].size();
	cout << lenght << endl;
}

void Check(map<string, set<string>>& list, const string& w1, const string& w2) {
	bool sim = false;
	if (list.count(w1) == 1) {
		for (const auto& item : list[w1]) {
			if (item == w2) {
				sim = true;
			}
		}
	}
	if (sim) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}


int main() {
	map<string, set<string>> similar;
	int q;
	cin >> q;

	for (int i = 0; i < q; ++i) {
		string command;
		cin >> command;

		if (command == "ADD") {
			string word1, word2;
			cin >> word1 >> word2;
			Add(similar, word1, word2);
		} else if (command == "COUNT") {
			string word;
			cin >> word;
			Count(similar, word);
		} else if (command == "CHECK") {
			string word1, word2;
			cin >> word1 >> word2;
			Check(similar, word1, word2);
		}
	}
    return 0;
}
