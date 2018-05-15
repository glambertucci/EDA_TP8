#include "menu.h"
#include "WrittenBox.h"
#include "allegroClass.h"
menu::menu(vector <string>& paths_, int mode_, string background_, int th)
{
	paths = paths_;
	mode = mode_;
	this->background = al_load_bitmap(background_.c_str());
	img_num = this->paths.size();
	for (int i = 0; i < img_num; i++)
		state.push_back(0);
	this->threshold = th;

}

void menu::workfile()
{
	bool allcero = true;
	for (int i = 0; i < img_num && allcero; i++)
	{
		if (state[i] == false)
			allcero = true;
		else allcero = false;
	}
	if (!allcero)
	{
		for (int i = 0; i < img_num; i++)
		{
			if (this->state[i] == true) {
				if (this->mode == COMPRESS) {
					int justname = paths[i].find_last_of("\\");
					string namefile = paths[i];
					namefile.erase(0, justname + 1);
					cout << "Compressing file " << namefile << endl;
					string aux = paths[i];
					int a = (aux.size());
					aux.erase(a - 4, a);
					std::ofstream out(aux + COMPEXTENSION, std::ofstream::binary);
					unsigned char * raw = NULL;
					unsigned int w = 0, h = 0;
					lodepng_decode32_file(&raw, &w, &h, this->paths[i].c_str());
					checkAndResizePicture(&raw, w, h);
					encoder(out, 0, 0, w, w, raw, this->threshold);
					out.close();
					free(raw);
				}
				else //descomprimir
				{

				}
			}
			//Aca va lo de comprimir o decomprimir, el iterador deonde sea true es el iterador de path a comrpmir / decomprimir

		}
	}
	else cout << "Nothing to work" << endl;
}
menu::~menu()
{

}
void menu::print_menu()
{

	if (mode == COMPRESS) {
		if (first) {
			for (int i = 0; (i < img_num); i++)
				this->bitmaps.push_back(al_load_bitmap(paths[i].c_str()));
			first = false;
			al_draw_bitmap(background, 0, 0, 0);
		}
		bool done = false;

		for (int i = 0; i < img_num && i < 9 && !done; i++)
		{
			int offset = firstpic / 9;
			if (firstpic + i >= img_num)
				done = true;
			else
				al_draw_scaled_bitmap(this->bitmaps[i + offset * 9], 0, 0, al_get_bitmap_width(this->bitmaps[i + offset * 9]), al_get_bitmap_height(this->bitmaps[i + offset * 9]), 50 + (i >= 3 ? (i >= 6 ? ((i - 6) * 200) : ((i - 3) * 200)) : (i * 200)), (i >= 3 ? (i >= 6 ? (500) : (300)) : (100)), 150, 100, NULL);
		}
	}
	else
	{
		if (first) {
			for (int i = 0; (i < img_num); i++)
				this->bitmaps.push_back(al_load_bitmap(paths[i].c_str()));
			first = false;
			al_draw_bitmap(background, 0, 0, 0);
		}
		for (int i = 0; (i < img_num) && (i < 9); i++)
		{
			int justname = paths[i].find_last_of("\\");
			string aux = paths[i];
			aux.erase(0, justname + 1);
			WrittenBox box((50.0 + (i >= 3 ? (i >= 6 ? ((i - 06) * 200) : ((i - 3) * 200)) : (i * 200))), (i >= 3 ? (i >= 6 ? (500.0) : (300.0)) : (100.0)), 150.0, 100.0, 10, aux.c_str(), FONTPATH, "black");
			box.draw();
		}
	}
	ALLEGRO_BITMAP * tutorial = al_load_bitmap(TUTOPATH);
	al_draw_scaled_bitmap(tutorial, 0, 0, al_get_bitmap_width(tutorial), al_get_bitmap_height(tutorial), 500, 50, 700, 600, NULL);

	al_flip_display();
}
void menu::select(ALLEGRO_EVENT_QUEUE * ev_queue)
{
	while (!finished)
	{
		ALLEGRO_EVENT ev;
		int num = 0;
		al_get_next_event(ev_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			//case ALLEGRO_KEY_1:
			//case ALLEGRO_KEY_PAD_1:
			//case ALLEGRO_KEY_2:
			//case ALLEGRO_KEY_PAD_2:
			//case ALLEGRO_KEY_3:
			//case ALLEGRO_KEY_PAD_3:
			//case ALLEGRO_KEY_4:
			//case ALLEGRO_KEY_PAD_4:
			//case ALLEGRO_KEY_5:
			//case ALLEGRO_KEY_PAD_5:
			//case ALLEGRO_KEY_6:
			//case ALLEGRO_KEY_PAD_6:
			//case ALLEGRO_KEY_7:
			//case ALLEGRO_KEY_PAD_7:
			//case ALLEGRO_KEY_8:
			//case ALLEGRO_KEY_PAD_8:
			//case ALLEGRO_KEY_9:
			//case ALLEGRO_KEY_PAD_9:
			//	num = (((ev.keyboard.keycode > ALLEGRO_KEY_0 && ev.keyboard.keycode < ALLEGRO_KEY_9) ? (ev.keyboard.keycode - ALLEGRO_KEY_0) : (ev.keyboard.keycode - ALLEGRO_KEY_PAD_0)) + firstpic);
			//	if (img_num >= num)
			//		update(num-1);
			//	break;

			case ALLEGRO_KEY_A:
				update('A');
				break;
			case ALLEGRO_KEY_N:
				update('N');
				break;
			case ALLEGRO_KEY_RIGHT:
				if (img_num > 9 && firstpic < img_num)
				{
					firstpic += 9;
					al_draw_bitmap(background, 0, 0, 0);
					update(-1);
				}
				print_menu();
				break;
			case ALLEGRO_KEY_LEFT:
				if (firstpic >= 9)
				{
					al_draw_bitmap(background, 0, 0, 0);
					firstpic -= 9;
					update(-1);
				}
				print_menu();
				break;
			case ALLEGRO_KEY_ENTER:
				finished = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				update('N');
				finished = true;
				break;
			default:
				if ((ev.keyboard.keycode > ALLEGRO_KEY_0 && ev.keyboard.keycode <= ALLEGRO_KEY_9) || (ev.keyboard.keycode > ALLEGRO_KEY_PAD_0 && ev.keyboard.keycode <= ALLEGRO_KEY_PAD_9))
				{
						num = (((ev.keyboard.keycode > ALLEGRO_KEY_0 && ev.keyboard.keycode <= ALLEGRO_KEY_9) ? (ev.keyboard.keycode - ALLEGRO_KEY_0) : (ev.keyboard.keycode - ALLEGRO_KEY_PAD_0)) + firstpic);
						if (img_num >= num)
							update(num-1);
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			update('N');
			finished = true;
		}
	}
}

vector <bool> * menu::getstatebool() {
	return &(this->state);
}
void menu::update(int iterator)
{
	if (iterator != -1) {
		if (iterator <= img_num)
			this->state[iterator] = state[iterator] == false ? true : false;
		else if (iterator == 'A')
			for (int i = 0; i < img_num; i++)
				state[i] = true;
		else
			for (int i = 0; i < img_num; i++)
				state[i] = false;
	}
	for (int i = 0; i + firstpic < img_num && i < 9; i++)
	{
		if (state[i + firstpic] == true)
		{
			al_draw_filled_rectangle(45 + (i >= 3 ? (i >= 6 ? ((i - 6) * 200) : ((i - 3) * 200)) : (i * 200)), (i >= 3 ? (i >= 6 ? (495) : (295)) : (95)), 205 + (i >= 3 ? (i >= 6 ? ((i - 6) * 200) : ((i - 3) * 200)) : (i * 200)), (i >= 3 ? (i >= 6 ? (605) : (405)) : (205)), al_map_rgb(0, 255, 0));
		}
		else {
			al_draw_filled_rectangle(45 + (i >= 3 ? (i >= 6 ? ((i - 6) * 200) : ((i - 3) * 200)) : (i * 200)), (i >= 3 ? (i >= 6 ? (495) : (295)) : (95)), 205 + (i >= 3 ? (i >= 6 ? ((i - 6) * 200) : ((i - 3) * 200)) : (i * 200)), (i >= 3 ? (i >= 6 ? (605) : (405)) : (205)), al_map_rgb(0, 0, 0));
		}
	}
	print_menu();
	al_flip_display();
}