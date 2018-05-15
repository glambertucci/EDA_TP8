#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#define COMPEXTENSION ".flg"
#define DECOMPEXTENSION ".png"
#include "../Allegro/menu.h"
using namespace std;
using namespace boost::filesystem;

vector<string> listall(path p, bool mode_);
int check_existance(const char* file);
