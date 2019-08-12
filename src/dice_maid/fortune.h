#pragma once
#include "common.h"

using namespace std;

namespace Fortune {

	struct member {
	    int data;
	    string time;
	};

	extern unordered_map<long, Fortune::member*> luck_map;

	void renew(Fortune::member *m);
	string get_luck(long qq);
}