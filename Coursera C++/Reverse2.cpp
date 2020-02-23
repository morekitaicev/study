#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> Reversed(const vector<int>& v) {
	vector<int> tmp;
	for (int i = v.size() - 1; i >= 0; --i) {
				tmp.push_back(v[i]);
		}
	return tmp;
}

int main() {
	vector<int> numbers = {1, 5, 3, 4, 2};
	Reversed(numbers);
    return 0;
}
