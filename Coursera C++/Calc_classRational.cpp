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

int gcd(int a, int b) {
        while (a!=0 && b!=0) {
            if (a>b) {
                a=a%b;
            }
            else b=b%a;
        }
        return a+b;
    }

int nok(const int& a, const int& b) {
	return (a * b / gcd(a, b));
}

class Rational {
public:
    Rational() {
    	p = 0;
    	q = 1;
    }

    Rational(const long& numerator, const long& denominator) {
    	if (denominator == 0) {
    		throw invalid_argument("Invalid argument");
    	}

    	bool positivity = true;
    	if (numerator * denominator < 0) {
    		positivity = false;
    	}
    	long num = abs(numerator);
    	long den = abs(denominator);
    	long nod = gcd(num, den);
    	if (nod != 1) {
    		p = num / nod;
    		q = den / nod;
    	} else {
    		p = num;
    		q = den;
    	}
    	if (!positivity) {
    		p = -p;
    	}
    }

    long Numerator() const {
    	return p;
    }

    long Denominator() const {
    	return q;
    }

private:
    long p = 0;
    long q = 1;
    long nod = 1;

};


bool operator== (const Rational& lhs, const Rational& rhs) {
	if (lhs.Numerator() == rhs.Numerator()
			&& lhs.Denominator() == rhs.Denominator()) {
		return true;
	}
	return false;
}

Rational operator+ (const Rational& lhs, const Rational& rhs) {
	int common = nok(lhs.Denominator(), rhs.Denominator());
	int lu = lhs.Numerator() * (common / lhs.Denominator());
	int ru = rhs.Numerator() * (common / rhs.Denominator());
	return Rational(lu + ru, common);
}

Rational operator- (const Rational& lhs, const Rational& rhs) {
	int common = nok(lhs.Denominator(), rhs.Denominator());
		int lu = lhs.Numerator() * (common / lhs.Denominator());
		int ru = rhs.Numerator() * (common / rhs.Denominator());
		return Rational(lu - ru, common);
}

Rational operator* (const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator()*rhs.Numerator(),
			lhs.Denominator()*rhs.Denominator());
}

Rational operator/ (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("Division by zero");
	}

	return Rational(lhs.Numerator()*rhs.Denominator(),
			lhs.Denominator()*rhs.Numerator());
}

ostream& operator<<(ostream& stream, const Rational& rat) {
	stream << rat.Numerator() << "/" << rat.Denominator();
	return stream;
}

istream& operator>>(istream& stream, Rational& rat) {
	int p, q;
	    if (stream >> p && stream.ignore(1) && stream >> q) {
	        rat = { p, q };
	    }
	    return stream;
}

bool operator< (const Rational& lhs, const Rational& rhs) {
	int common = nok(lhs.Denominator(), rhs.Denominator());
	int lu = lhs.Numerator() * (common / lhs.Denominator());
	int ru = rhs.Numerator() * (common / rhs.Denominator());
	if (lu < ru) {
		return true;
	}
	return false;
}

int main() {
	Rational left, right, result;
	char operation;
	try {
	cin >> left >> operation >> right;
	} catch  (invalid_argument& ia) {
		cout << ia.what();
		return 0;
	}

	try {
		if (operation == '+') {
			result = left + right;
		} else if (operation == '-') {
			result = left - right;
		} else if (operation == '*') {
			result = left * right;
		} else if (operation == '/') {
			result = left / right;
		}
	} catch (domain_error& de) {
		cout << de.what();
		return 0;
	}
	cout << result;
	    return 0;
}

