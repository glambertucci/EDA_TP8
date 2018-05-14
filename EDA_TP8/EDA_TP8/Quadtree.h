#pragma once
#include <fstream>
#include <array>
enum{R,G,B};

using namespace std;

// Comprime a la imagen
//
// - output: es el stream al archivo donde se va a escribir (Debe estar en modo binario)
// - x, y: son las coordenadas donde se evaluara y comprimira
// - lenght: es el lado del cuadrado a evaluar
// - totalSize: es el tama;o total de la imagen. ESTE VALOR NO DEBE CAMBIAR.
// - rawPNG: Es la imagen en formato raw
// - threshold: determina la compresion final del archivo.

void encoder(ofstream & output, int x, int y, int lenght, int totalSize, unsigned char * rawPNG, int threshold );

bool thresholdColor(unsigned char * rawPNG, int x, int y, int lenght, int totalSize, int threshold);

array<unsigned int,3> averageColor(ofstream & output, int x, int y, int lenght, int totalSize, unsigned char * rawPNG);

void createLeaf(ofstream & output, array<unsigned int, 3> color);

void createNode(ofstream & output);