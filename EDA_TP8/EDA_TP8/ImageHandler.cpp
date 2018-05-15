#include "ImageHandler.h"

void paintRegion(unsigned int x, unsigned int y, unsigned int lenght, unsigned char * rawPNG, array<unsigned char, 4> color, unsigned int totalSize)
{
	unsigned int basePixel = (((y ? y : 1) - 1) * 4 * totalSize) + (((x ? x : 1) - 1) * 4);
	for (int i = 0; i < lenght; i++) {
		for (int j = 0; j < lenght; j++) {
			unsigned int pixel = basePixel + (4 * i * totalSize) + (4 * j);
			for (int a = 0; a < color.size(); a++)
				rawPNG[pixel + a] = color[a];
		}
	}
}

void getSize(ifstream & input, unsigned int & w, unsigned int & h, unsigned int & squaredEdge)
{
	string buffer;
	input >> buffer;
	w = atoi(buffer.c_str());
	input >> buffer;
	h = atoi(buffer.c_str());
	input.get();

	if (w > h)
		squaredEdge = w;
	else
		squaredEdge = h;


	findNextPower(squaredEdge);
}

void setSize(ofstream & output, unsigned int & w, unsigned int & h)
{
	output << w << endl << h << endl;
}


void unsquarePicture(unsigned char ** rawPNG, unsigned int & OrigW, unsigned int & OrigH)
{
	unsigned int sqsize = (OrigH > OrigW ? OrigH : OrigW);
	findNextPower(sqsize);

	unsigned char * rectRaw = (unsigned char *)malloc(4 * OrigH * OrigW);
	unsigned char * sqRaw = *rawPNG;

	for (int i = 0; i < OrigH; i++) {
		for (int j = 0; j < OrigW; j++) {
			unsigned int pixelSq = (4 * i * sqsize) + (j * 4);
			unsigned int pixelRect = (4 * i * OrigW) + (j * 4);
			rectRaw[pixelRect + R] = sqRaw[pixelSq + R];
			rectRaw[pixelRect + G] = sqRaw[pixelSq + G];
			rectRaw[pixelRect + B] = sqRaw[pixelSq + B];
			rectRaw[pixelRect + A] = sqRaw[pixelSq + A];
		}
	}
	free(sqRaw);
	*rawPNG = rectRaw;

}

void findNextPower(unsigned int& num) {

	double log = log2(num);
	if (log - (unsigned int)log)					// Si es 0, entonces el numero ya es una potencia de dos.
		num = pow(2, (unsigned int)(log + 1));
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

bool thresholdColor(unsigned char * rawPNG, int x, int y, int lenght, int totalSize, int threshold)
{
	array<unsigned char, 3> max = { 0,0,0 }, min = { 255,255,255 };

	for (int i = 0; i < lenght; i++) {
		for (int j = 0; j < lenght; j++) {
			int pixelInicial = (4 * x + (y*totalSize * 4));
			int pixelActual = pixelInicial + (4 * i * totalSize) + (4 * j);

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
	array<unsigned int, 3 > retValue = { 0,0,0 };

	for (int i = 0; i < lenght; i++)
		for (int j = 0; j < lenght; j++) {
			int pixelInicial = (4 * x + (y * totalSize * 4));
			int pixelActual = pixelInicial + (4 * i * totalSize) + (4 * j);


			for (int a = 0; a < retValue.size(); a++)
				retValue[a] += rawPNG[pixelActual + a];
		}

	for (int a = 0; a < retValue.size(); a++)
		retValue[a] = retValue[a] / (lenght * lenght);



	return retValue;
}