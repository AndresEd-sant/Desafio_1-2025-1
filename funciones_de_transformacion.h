#ifndef FUNCIONES_DE_TRANSFORMACION_H
#define FUNCIONES_DE_TRANSFORMACION_H

#include <QDebug>
#include <QFile>

unsigned int desplazarBitsIzq(unsigned int valor, int bits);

unsigned int desplazarBitsDer(unsigned int valor, int bits);

unsigned int Xor(unsigned int pixel1, unsigned int pixel2);

uint8_t RotacionBitsIzq(uint8_t valor, int bits);

uint8_t RotacionBitsDer(uint8_t valor, int bits);

#endif // FUNCIONES_DE_TRANSFORMACION_H
