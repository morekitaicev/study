#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void ChangeCapital(map<string, string>& list, const string& country, const string& capital){
	if (list.count(country) == 0) {
		list[country] = capital;
		cout << "Introduce new country "<< country << " with capital " << capital << endl;
	} else if (list[country] == capital) {
		cout << "Country " << country << " hasn't changed its capital" << endl;
	} else if (list[country] != capital && list.count(country) == 1) {
		string old_capital = list[country];
		list[country] = capital;
		cout << "Country " << country << " has changed its capital from " << old_capital
				<< " to " << capital << endl;
	}
}

void Rename(map<string, string>& list, const string& old_country, const string& new_country) {
	if (old_country == new_country
			|| list.count(old_country) == 0
			|| list.count(new_country) == 1) {
		cout << "Incorrect rename, skip" << endl;
	} else {
		string old = old_country, capital = list[old_country];
		list.erase(old);
		list[new_country] = capital;
		cout << "Country " << old << " with capital " << capital
				<<" has been renamed to " << new_country << endl;
	}
}

void About(map<string, string>& list, const string& country) {
	if (list.count(country) == 0) {
		cout << "Country " << country << " doesn't exist" << endl;
	} else {
		cout << "Country " << country << " has capital "<< list[country];
		cout << endl;
	}
}

void Dump(const map<string, string>& list) {
	if (list.empty()) {
		cout << "There are no countries in the world" << endl;
	} else {
		for (const auto& item : list) {
			cout << item.first << "/" << item.second << endl;
		}
	}
}

int main() {
	int n;
	cin >> n;

	map<string, string> capitals;

	for (int i = 0; i < n; ++i) {
		string command;
		cin >> command;

		if (command == "CHANGE_CAPITAL") {
			string country, capital;
			cin >> country >> capital;
			ChangeCapital(capitals, country, capital);
		} else if (command == "RENAME") {
			string old_country, new_country;
			cin >> old_country >> new_country;
			Rename(capitals, old_country, new_country);
		} else if (command == "ABOUT") {
			string country;
			cin >> country;
			About(capitals, country);
		} else if (command == "DUMP") {
			Dump(capitals);
		}

	}
    return 0;
}
