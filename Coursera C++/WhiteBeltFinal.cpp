#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include <set>
#include <exception>
using namespace std;

class Date {
public:
  int GetYear() const {
  	  return year;
  }
  int GetMonth() const{
	  return month;
  }
  int GetDay() const {
	  return day;
  }
  void SetYear(int new_value) {
	  year = new_value;
  }
  void SetMonth(int new_value) {
  	  month = new_value;
  }
  void SetDay(int new_value) {
  	  day = new_value;
  }

private:
  int year;
  int month;
  int day;
};

Date ParseDate(string& str) {
	stringstream ss;
	int foo = 0;
	Date new_date;
	ss << str;

	if (ss.peek() == '-') {
		ss.ignore(1);
	}

	if (!isdigit(ss.peek())) {
		throw domain_error("Wrong date format: " + str);
	} else {
		ss >> foo;
		new_date.SetYear(foo);
	}

	if (ss.peek() == '-') {
		ss.ignore(1);
	} else {
		throw domain_error("Wrong date format: " + str);
	}

	if (ss.peek() == '+') {
			ss.ignore(1);
	}

	if (!isdigit(ss.peek())) {
		throw domain_error("Wrong date format: " + str);
	} else {
		ss >> foo;
		new_date.SetMonth(foo);
	}

	if (ss.peek() == '-') {
			ss.ignore(1);
		} else {
			throw domain_error("Wrong date format: " + str);
		}

		if (ss.peek() == '+') {
				ss.ignore(1);
	}

	if (!isdigit(ss.peek())) {
			throw domain_error("Wrong date format: " + str);
		} else {
			ss >> foo;
			new_date.SetDay(foo);
		}


	if (!ss.eof()) {
		throw domain_error("Wrong date format: " + str);
	}

	if (new_date.GetMonth() > 12 || new_date.GetMonth() < 1) {
		string error = "Month value is invalid: " + to_string(new_date.GetMonth());
		throw invalid_argument(error);
	}

	if (new_date.GetDay() > 31 || new_date.GetDay() < 1) {
		string error = "Day value is invalid: " + to_string(new_date.GetDay());
		throw invalid_argument(error);
	}

	return new_date;
}


ostream& operator<<(ostream& stream, const Date& dat) {
	stream << setw(4) << setfill('0') << dat.GetYear() << '-'
			<< setw(2) << setfill('0') << dat.GetMonth() << '-'
			<< setw(2) << setfill('0') << dat.GetDay();
	return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear()) {
		return true;
	} else if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() < rhs.GetMonth()) {
		return true;
	} else if (lhs.GetYear() == rhs.GetYear()
				&& lhs.GetMonth() == rhs.GetMonth()
				&& lhs.GetDay() < rhs.GetDay()) {
		return true;
	}
	return false;
}


class Database {
public:
  void AddEvent(const Date& date, const string& event) {
	  db[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event) {
	  if (db.find(date) != db.end() && db.size() != 0) {
		  for (const auto item : db[date]) {
		  	  if (item == event) {
			  	  db[date].erase(event);
			  	  return true;
		  	  }
	  	  }
	  }
	  return false;
  }

  int DeleteDate(const Date& date) {
	  int n = 0;
	  if (db.find(date) != db.end() && db.size() != 0) {
		  n = db.at(date).size();
		  db.erase(date);
	  }
	  return n;
  }

  void Find(const Date& date) const {
	  if (db.find(date) != db.end() && db.size() != 0) {
		  for (const auto item : db.at(date)) {
			  cout << item << endl;
	  	  }
	  }
  }

  void Print() const {
	  if (db.size() != 0) {
		  for (const auto [key, value] : db) {
			  for (const auto event : value) {
				  cout << key << ' ' << event << endl;
			  }
		  }
	  }
  }
private:
  map<Date, set<string>> db;
};

string ReadDate(istream& stream) {
	string str;
	stream >> str;
	return str;
}


int main() {
  Database db;

  string command;


  while (getline(cin, command)) {
	  if (command == "") {
		  continue;
	  }

	  istringstream iss;
	  string operation;
	  iss.str(command);
	  iss >> operation;

	  if (operation == "Add") {
		  string event, date_str;
		  Date date;
		  date_str = ReadDate(iss);
		  try {
			  date = ParseDate(date_str);
		  } catch (domain_error& de) {
			  cout << de.what() << endl;
		  } catch (invalid_argument& ia) {
			  cout << ia.what() << endl;
		  }
		  iss >> event;
		  db.AddEvent(date, event);
	  } else if (operation == "Del") {
		  string event, date_str;
		  Date date;
		  bool next = true;
		  date_str = ReadDate(iss);
		  try {
			  date = ParseDate(date_str);
		  } catch (domain_error& de) {
			  cout << de.what() << endl;
			  next = false;
		  } catch (invalid_argument& ia) {
			  cout << ia.what() << endl;
			  next = false;
		  }

		  iss >> event;
		  if (event != "" && next) {
			   if (db.DeleteEvent(date, event)) {
				   cout << "Deleted successfully" << endl;
			   } else {
				   cout << "Event not found" << endl;
			   }
		  } else if (next) {
			  cout << "Deleted " << db.DeleteDate(date) << " events"<< endl;
		  }
	  } else if (operation == "Find") {
		  string date_str;
		  Date date;
		  date_str = ReadDate(iss);
		  try {
			  date = ParseDate(date_str);
		  } catch (domain_error& de) {
			  cout << de.what() << endl;
		  } catch (invalid_argument& ia) {
			  cout << ia.what() << endl;
		  }
		  db.Find(date);
	  } else if (operation == "Print") {
		  db.Print();
	  } else {
		  cout << "Unknown command: " << operation << endl;
	  }

  }

  return 0;
}
