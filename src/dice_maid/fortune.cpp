#include "fortune.h"

using namespace std;

unordered_map<long, Fortune::member*> Fortune::luck_map;

string get_timestamp() {
	time_t t;
	time(&t);
	struct tm temp;
	localtime_s(&temp, &t);
	char s[10];
	strftime(s, 10, "%F", &temp);
	return string(s);
}

void Fortune::renew(Fortune::member *m) {
	string t = get_timestamp();
	if (m->time.compare(t) != 0) { 
		m->time = t;
		m->data = common::random(100);
	}
}

string Fortune::get_luck(long qq) {
	int luck = 0;
	if (Fortune::luck_map.find(qq) != Fortune::luck_map.end()) { 
		Fortune::member *m = Fortune::luck_map[qq];
		Fortune::renew(m);
		luck = m->data;
	} else {
		Fortune::member *m = (Fortune::member*)calloc(1, sizeof(Fortune::member));
		m->data = common::random(100);
		m->time = get_timestamp();
		luck = m->data;
		Fortune::luck_map.insert(pair<long, Fortune::member*>(qq, m));
	}

	stringstream s;
	s << "今日人品: " << luck;
	return s.str();
}