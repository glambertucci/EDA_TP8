#pragma once
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#define ICONPATH "Utils/icon.png"
#define BACKGROUNDPATH "Utils/background.jpg"
#define MUSICPATH "Music/Antman.wav"
#define TUTOPATH "Utils/tutorial.png"
#define FONTPATH "Utils/Triforce.ttf"

#define FPS (50.0)
#define SCREEN_W 1000 
#define SCREEN_H 600
class allegro_c
{
public:
	allegro_c(double H, double W);
	~allegro_c();
	ALLEGRO_EVENT_QUEUE * getEventQueue();
	bool load_music(const char * music_file);
	void play_music();
	void updateDisplay();
	
private:
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_EVENT_QUEUE * ev_queue = NULL;
	ALLEGRO_SAMPLE * music = NULL;
	ALLEGRO_TIMER * timer = NULL;
};