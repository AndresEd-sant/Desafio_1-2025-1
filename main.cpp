#include <QCoreApplication>
#include <QImage>
#include <QDebug>
#include <iostream>
#include "funciones_imagen.h"

using namespace std;

// Funciones mejoradas
uint8_t desplazarBitsIzq(uint8_t valor, int bits);
uint8_t desplazarBitsDer(uint8_t valor, int bits);

int main() {
    QString archivoEntrada = "I_D.bmp";

    int width = 0, height = 0;
    unsigned char *pixelData = loadPixels(archivoEntrada, width, height);

    cout << "Tamaño de la imagen: " << height << "x" << width << endl;

    // Semilla y datos de enmascaramiento
    int seed = 0;
    int n_pixels = 0;
    unsigned int *maskingData = loadSeedMasking("M2.txt", seed, n_pixels);

    cout << "\nContenido del archivo M2.txt:\n";
    for (int i = 0; i < n_pixels * 3; i += 3) {
        cout << maskingData[i] << " "
             << maskingData[i + 1] << " "
             << maskingData[i + 2] << endl;
    }

    // Prueba de desplazamiento
    cout << "\n[Prueba desplazamiento a la izquierda]\n";
    for (int bits = 1; bits <= 8; ++bits) {
        cout << "- " << bits << " bits: ";
        for (int i = 0; i < n_pixels; ++i) {
            uint8_t val = pixelData[seed + i];
            cout << int(desplazarBitsIzq(val, bits)) << " ";
        }
        cout << endl;
    }

    cout << "\n[Prueba desplazamiento a la derecha]\n";
    for (int bits = 1; bits <= 8; ++bits) {
        cout << "- " << bits << " bits: ";
        for (int i = 0; i < n_pixels; ++i) {
            uint8_t val = pixelData[seed + i];
            cout << int(desplazarBitsDer(val, bits)) << " ";
        }
        cout << endl;
    }

    delete[] pixelData;
    delete[] maskingData;

    return 0;
}

uint8_t desplazarBitsIzq(uint8_t valor, int bits) {
    return (valor << bits) & 0xFF;
}

uint8_t desplazarBitsDer(uint8_t valor, int bits) {
    return (valor >> bits);
}

