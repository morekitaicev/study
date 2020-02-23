#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool IsPalindrom(string s) {
	for (int i = 0; i <= s.size()/2; ++i) {
		if (s[i] != s[s.size() - i - 1]) {
			return false;
		}
	}
	return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength) {
	vector<string> result;
	for (auto w : words) {
		if (w.size() >= minLength && IsPalindrom(w)) {
			result.push_back(w);
		}
	}
	return(result);
}

int main() {
	vector<string> strs = {"abacaba", "aba"};
	vector<string> result;
	int min = 2;
	result = PalindromFilter(strs, min);
	for (auto w : result){
		cout << w << " ";
	}
    return 0;
}
