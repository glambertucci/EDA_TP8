#include "Allegro\allegroClass.h"
#include "Allegro\menu.h"
#include <cstdio>
int main(int argc, char ** argv)
{
	allegro_c Allegrotools(SCREEN_H,SCREEN_W);
	Allegrotools.load_music("Music/Antman.wav");
	Allegrotools.play_music();
	vector <string> name;
	name.push_back( "eda1.jpg");
	name.push_back("eda2.jpg");
	name.push_back("eda3.jpg");
	name.push_back("eda4.jpg");
	name.push_back("eda5.jpg");
	name.push_back("eda6.jpg");
	name.push_back("eda7.png");
	menu men(name,0,"Images/background.jpg");
	men.print_menu();

	al_rest(120.0);
	return 0;
}