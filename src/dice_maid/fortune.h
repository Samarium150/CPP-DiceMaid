#pragma once
#include "common.h"

namespace Fortune {
	extern unordered_map<long, int> luck_map;
	extern string date;
	bool check();
	string get_luck(long qq);
}