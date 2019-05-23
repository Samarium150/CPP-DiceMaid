#pragma once
#include "common.h"

namespace Tarot {
	extern string numbers[];
	extern string major[];
	extern string major_meaning_a[];
	extern string major_meaning_b[];
	string get_card();
	string get_card(string msg);
};