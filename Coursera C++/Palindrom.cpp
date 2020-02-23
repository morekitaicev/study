#include <iostream>
#include <string>

bool IsPalindrom(string s) {
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

int main {
    string str;
    cin >> str;
    cout << IsPalindrom(str);
    return 0;
}