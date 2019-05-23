#pragma once

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/random.hpp>

using namespace std;
using namespace boost::random;

extern taus88 engine;

int random(int, int);
int random(int);

string& strip(string&);
static void	_split(const string&, char, vector<string>&);
vector<string> split(const string&, char);
string extract(string&, int, char);

bool start_with(const string&, const string&);