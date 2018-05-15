#include "Allegro\allegroClass.h"
#include "Allegro\menu.h"
#include <cstdio>
#include "Utils/parser.h"
#include "Directories/filesystem_header.h"



int main(int argc, char ** argv)
{
	userInfo data;
	if (!parseCmdLine(argc, argv, &callback, (void*)&data)) {
		vector<string> path_of_pngs;
		if (check_existance(data.userpath.c_str())) { //me fijo que exista el apth
			cout << ">> Empezando a buscar archivos" << endl;
			path_of_pngs = listall(data.userpath.c_str(), data.mode); // tenemos los pngs en del directorio que nos pasaron!
			if (path_of_pngs.size() == 0) {//Si existe el path  pero no hay ninguna imagen con esa extension
				cout << ">>No hay ninguna imagen con dicha extensión, toque enter para salir" << endl;
				getchar();
				return 0;
			}
			cout << ">> Archivos encontrados." << endl;
		}
		else {
			cout << ">> Input error: el directorio no es valido." << endl;
			cout << ">>Toque enter para salir" << endl;
			getchar();
			return 0;
		}
		allegro_c Allegrotools(SCREEN_H, SCREEN_W);
		Allegrotools.load_music(MUSICPATH);
		Allegrotools.play_music();
		menu men(path_of_pngs, data.mode, BACKGROUNDPATH, data.threshold);
		men.print_menu();
		men.update(-1);
		men.select(Allegrotools.getEventQueue());
		men.workfile();
	}
	else
	{
		cout << ">>Ha ocurrido un error de parseo, por favor ingrese por linea de comando parámetros con las siguientes especificaciones" << endl;
		cout << "Ingrese" << endl << "-Threshold [value] con el value 0<val<100" << endl;
		cout << "-method [compresion/decompresion]" << endl;
		cout << "-p [path donde guarda las imágenes]" << endl;
		cout << "Nosotros suministramos una carpeta con alguna imágenes de prueba llamada images." << endl;
		cout << "Aprete enter para salir" << endl;
		getchar();
	}
	return 0;
}

