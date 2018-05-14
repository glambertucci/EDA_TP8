#pragma once
#include <vector>
#include "allegroClass.h"
#include <iostream>
using namespace std;
#define COMPRESS 1
#define DECOMPRESS 0
class menu
{
public:
	menu(vector <string>& paths_,int mode_,string background_);
	~menu();
	void print_menu();
	void update(int iterator);
	void select(ALLEGRO_EVENT_QUEUE * ev);
	vector <bool> * getstatebool();
	void workfile();
private:
	bool finished = false;
	vector <bool> state;
	vector <string> paths;
	vector <ALLEGRO_BITMAP*> bitmaps;
	int mode;
	bool first=true;
	int img_num;
	int firstpic=0;
	ALLEGRO_BITMAP * background;
};

