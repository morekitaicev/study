#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

map<char, int> BuildCharCounters(const string& word) {
	map<char, int> result;
	for (const char& letter : word) {
		++result[letter];
	}
	return result;
}

void CheckAnagramm(const string& word1, const string& word2) {
	if (BuildCharCounters(word1) == BuildCharCounters(word2)) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		string one, two;
		cin >> one >> two;

		CheckAnagramm(one, two);
	}
    return 0;
}
