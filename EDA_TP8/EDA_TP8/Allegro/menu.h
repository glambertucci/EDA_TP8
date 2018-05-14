#pragma once
#include <vector>
#include "allegroClass.h"
#include <iostream>
using namespace std;

class menu
{
public:
	menu(vector <string>& paths_,int mode_);
	~menu();
	void print_menu();
private:
	vector <string> paths;
	vector <ALLEGRO_BITMAP*> bitmaps;
	int mode;
};

