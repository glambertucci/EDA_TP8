#include "parser.h"
#include "../Directories/filesystem_header.h"
#include "../Allegro\menu.h"
void strToCapital(char * str);
int parseCmdLine(int argc, char *argv[], pCallback p, void * userData) {
	int final = 0, result = 0, posible = 0, error = false;

	for (int i = 1; i<argc;) {
		if (argv[i][0] == '-') { //Si el primer caracter es un - sera una opcion (opcion es clave+valor)
			if (argv[i][1] == 0) //si pasan -  solo
			{
				error = ERROR2;
				i = argc;
			}
			else if ((i + 1) >= argc)
			{
				error = ERROR1; //si es el ultimo caracter obviamente no tiene valor
				i++;
			}

			else
			{
				posible = p(&(argv[i][1]), argv[i + 1], userData);
				if (posible >= 0) {
					i += 2; //avanzo 2 parametros
					result += posible;
				}
				else {
					error = ERROR3;
					i = argc;
				}
			}
		}
		else {
			posible = p(NULL, argv[i], userData); //si no es opcion es parametro
			if (posible >= 0) {
				i++;
				result += posible;
			}
			else {
				error = ERROR3;
				i = argc;
			}
		}
	}
	if (error == ERROR1)
		final = ERROR1;
	else if (error == ERROR2)// reconoce el error
		final = ERROR2;
	else if (error == ERROR3)
		final = ERROR3;
	else
		final = result;
	return final;
}

int callback(char * key, char * value, void * info) {
	userInfo* minfo = (userInfo*)info;
	int i = 0;
	strToCapital(key);
	if (!strcmp(key, "P")) {
		(minfo)->userpath = value; return 0;
	}
	else if (!strcmp(key, "METHOD")) {
		strToCapital(value);
		if (!strcmp(value, "COMPRESION")) {
			minfo->mode = COMPRESS; return 0;
		}
		else if (!strcmp(value, "DECOMPRESION")) {
			minfo->mode = DECOMPRESS; return 0;
		}
		else return ERROR1;
	}
	else if (!strcmp(key, "THRESHOLD"))
	{
		int val = atoi(value);
		if (val > 0 && val < 100)
		{
			int aux_th = boost::lexical_cast<int>(val);
			aux_th = (aux_th * 765) / 100; // conversion de porcentage a data
			minfo->threshold = aux_th;
			return 0;
		}
		else return ERROR1;
	}
}
void strToCapital(char * str)
{

	int i = 0;

	while (str[i]) {
		str[i] = toupper(str[i]);
		i++;
	}

}