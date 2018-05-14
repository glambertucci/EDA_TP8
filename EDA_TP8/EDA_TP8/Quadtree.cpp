#include "Quadtree.h"

void encoder(ostream & output, int x, int y, int lenght, char ** rawPNG, int threshold)
{
	if ((lenght == 1) || (thresholdColor(rawPNG, x, y, lenght, threshold))) {
		createLeaf(output,averageColor(output, x, y, lenght, rawPNG));
		return;
	} else
		createNode(output);

	encoder(output, x, y, lenght / 2, rawPNG, threshold);
	encoder(output, x + lenght / 2, y, lenght / 2, rawPNG, threshold);
	encoder(output, x, y + lenght / 2, lenght / 2, rawPNG, threshold);
	encoder(output, x + lenght / 2, y + lenght / 2, lenght / 2, rawPNG, threshold);

}

bool thresholdColor(char ** rawPNG, int x, int y, int lenght, int threshold)
{
	bool retValue;
	unsigned char maxRed = 0, maxBlue = 0, maxGreen = 0;
	unsigned char minRed = 255, minBlue = 255, minGreen = 255;

	for (int i = 0; i < lenght; i++) {
		for (int j = 0; j < lenght; j++) {
			if (maxRed < rawPNG[(y + i * lenght) + (x + j)][0])		// Almacena los maximos y minimos del color rojo
				maxRed = rawPNG[(y + i * lenght) + (x + j)][0];
			if (minRed >rawPNG[(y + i * lenght) + (x + j)][0])	//DUDA: seria un else if o un if?
				minRed = rawPNG[(y + i * lenght) + (x + j)][0];

			if (maxGreen < rawPNG[(y + i * lenght) + (x + j)][1])	// Almacena los maximos y minimos del color verde
				maxGreen = rawPNG[(y + i * lenght) + (x + j)][1];
			if (minGreen >rawPNG[(y + i * lenght) + (x + j)][1])
				minGreen = rawPNG[(y+ i * lenght) + (x + j)][1];

			if (maxBlue < rawPNG[(y + i * lenght) + (x + j)][2])	// Almacena los maximos y minimos del color azul
				maxBlue = rawPNG[(y + i * lenght) + (x + j)][2];
			if (minBlue >rawPNG[(y + i * lenght) + (x + j)][2])
				minBlue = rawPNG[(y + i * lenght) + (x + j)][2];
		}
	}

	int score = (maxRed - minRed) + (maxGreen - minGreen) + (maxBlue - minBlue);
	
	return score < threshold;
}

array<unsigned char, 3> averageColor(ostream & output, int x, int y, int lenght, char ** rawPNG)
{
	array<unsigned char, 3> retValue = { 0,0,0 };
	
	for (int i = 0; i < lenght; i++) 
		for (int j = 0; j < lenght; j++) 
			for (int a = 0; a < retValue.size(); a++) 
				retValue[a] = +rawPNG[(x + i * lenght) + (y + j)][a];

	for (int a = 0; a < retValue.size(); a++)
		retValue[a] = retValue[a] / (lenght * lenght);


	return retValue;
}

void createLeaf(ostream & output, array<unsigned char, 3> color)
{
	output << 'N'<< color[R] << color[G] << color[B];

}

void createNode(ostream & output)
{
	output << 'B';
}
