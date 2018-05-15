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
	char valueToDecode = input.get();
	unsigned int depth = 0, branch = 0, iterator = 0;
	
	array<unsigned char, 3> color = { 0,0,0 };
	bool isB;			//False para N, true para B
	while (!input.eof())
	{
		do {
			if (valueToDecode == 'B') {
				depth++;
			}
		} while (valueToDecode != 'N');
		if (depth == 0) {			//Imagen monocromatica
			color[R] = input.get();
			color[G] = input.get();
			color[B] = input.get();
			//DIBUJO ESO
		}
		else if (depth > 0) {					//Imagen subdividida en cuadrantes
			branch++;							//Me posiciono en una rama
			if (branch <= 4) {					//Como se que luego de una N vienen los 3 bytes de color
				color[R] = input.get();
				color[G] = input.get();
				color[B] = input.get();
				//DIBUJO		
			}
			else if (branch > 4) {				//Mientras no me pase de esta condicion, mantengo mi nivel en el arbol para iterar 
				branch = 1;						//Una vez que se cumpla esta condicion reinicio en 1 la rama, volviendo al nodo padre
				depth--;						//al que se llega decrementando la profundidad del arbol
			}
		}
	}
}

void reconstructImg(array<unsigned char, 3> & color, int depth, int branch, unsigned int measure, vector<unsigned char>& pngImage, unsigned char alpha)
{
	unsigned int orgX = 0, orgY = 0;
	unsigned int quadrantMeasure = measure / pow(2,depth);
	getOriginQuad(orgX, orgY, depth, branch, measure);		// CON ESTA FUNCIÖN TENGO PROBLEMAS, buscar el "cero" para el cuadrado 

	unsigned int  maxX, maxY;
	maxX = orgX + (quadrantMeasure) * 4; 
	maxY = orgY + (quadrantMeasure);

	for (unsigned int i = orgX; i < maxX; i += 4){
		for (unsigned int j = orgY; j < maxY; j++){
			pngImage[i + j * (measure * 4)] = color[R];
			pngImage[i + j * (measure * 4) + 1] = color[G];
			pngImage[i + j * (measure * 4) + 2] = color[B];
			pngImage[i + j * (measure * 4) + 3] = alpha;
		}
	}
}

void getOriginQuad(unsigned int& corrX, unsigned int& corrY, int depth, int branch, unsigned int width)
{

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
		retValue[a] = retValue[a] / (counter ? counter : 1);					// Esto es para evitarlo si es transparente

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