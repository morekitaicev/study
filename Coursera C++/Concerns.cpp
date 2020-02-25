#include <iostream>
#include <string>
#include <vector>
using namespace std;

void add(const int& day, const string& plan, vector<vector<string>>& cal){
	cal[day-1].push_back(plan);
}

void next(vector<vector<string>>& cal, int& count) {
	if (cal.size() == 31 && count % 12 == 1) { // январь -> ‘евраль
		cal[27].insert(end(cal[27]), begin(cal[28]), end(cal[28]));
		cal[27].insert(end(cal[27]), begin(cal[29]), end(cal[29]));
		cal[27].insert(end(cal[27]), begin(cal[30]), end(cal[30]));
		cal.resize(28);
		++count;
	} else if (cal.size() == 31 && count % 12 == 7) { // »юль -> јвгуст
		++count;
	}
	else if (cal.size() == 31 && count % 12 != 1 && count % 12 != 0) { // 31 -> 30
		cal[29].insert(end(cal[29]), begin(cal[30]), end(cal[30]));
		cal.resize(30);
		++count;
	} else if ((cal.size() == 30 || cal.size() == 28) && count % 12 != 0) { // 30/28 -> 31
		cal.resize(31);
		++count;
	} else if (cal.size() == 31 && count % 12 == 0) { // ƒекабрь -> январь
		++count;
	}
}

void dump(const int& day, vector<vector<string>>& cal) {
	cout << cal[day-1].size() << " ";
	if (cal[day-1].size() > 0){
		for (int i = 0; i < cal[day-1].size(); ++i){
			cout << cal[day-1][i] << " ";
		}
	}
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	vector<vector<string>> cal(31);
	int count = 1;
	for (int i = 0; i < n; ++i) {
		string command;
		cin >> command;
		if (command == "ADD"){
			int day;
			string plan;
			cin >> day;
			cin >> plan;
			add(day, plan, cal);
		} else if (command == "NEXT") {
			next(cal, count);
		} else if (command == "DUMP") {
			int day;
			cin >> day;
			dump(day, cal);
		}
	}
    return 0;
}
