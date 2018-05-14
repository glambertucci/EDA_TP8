#include "Allegro\allegroClass.h"
#include "Allegro\menu.h"
#include <cstdio>
#include "Utils/parser.h"
#include "Directories/filesystem_header.h"


vector<string> listall(path p,bool mode_);


int main(int argc, char ** argv)
{
	allegro_c Allegrotools(SCREEN_H, SCREEN_W);
	Allegrotools.load_music("Music/Antman.wav");
	Allegrotools.play_music();
	userInfo data;

	if (!parseCmdLine(argc, argv, &callback, (void*)&data)) {
		vector<string> path_of_pngs;
			if (check_existance(data.userpath.c_str())) { // poner en lugar de EXAMPLE el argv[1]
				cout << ">> Empezando a buscar archivos" << endl;
				path_of_pngs = listall(data.userpath.c_str(),data.mode); // tenemos los pngs en del directorio que nos pasaron!
				if (path_of_pngs.size() == 0) {return -1;}
				cout << ">> Archivos encontrados." << endl;
			}
			else {
				cout << ">> Input error: el directorio no es valido." << endl;
			}
		menu men(path_of_pngs, data.mode, "Utils/background.jpg",data.threshold);
		men.print_menu();
		men.select(Allegrotools.getEventQueue());
		//Menu tiene un metodo que es getstate bool creo que basicamente lo que esta en 1 son los que hay que comprimir/decomprimir, el iterador
		//de esos numeros es equivalente al iterador del vector de paths
		men.workfile();

	}
	return 0;
}

vector<string> listall(path p,bool mode_) {
	directory_iterator end_itr;
	vector<string> found;
	// cycle through the directory
	for (directory_iterator itr(p); itr != end_itr; ++itr){
		// If it's not a directory, list it. If you want to list directories too, just remove this check.
		if (is_regular_file(itr->path())) {
			// assign current file name to current_file and echo it out to the console.
			string current_file = itr->path().string();
			if (current_file.size() >= 5) { // al menos es un a.png
				if (!strcmp(&current_file[current_file.size() - 4], mode_==COMPRESS? ".png" : ".gay")) {//DEBUG
					found.push_back(current_file);
					path aux(current_file);
				}
			}
		}
	}
	return found;
}