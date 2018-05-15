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

int see_dirContent(const char* dir);
int check_existance(const char* file);
int copyFile(const char* base, const char* targ);
int returnCurrentPath();
int createDir(const char* dir);
int seeLastWritten(const char* dir);

