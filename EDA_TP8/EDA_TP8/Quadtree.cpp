#include "Quadtree.h"

int br = 0;

void encoder(ofstream & output, int x, int y, int lenght, int totalSize, unsigned char * rawPNG, int threshold)
{
	if ((lenght == 1) || (thresholdColor(rawPNG, x, y, lenght, totalSize, threshold))) {
		createLeaf(output,averageColor(output, x, y, lenght, totalSize, rawPNG));
		return;
	} else
		createNode(output);

	encoder(output, x, y, lenght / 2, totalSize, rawPNG, threshold);
	encoder(output, x + lenght / 2, y, lenght / 2, totalSize, rawPNG, threshold);
	encoder(output, x, y + lenght / 2, lenght / 2, totalSize, rawPNG, threshold);
	encoder(output, x + lenght / 2, y + lenght / 2, lenght / 2, totalSize, rawPNG, threshold);

}

void decoder(ifstream & input)
{
	char valueToDecode = input.get();
	char R, G, B;
	int levelCounter = 0;
	
	while (!input.eof())
	{		
		while (valueToDecode == 'B')
		{			//Miro si se cre� un nodo
			levelCounter++;
			valueToDecode = input.get();
			if (valueToDecode == 'N') 
			{		// Como encuentro un NoBranch seguro los siguientes 3 bytes son el RGB
				R = input.get();
				G = input.get();
				B = input.get();
			}

		}
		
	}
}


bool thresholdColor(unsigned char * rawPNG, int x, int y, int lenght, int totalSize, int threshold)
{
	array<unsigned char, 3> max = { 0,0,0 }, min = { 255,255,255 };

	for (int i = 0; i < lenght; i++) {
		for (int j = 0; j < lenght; j++) {
			int pixelInicial = (4 * x + (y*totalSize *4));
			int pixelActual = pixelInicial + (4* i * totalSize) + ( 4*j);

			for (int a = 0; a < max.size(); a++)
				if (max[a] < rawPNG[pixelActual + a])
					max[a] = rawPNG[pixelActual + a];

			for (int a = 0; a < min.size(); a++)
				if (min[a] > rawPNG[pixelActual + a])
					min[a] = rawPNG[pixelActual + a];
		}
	}

	int score = (max[R] - min[R]) + (max[G] - min[G]) + (max[B] - min[B]);
	
	return score < threshold;
}

array<unsigned int, 3> averageColor(ofstream & output, int x, int y, int lenght, int totalSize, unsigned char * rawPNG)
{
	array<unsigned int, 3> retValue = { 0,0,0 };
	
	for (int i = 0; i < lenght; i++)
		for (int j = 0; j < lenght; j++)
			for (int a = 0; a < retValue.size(); a++) {
				int pixelInicial = (4 * x + (y * totalSize * 4));
				int pixelActual = pixelInicial + (4 * i * totalSize) + (4 * j);
				retValue[a] += rawPNG[pixelActual + a];
			}

	for (int a = 0; a < retValue.size(); a++)
		retValue[a] = retValue[a] / (lenght * lenght);


	return retValue;
}

void createLeaf(ofstream & output, array<unsigned int, 3> color)
{

	output << 'N'<< (unsigned char)color[R] << (unsigned char)color[G] << (unsigned char)color[B];

}

void createNode(ofstream & output)
{	
	output << 'B';
}
