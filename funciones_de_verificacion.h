#ifndef FUNCIONES_DE_VERIFICACION_H
#define FUNCIONES_DE_VERIFICACION_H

#include <QDebug>
#include <QFile>
#include <QImage.h>

bool verificarTransformacionIzq(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                                int seed, int size, int bits);
bool verificarTransformacionDer(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                                int seed, int size, int bits);
bool verificarXoR(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                  int seed, int size, unsigned char* pixelData2);
bool verificarRotacionIzq(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                          int seed, int size, int bits);
bool verificarRotacionDer(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                          int seed, int size, int bits);

#endif // FUNCIONES_DE_VERIFICACION_H
