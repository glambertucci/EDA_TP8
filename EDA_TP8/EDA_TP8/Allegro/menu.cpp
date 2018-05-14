#include "menu.h"
#include "WrittenBox.h"
menu::menu(vector <string>& paths_,int mode_,string background_)
{
	paths = paths_;
	mode = mode_;
	this->background = al_load_bitmap(background_.c_str());
	al_draw_bitmap(background, 0, 0, 0);

}


menu::~menu()
{
}
void menu::print_menu()
{
	
	int iterator = this->paths.size();
	if(mode==COMPRESS){
	for (int i = 0; (i < iterator) && (i< 9); i++)
		this->bitmaps.push_back(al_load_bitmap(paths[i].c_str()));
	for (int i = 0; i < iterator && i < 9; i++)
		al_draw_scaled_bitmap(this->bitmaps[i], 0, 0, al_get_bitmap_width(this->bitmaps[i]), al_get_bitmap_height(this->bitmaps[i]), 50 + (i >= 3 ? (i >= 6 ? ((i - 6) * 200):((i - 3) * 200)) : (i * 200)), (i >= 3 ? (i >= 6 ? (500) : (300)) : (100)), 150, 100, NULL);
	}
	else
	{
		for (int i = 0; (i < iterator) && (i < 9); i++)
		{
			WrittenBox box((50.0+(i >= 3 ? (i >=6 ? ((i - 06) * 200) : ((i - 3) * 200)) : (i * 200))), (i >= 3 ? (i >= 6 ? (500.0) : (300.0)) : (100.0)),150.0, 100.0,20,paths[i].c_str(),"antman.ttf", "mediumorchid");
			box.draw();
		}
	}

	al_flip_display();
}