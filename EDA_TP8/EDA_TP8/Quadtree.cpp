#include "Quadtree.h"



void encoder(ofstream & output, int x, int y, int lenght, int totalSize, unsigned char * rawPNG, int threshold)
{
	if ((lenght == 1) || (thresholdColor(rawPNG, x, y, lenght, totalSize, threshold))) {
		createLeaf(output, averageColor(output, x, y, lenght, totalSize, rawPNG));
		return;
	}
	else
		createNode(output);

	encoder(output, x, y, lenght / 2, totalSize, rawPNG, threshold);
	encoder(output, x + lenght / 2, y, lenght / 2, totalSize, rawPNG, threshold);
	encoder(output, x, y + lenght / 2, lenght / 2, totalSize, rawPNG, threshold);
	encoder(output, x + lenght / 2, y + lenght / 2, lenght / 2, totalSize, rawPNG, threshold);

}

void decoder(ifstream & input, unsigned char * rawPNG, unsigned int x, unsigned int y, unsigned int totalSize, unsigned int lenght)
{
	char val[1];
	input.read(val, 1);
	if (*val == 'N') {
		char color[3];
		input.read(color, 3);
		paintRegion(x, y, lenght, rawPNG, { (unsigned char)color[R],(unsigned char)color[G] ,(unsigned char)color[B] , 0xff }, totalSize);
	}
	else if (*val == 'B') {
		decoder(input, rawPNG, x, y, totalSize, lenght / 2);
		decoder(input, rawPNG, x + lenght / 2, y, totalSize, lenght / 2);
		decoder(input, rawPNG, x, y + lenght / 2, totalSize, lenght / 2);
		decoder(input, rawPNG, x + lenght / 2, y + lenght / 2, totalSize, lenght / 2);
	}
}


void createLeaf(ofstream & output, array<unsigned int, 3> color)
{
	output << 'N' << (unsigned char)color[R] << (unsigned char)color[G] << (unsigned char)color[B];
}


void createNode(ofstream & output)
{
	output << 'B';
}


