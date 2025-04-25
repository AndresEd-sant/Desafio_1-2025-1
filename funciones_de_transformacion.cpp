#include <QImage>
#include <QDebug>
#include <QFile>
#include <QString>
#include "funciones_de_transformacion.h"



// ---------------------- FUNCIONES DE TRANSFORMACION ----------------------


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
    return ((valor << bits) | (valor >> (8 - bits)));
}

uint8_t RotacionBitsDer(uint8_t valor, int bits) {
    return ((valor >> bits) | (valor << (8 - bits)));
}
