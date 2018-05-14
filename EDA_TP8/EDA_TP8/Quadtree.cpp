#include "Quadtree.h"

void encoder(ostream & output, int x, int y, int lenght, char ** rawPNG, int threshold)
{
	if ((lenght == 1) || (thresholdColor(rawPNG, x, y, lenght, threshold))) {
		averageColor(output, x, y, lenght, rawPNG);
		return;
	}
	createNode();
	encoder(output, x, y, lenght / 2, rawPNG, threshold);
	createNode();
	encoder(output, x + lenght / 2, y, lenght / 2, rawPNG, threshold);
	createNode();
	encoder(output, x, y + lenght / 2, lenght / 2, rawPNG, threshold);
	createNode();
	encoder(output, x + lenght / 2, y + lenght / 2, lenght / 2, rawPNG, threshold);

}

bool thresholdColor(char ** rawPNG, int x, int y, int lenght, int threshold)
{
	bool retValue;
	unsigned char maxRed = 0, maxBlue = 0, maxGreen = 0;
	unsigned char minRed = 255, minBlue = 255, minGreen = 255;

	for (int i = 0; i < lenght; i++) {
		for (int j = 0; j < lenght; j++) {
			if (maxRed < rawPNG[(x + i * lenght) + (y + j)][0])		// Almacena los maximos y minimos del color rojo
				maxRed = rawPNG[(x + i * lenght) + (y + j)][0];
			else if (minRed >rawPNG[(x + i * lenght) + (y + j)][0])	//DUDA: seria un else if o un if?
				minRed = rawPNG[(x + i * lenght) + (y + j)][0];

			if (maxGreen < rawPNG[(x + i * lenght) + (y + j)][1])	// Almacena los maximos y minimos del color verde
				maxGreen = rawPNG[(x + i * lenght) + (y + j)][1];
			else if (minGreen >rawPNG[(x + i * lenght) + (y + j)][1])
				minGreen = rawPNG[(x + i * lenght) + (y + j)][1];

			if (maxBlue < rawPNG[(x + i * lenght) + (y + j)][2])	// Almacena los maximos y minimos del color azul
				maxBlue = rawPNG[(x + i * lenght) + (y + j)][2];
			else if (minBlue >rawPNG[(x + i * lenght) + (y + j)][2])
				minBlue = rawPNG[(x + i * lenght) + (y + j)][2];
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
