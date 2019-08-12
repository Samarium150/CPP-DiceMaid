#pragma once

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <boost/random.hpp>

using namespace std;
using namespace boost::random;

extern mt19937 engine;

namespace common {
int random(int, int);
int random(int);
}  // namespace common

string&	strip(string&);
static void	_split(const string&, char, vector<string>&);
vector<string> split(const string&, char);
string extract(string&, int, char);

bool start_with(const string&, const string&);