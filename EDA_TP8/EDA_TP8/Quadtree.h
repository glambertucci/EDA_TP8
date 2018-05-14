#pragma once
#include <fstream>
#include <array>

enum{R,G,B};

using namespace std;

void encoder(ostream& output, int x, int y, int lenght, char ** rawPNG, int threshold );

bool thresholdColor(char ** rawPNG, int x, int y, int lenght, int threshold);

array<unsigned char,3> averageColor(ostream& output, int x, int y, int lenght, char ** rawPNG);

void createLeaf(ostream& output, array<unsigned char, 3> color);

void createNode(ostream& output);