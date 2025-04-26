#ifndef FUNCIONES_DE_TRANSFORMACION_H
#define FUNCIONES_DE_TRANSFORMACION_H

#include <QDebug>
#include <QFile>

unsigned int Xor(unsigned int pixel1, unsigned int pixel2);

uint8_t RotacionBitsIzq(uint8_t valor, unsigned short int bits);

uint8_t RotacionBitsDer(uint8_t valor, unsigned short int bits);

uint8_t desplazarBitsIzq(uint8_t valor, unsigned short int bits);

uint8_t desplazarBitsDer(uint8_t valor, unsigned short int bits);

void aplicarTransformacion(unsigned char* pixelData, unsigned short int modo,
                           unsigned short int bits, unsigned int tamanio_im,
                           unsigned char* pixeldata2 = nullptr);

#endif // FUNCIONES_DE_TRANSFORMACION_H
