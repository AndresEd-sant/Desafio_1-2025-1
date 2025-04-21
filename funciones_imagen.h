#ifndef FUNCIONES_IMAGEN_H
#define FUNCIONES_IMAGEN_H

#include <QCoreApplication>
#include <QImage>

using namespace std;
unsigned char* loadPixels(QString input, int &width, int &height);
bool exportImage(unsigned char* pixelData, int width,int height, QString archivoSalida);
unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels);




#endif // FUNCIONES_IMAGEN_H
