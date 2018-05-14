#include "menu.h"

menu::menu(vector <string>& paths_,int mode_)
{
	paths = paths_;
	mode = mode_;
}


menu::~menu()
{
}
void menu::print_menu()
{
	int iterator = this->paths.size();
	for (int i = 0; i < iterator; i++)
	{
		this->bitmaps.push_back(al_load_bitmap(paths[i].c_str()));
	}
}