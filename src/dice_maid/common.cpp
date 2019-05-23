#include "common.h"

using namespace std;
using namespace boost::random;

taus88 engine;

string& strip(string& s) {
	if (s.empty()) return s;
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

int random(int min, int max) {
	uniform_int_distribution dist(min, max);
	return dist(engine);
}

int random(int sides) {
	return random(1, sides);
}

static void _split(const string& s, char delim, vector<string>& elems) {
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) { elems.push_back(item); }
}

vector<string> split(const string& s, char delim) {
	vector<string> elems;
	_split(s, delim, elems);
	return elems;
}

string extract(string& values, int index, char delim = ' ') {
	if (values.length() == 0) return string("");

	vector<string> x = split(values, delim);
	try {
		return x.at(index);
	}
	catch (const out_of_range& oor) {
		return string("");
	}
}

bool start_with(const string& str, const string& head) {
	int srclen   = str.size();
	int startlen = head.size();
	if (srclen >= startlen) {
		string temp = str.substr(0, startlen);
		return temp == head;
	}
	return false;
}
