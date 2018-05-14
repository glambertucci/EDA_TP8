#include "Allegro\allegroClass.h"
#include "Quadtree.h"
#include <cstdio>
int main(int argc, char ** argv)
{
	allegro_c Allegrotools(SCREEN_H,SCREEN_W);
	Allegrotools.load_music("Music/Antman.wav");
	Allegrotools.play_music();
	
	return 0;
}