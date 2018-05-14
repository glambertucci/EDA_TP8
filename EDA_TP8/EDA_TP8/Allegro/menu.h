#pragma once
#include <vector>
#include "allegroClass.h"
#include <iostream>
using namespace std;
#define COMPRESS 1
class menu
{
public:
	menu(vector <string>& paths_,int mode_,string background_);
	~menu();
	void print_menu();
private:
	vector <string> paths;
	vector <ALLEGRO_BITMAP*> bitmaps;
	int mode;
	ALLEGRO_BITMAP * background;
};

