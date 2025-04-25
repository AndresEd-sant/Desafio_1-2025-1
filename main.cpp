#include <QCoreApplication>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <QString>
#include <iostream>
#include <cstring>
#include "funciones_imagen.h"

using namespace std;

unsigned int desplazarBitsIzq(unsigned int valor, int bits) {
    return (valor << bits) & 0xFF;
}

unsigned int desplazarBitsDer(unsigned int valor, int bits) {
    return (valor >> bits);
}

unsigned int Xor(unsigned int pixel1, unsigned int pixel2) {
    return pixel1 ^ pixel2;
}

uint8_t RotacionBitsIzq(uint8_t valor, int bits) {
    return ((valor << bits) | (valor >> (8 - bits))) & 0xFF;
}

uint8_t RotacionBitsDer(uint8_t valor, int bits) {
    return ((valor >> bits) | (valor << (8 - bits))) & 0xFF;
}

QString nombreArchivoPaso(int paso) {
    return QString("M%1.txt").arg(paso);
}

bool verificarTransformacionIzq(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia, int seed, int size, int bits) {
    for (int i = 0; i < size; ++i) {
        unsigned int val = pixelData[seed + i];
        if ((desplazarBitsIzq(val, bits) + mascara[i]) != referencia[i]) return false;
    }
    return true;
}

bool verificarTransformacionDer(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia, int seed, int size, int bits) {
    for (int i = 0; i < size; ++i) {
        unsigned int val = pixelData[seed + i];
        if ((desplazarBitsDer(val, bits) + mascara[i]) != referencia[i]) return false;
    }
    return true;
}

bool verificarXoR(unsigned char* IM_danada, unsigned char* mascara, unsigned int* referencia, int seed, int size, unsigned char* IM_mascara) {
    for (int i = 0; i < size; ++i) {
        unsigned int v1 = IM_danada[seed + i];
        unsigned int v2 = IM_mascara[seed + i];
        if ((Xor(v1, v2) + mascara[i]) != referencia[i]) return false;
    }
    return true;
}

bool verificarRotacionIzq(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia, int seed, int size, int bits) {
    for (int i = 0; i < size; ++i) {
        unsigned int val = pixelData[seed + i];
        if ((RotacionBitsIzq(val, bits) + mascara[i]) != referencia[i]) return false;
    }
    return true;
}

bool verificarRotacionDer(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia, int seed, int size, int bits) {
    for (int i = 0; i < size; ++i) {
        unsigned int val = pixelData[seed + i];
        if ((RotacionBitsDer(val, bits) + mascara[i]) != referencia[i]) return false;
    }
    return true;
}
