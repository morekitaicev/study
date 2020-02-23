#include <iostream>
#include <string>
#include <vector>
using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination) {
	for (auto word : source) {
		destination.push_back(word);
	}
	source.clear();
}

int main() {
	vector<string> source = {"a", "b", "c"};
	vector<string> destination = {"z"};
	MoveStrings(source, destination);
	for (auto word : source) {
		cout << word << " ";
	}
	cout << "\n";

	for (auto word : destination) {
			cout << word << " ";
		}
		cout << "\n";
    return 0;
}
