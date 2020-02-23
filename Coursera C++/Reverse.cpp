#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Reverse(vector<int>& v) {
	vector<int> tmp = v;
	v.clear();
	for (int i = tmp.size() - 1; i >= 0; --i) {
				v.push_back(tmp[i]);
		}
}

int main() {
	vector<int> numbers = {1, 5, 3, 4, 2};
	Reverse(numbers);
    return 0;
}
