#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;


int main() {
	set<string> words;
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		string w;
		cin >> w;
		words.insert(w);
	}
	cout << words.size();
    return 0;
}
