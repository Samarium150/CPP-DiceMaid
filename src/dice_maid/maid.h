#pragma once
#include "common.h"
#include "dice.h"
#include "fortune.h"
#include "tarot.h"
#include "madness.h"

namespace Maid {
	extern unordered_map<long, int> setting;
	string get_help();
    string command(long qq, string msg);
};
