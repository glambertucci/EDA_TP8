#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
int callback(char * key, char * value, void * info);
typedef int(*pCallback) (char *, char*, void *);
typedef struct
{
	std::string userpath;
	int threshold;
	bool mode;
}userInfo;

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);
//Recibe la informacion de linea de comando, la funcion a operar y una base de datos
//devuelve la cantidad de parametros ingresados


enum { ERROR1 = -3, ERROR2, ERROR3 };
//error 1 es opcion sin valor, error 2 es opcion sin clave error3 es no encontrado

