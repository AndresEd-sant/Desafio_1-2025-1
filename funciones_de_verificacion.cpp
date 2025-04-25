#include "funciones_de_verificacion.h"
#include "funciones_de_transformacion.h"
#include <QImage>
#include <QDebug>
#include <QFile>


// ---------------------- FUNCIONES DE VERIFICACION ----------------------

bool verificarTransformacionIzq(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                                int seed, int size, int bits) {
    for (int i = 0; i < size; ++i) {
        unsigned int val = pixelData[seed + i];
        unsigned int resultado = desplazarBitsIzq(val, bits) + mascara[i];
        if (resultado != referencia[i]) return false;
    }
    return true;
}

bool verificarTransformacionDer(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                                int seed, int size, int bits) {
    for (int i = 0; i < size; ++i) {
        unsigned int val = pixelData[seed + i];
        unsigned int resultado = desplazarBitsDer(val, bits) + mascara[i];
        if (resultado != referencia[i]) return false;
    }
    return true;
}


bool verificarXoR(unsigned char* IM_danada, unsigned char* mascara, unsigned int* referencia,
                  int seed, int size, unsigned char* IM_mascara) {
    for (int i = 0; i < size; ++i) {
        unsigned int valor1 = IM_danada[seed + i];
        unsigned int valor2 = IM_mascara[seed + i];
        unsigned int enmascaramiento = Xor(valor1, valor2) + mascara[i];
        if (enmascaramiento != referencia[i]) return false;
    }
    return true;
}

bool verificarRotacionIzq(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                          int seed, int size, int bits) {
    for (int i = 0; i < size; ++i) {
        unsigned int val = pixelData[seed + i];
        unsigned int resultado = RotacionBitsIzq(val, bits);
        if ((resultado + mascara[i]) != referencia[i]) return false;
    }
    return true;
}
bool verificarRotacionDer(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                          int seed, int size, int bits) {
    for (int i = 0; i < size; ++i) {
        unsigned int val = pixelData[seed + i];
        unsigned int resultado = RotacionBitsDer(val, bits);
        if ((resultado + mascara[i]) != referencia[i]) return false;
    }
    return true;
}
