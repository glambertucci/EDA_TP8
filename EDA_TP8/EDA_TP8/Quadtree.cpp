#include "Quadtree.h"


void findNextPower(unsigned int& num);

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

void decoder(std::ifstream & input)
{
	//char valueToDecode = input.get();
	//int depth = 0;
	//int branch = 0;
	//char R, G, B;
	//bool isB;			//False para N, true para B
	//while (!input.eof())
	//{		
	//	isB = checkNode(valueToDecode, depth, branch);
	//	if (!isB)
	//	{
	//		// Como encuentro un NoBranch seguro los siguientes 3 bytes son el RGB
	//		R = input.get();
	//		G = input.get();
	//		B = input.get();
	//		//ACA IRIA LA FUNCION QUE DIBUJA, RECIBIRIA COMO PAREMENTROS EL RGB, LA PROFUNDIDAD Y LA RAMA
	//	}
	//	else
	//		if ((branch > 0) && (branch < 4))
	//		{
	//			valueToDecode = input.get();		//Tomo el siguiente caracter codificado
	//		}
	//	
	//}
}

bool checkNode(char byteAnalize, int & depth, int & branch)
{
	if (byteAnalize == 'B')
	{			//Miro si se creó un nodo
		depth++;
		branch++;
		return true;
	}
	if (byteAnalize == 'N')
	{	
		if (branch == 4)
			depth--;
		branch--;
		return false;
	}
}

bool thresholdColor(unsigned char * rawPNG, int x, int y, int lenght, int totalSize, int threshold)
{
	array<unsigned char, 3> max = { 0,0,0 }, min = { 255,255,255 };

	for (int i = 0; i < lenght; i++) {
		for (int j = 0; j < lenght; j++) {
			int pixelInicial = (4 * x + (y*totalSize *4));
			int pixelActual = pixelInicial + (4* i * totalSize) + ( 4*j);

			if (rawPNG[pixelActual + A] != 0) {				// Esto es para evitarlo si es transparente. NO SE SI TIENE QUE IR ACA
				for (int a = 0; a < max.size(); a++)
					if (max[a] < rawPNG[pixelActual + a])
						max[a] = rawPNG[pixelActual + a];

				for (int a = 0; a < min.size(); a++)
					if (min[a] > rawPNG[pixelActual + a])
						min[a] = rawPNG[pixelActual + a];
			}
		}
	}

	int score = (max[R] - min[R]) + (max[G] - min[G]) + (max[B] - min[B]);
	
	return score < threshold;
}

array<unsigned int, 3> averageColor(std::ofstream & output, int x, int y, int lenght, int totalSize, unsigned char * rawPNG)
{
	array<unsigned int, 3> retValue = { 0,0,0 };
	unsigned int counter = 0;										// Esto es para evitarlo si es transparente
	
	for (int i = 0; i < lenght; i++)
		for (int j = 0; j < lenght; j++) {
			int pixelInicial = (4 * x + (y * totalSize * 4));
			int pixelActual = pixelInicial + (4 * i * totalSize) + (4 * j);

			if (rawPNG[pixelActual + A] != 0) {						// Esto es para evitarlo si es transparente
				counter++;
				for (int a = 0; a < retValue.size(); a++)
					retValue[a] += rawPNG[pixelActual + a];
			}
		}

	for (int a = 0; a < retValue.size(); a++)				
		retValue[a] = retValue[a] / counter;					// Esto es para evitarlo si es transparente

	return retValue;
}

void createLeaf(std::ofstream & output, array<unsigned int, 3> color)
{
	output << 'N'<< (unsigned char)color[R] << (unsigned char)color[G] << (unsigned char)color[B];
}

void createNode(std::ofstream & output)
{	
	output << 'B';
}


void checkAndResizePicture(unsigned char ** rawPNG_, unsigned int & w, unsigned int & h)
{
	unsigned int oldW = w, oldH = h;

	if (((log2((double)w) - (unsigned int)log2((double)w)) || (log2((double)h) - (unsigned int)log2((double)h) != 0)) || w != h) {

		findNextPower(w);
		findNextPower(h);

		if (w > h)
			h = w;
		else if (w < h)
			w = h;

		unsigned char * rawPNG = *rawPNG_;
		unsigned char * newRaw = (unsigned char *)malloc(sizeof(unsigned char) * 4 * w * h);
		int fixedPixel = 4 * (oldH - 1) *oldW + 4 * (oldW - 1);

		for (int i = 0; i < oldH; i++) {
			for (int a = 0; a < oldW; a++) {
				int pixel = 4 * i * w + a * 4;
				int oldPixel = 4 * i * oldW + a * 4;

				newRaw[pixel + R] = rawPNG[oldPixel + R];
				newRaw[pixel + G] = rawPNG[oldPixel + G];
				newRaw[pixel + B] = rawPNG[oldPixel + B];
				newRaw[pixel + A] = rawPNG[oldPixel + A];
			}
		}
		for (int i = 0; i < h; i++) {
			for (int a = oldW; a < w; a++) {
				int pixel = 4 * i * w + a * 4;
				newRaw[pixel + R] = rawPNG[fixedPixel + R];
				newRaw[pixel + G] = rawPNG[fixedPixel + G];
				newRaw[pixel + B] = rawPNG[fixedPixel + B];
				newRaw[pixel + A] = 0;
			}
		}

		for (int i = oldH; i < h; i++) {
			for (int a = 0; a < w; a++) {
				int pixel = 4 * i * w + a * 4;
				newRaw[pixel + R] = rawPNG[fixedPixel + R];
				newRaw[pixel + G] = rawPNG[fixedPixel + G];
				newRaw[pixel + B] = rawPNG[fixedPixel + B];
				newRaw[pixel + A] = 0;
			}
		}
		free(rawPNG);
		*rawPNG_ = newRaw;
	}
}

void findNextPower(unsigned int& num) {

	double log = log2(num);
	if (log - (unsigned int)log)					// Si es 0, entonces el numero ya es una potencia de dos.
		num = pow(2, (unsigned int)(log + 1));
}