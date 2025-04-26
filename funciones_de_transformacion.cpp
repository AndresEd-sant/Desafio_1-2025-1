#include <QImage>
#include <QDebug>
#include <QFile>
#include <QString>
#include "funciones_de_transformacion.h"



// ---------------------- FUNCIONES DE TRANSFORMACION ----------------------


uint8_t desplazarBitsIzq(uint8_t valor,unsigned short int bits) {
    return (valor << bits) & 0xFF;
}

uint8_t desplazarBitsDer(uint8_t valor,unsigned short int bits) {
    return (valor >> bits)& 0xFF;
}

unsigned int Xor(unsigned int pixel1, unsigned int pixel2) {
    return pixel1 ^ pixel2;
}

uint8_t RotacionBitsIzq(uint8_t valor, unsigned short int bits) {
    return ((valor << bits) | (valor >> (8 - bits)))& 0xFF;
}

uint8_t RotacionBitsDer(uint8_t valor, unsigned short int bits) {
    return ((valor >> bits) | (valor << (8 - bits)))& 0xFF;
}

void aplicarTransformacion(unsigned char* pixelData, unsigned short int modo,
                           unsigned short int bits, unsigned int tamanio_im,
                           unsigned char* pixeldata2) {
    for (unsigned int i = 0; i < tamanio_im; ++i) {
        unsigned int original = pixelData[i];
        unsigned int transformado = 0;
        if (modo == 1) {
            transformado = desplazarBitsIzq(original, bits);
        }
        else if (modo == 2){
            transformado = desplazarBitsDer(original, bits);
        }
        else if (modo == 3){
            transformado = Xor(original, pixeldata2[i]);
        }
        else if (modo == 4){
            transformado = RotacionBitsIzq(original, bits);
        }
        else if (modo == 5){
            transformado = RotacionBitsDer(original, bits);
        }
        pixelData[i] = transformado;
    }
}
