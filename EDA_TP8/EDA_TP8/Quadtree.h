#pragma once
#include <fstream>
#include <array>
#include <math.h>
#include "ImageHandler.h"


using namespace std;

// Comprime a la imagen
//
// - output: es el stream al archivo donde se va a escribir (Debe estar en modo binario)
// - x, y: son las coordenadas donde se evaluara y comprimira
// - lenght: es el lado del cuadrado a evaluar
// - totalSize: es el tama;o total de la imagen. ESTE VALOR NO DEBE CAMBIAR.
// - rawPNG: Es la imagen en formato raw
// - threshold: determina la compresion final del archivo.

void encoder(std::ofstream & output, int x, int y, int lenght, int totalSize, unsigned char * rawPNG, int threshold);


void createLeaf(std::ofstream & output, array<unsigned int, 3> color);

void createNode(std::ofstream & output);


void decoder(std::ifstream & input, unsigned char * rawPNG, unsigned int x, unsigned int y, unsigned int totalSize, unsigned int lenght);

