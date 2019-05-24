#pragma once
#include "common.h"
#include "dice.h"
#include "fortune.h"
#include "tarot.h"
#include "madness.h"

namespace Maid {
	extern unordered_map<long, int> setting;
	string get_help();
	string get_info();
    string command(long id, string msg);
	string command(long id, string name, string msg);
};
