#pragma once
#include <vector>
#include "allegroClass.h"
#include "../Quadtree.h"
#include "../ImageHandler.h"
#include "../Directories/lodepng.h"
#include <iostream>
#include "../Directories/filesystem_header.h"
using namespace std;
enum{DECOMPRESS,COMPRESS};

class menu
{
public:
	menu(vector <string>& paths_,int mode_,string background_,int th);
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
	int threshold;
	ALLEGRO_BITMAP * background;
};

