#pragma once
#include <array>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

enum { R, G, B, A };


void unsquarePicture(unsigned char ** rawPNG, unsigned int & OrigW, unsigned int & OrigH);

void findNextPower(unsigned int& num);

void checkAndResizePicture(unsigned char ** rawPNG, unsigned int& w, unsigned int& h);

void paintRegion(unsigned int x, unsigned int y, unsigned int lenght, unsigned char * rawPNG, array<unsigned char, 4> color, unsigned int totalSize);

void getSize(ifstream& input, unsigned int& w, unsigned int & h, unsigned int & squaredEdge);

void setSize(ofstream& output, unsigned int& w, unsigned int & h);

bool thresholdColor(unsigned char * rawPNG, int x, int y, int lenght, int totalSize, int threshold);

array<unsigned int, 3> averageColor(ofstream & output, int x, int y, int lenght, int totalSize, unsigned char * rawPNG);
