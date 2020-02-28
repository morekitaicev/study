#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


void NewBus(map<string, vector<string>>& list, map<int, string>& origin,
		const string& bus, const vector<string>& stops){
	origin[origin.size() - 1] = bus;
	list[bus] = stops;
}

vector<string> BusesForStop(map<string, vector<string>>& list, map<int, string>& origin,
		const string& stop) {
	vector<string> result;
	for (const auto& number : origin) {
		vector<string> bus_stops = list[number.second];
		for (int i = 0; i < bus_stops.size(); ++i) {
				if (bus_stops[i] == stop) {
					result.push_back(number.second);
				}
		}
	}
	return result;
	/* if (result.size() == 0) {
		cout << "No stop";
	} else {
		for (int i = 0; i < result.size(); ++i) {
			cout << result[i] << " ";
		}
	}
	cout << endl; */
}


void StopsForBus(map<string, vector<string>>& list, map<int, string>& origin, const string& bus) {
	if (list.count(bus) == 0) {
		cout << "No bus" << endl;
	} else {
		vector<string> stops;
		stops = list[bus];
		for (int i = 0; i < stops.size(); ++i) {
			vector<string> bus_for_stop = BusesForStop(list, origin, stops[i]);
			if (bus_for_stop.size() == 1 && bus_for_stop[0] == bus) {
				cout << "Stop " << stops[i] << ": ";
				cout << "no interchange" << endl;
				continue;
			} else {
				cout << "Stop " << stops[i] << ": ";
				for (int j = 0; j < bus_for_stop.size(); ++j){
					if (bus_for_stop[j] != bus) {
						cout << bus_for_stop[j] << " ";
					}
				}
				cout << endl;
			}
		}
	}
}

void AllBuses(map<string, vector<string>>& list) {
	if (list.size() == 0) {
		cout << "No buses" << endl;
	} else {
		for (const auto& bus : list) {
			cout << "Bus " << bus.first << ": ";
			vector<string> stops;
					stops = list[bus.first];
			for (int i = 0; i < stops.size(); ++i) {
				cout << stops[i] << " ";
			}
			cout << endl;
		}
	}
}

int main() {
    int n;
    cin >> n;
    map<string, vector<string>> routes;
    map<int, string> origin;
    for (int i = 0; i < n; ++i) {
        string command;
        cin >> command;

        if (command == "NEW_BUS") {
            string bus;
            int stop_count;
            cin >> bus >> stop_count;
            vector<string> stops(stop_count);

            for (int s = 0; s < stop_count; ++s) {
                cin >> stops[s];
            }

            NewBus(routes, origin, bus, stops);
        } else if (command == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;
            vector<string> result = BusesForStop(routes, origin, stop);
            if (result.size() == 0) {
            		cout << "No stop";
            	} else {
            		for (int i = 0; i < result.size(); ++i) {
            			cout << result[i] << " ";
            		}
            	}
            	cout << endl;
        } else if (command == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;
            StopsForBus(routes, origin, bus);
        } else if (command == "ALL_BUSES") {
            AllBuses(routes);
        }

    }

    return 0;
}
