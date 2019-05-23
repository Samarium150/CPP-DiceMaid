#include "fortune.h"

using namespace std;

unordered_map<long, int> Fortune::luck_map;
string Fortune::date("");

bool Fortune::check() {
	time_t t;
	time(&t);
	struct tm *temp = localtime(&t);
	char s[10];
	strftime(s, 10, "%F", temp);
	string result(s);
	if (result == date) return true;
	Fortune::date = result;
	Fortune::luck_map.clear();
	return false;
}

string Fortune::get_luck(long qq) {
	int luck = 0;
	if (Fortune::check() && Fortune::luck_map.find(qq) != Fortune::luck_map.end()) luck = Fortune::luck_map.at(qq);
	else {
		luck = random(1, 100);
		Fortune::luck_map.insert(pair<long, int>(qq, luck));
	}
	
	stringstream s;
	s << "今日人品: " << luck;
	return s.str();
}