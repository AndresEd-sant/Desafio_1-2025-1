#include <QCoreApplication>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <QString>
#include <iostream>
#include <cstring>
#include "funciones_imagen.h"

using namespace std;

unsigned int desplazarBitsIzq(unsigned int valor, int bits);

unsigned int desplazarBitsDer(unsigned int valor, int bits);

unsigned int Xor(unsigned int pixel1, unsigned int pixel2);

uint8_t RotacionBitsIzq(uint8_t valor, int bits);

uint8_t RotacionBitsDer(uint8_t valor, int bits);

QString nombreArchivoPaso(int paso);

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
void aplicarTransformacion(unsigned char* pixelData, unsigned short int modo,
                           unsigned short int bits, unsigned int tamanio_im,
                           unsigned char* pixeldata2 = nullptr);

QString nombreArchivoPaso(int paso);



// ---------------------- MAIN ----------------------

int main() {
    QString archivoEntrada = "I_D.bmp";
    QString archivoMascara = "M.bmp";

    int width_img = 0, height_img = 0;
    unsigned char* pixelData = loadPixels(archivoEntrada, width_img, height_img);

    int width_mask = 0, height_mask = 0;
    unsigned char* mascaraData = loadPixels(archivoMascara, width_mask, height_mask);


    unsigned int DimensionImagen = width_img * height_img * 3;

    int pasos = 0;
    cout << "Ingrese el numero total de archivos Mx.txt: ";
    cin >> pasos;

    for (int paso = pasos; paso >= 0; --paso) {
        QString archivoPaso = nombreArchivoPaso(paso);
        if (!QFile::exists(archivoPaso)) {
            cout << "Archivo no encontrado: " << archivoPaso.toStdString() << endl;
            continue;
        }

        int seed = 0, n_pixels = 0;
        unsigned int* maskingData = loadSeedMasking(archivoPaso.toStdString().c_str(), seed, n_pixels);

        int tamanioMascara = n_pixels * 3;
        bool encontrado = false;

        for (int bits = 1; bits <= 8 && !encontrado; ++bits) {
            if (verificarTransformacionIzq(pixelData, mascaraData, maskingData, seed, tamanioMascara, bits)) {
                cout << "Transformacion encontrada : desplazamiento izquierda " << bits << " bits\n";
                aplicarTransformacion(pixelData, 1, bits, DimensionImagen);
                encontrado = true;
            } else if (verificarTransformacionDer(pixelData, mascaraData, maskingData, seed, tamanioMascara, bits)) {
                cout << "Transformacion encontrada : desplazamiento derecha " << bits << " bits\n";
                aplicarTransformacion(pixelData, 2, bits, DimensionImagen);
                encontrado = true;
            }
        }

        if (!encontrado) {
            int w2 = 0, h2 = 0;
            unsigned char* pixelData_I_M = loadPixels("I_M.bmp", w2, h2);
            if (verificarXoR(pixelData, mascaraData, maskingData, seed, tamanioMascara, pixelData_I_M)) {
                cout << " Transformacion encontrada : XOR con I_M.bmp\n";
                aplicarTransformacion(pixelData, 3, 0, DimensionImagen, pixelData_I_M);
                encontrado = true;
            }
            delete[] pixelData_I_M;
        }
        if (!encontrado){

            for (int bits = 1; bits <= 8 && !encontrado; ++bits) {
                if (verificarRotacionIzq(pixelData, mascaraData, maskingData, seed, tamanioMascara, bits)) {
                    cout << "Transformacion encontrada : rotacion a la derecha de " << bits << " bits\n";
                    aplicarTransformacion(pixelData, 4, bits, DimensionImagen);
                    encontrado = true;
                }

                else if (verificarRotacionDer(pixelData, mascaraData, maskingData, seed, tamanioMascara, bits)) {
                    cout << "Transformacion encontrada : rotacion a la derecha de " << bits << " bits\n";
                    aplicarTransformacion(pixelData, 5, bits, DimensionImagen);
                    encontrado = true;
                }
            }

        }

        if (!encontrado)
            cout << "Ninguna transformacion valida para " << archivoPaso.toStdString() << endl;

        delete[] maskingData;
    }

    delete[] pixelData;
    delete[] mascaraData;



    return 0;
}



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
    return ((valor << bits) | (valor >> (8 - bits))) & 0xFF;
}

uint8_t RotacionBitsDer(uint8_t valor, int bits) {
    return ((valor >> bits) | (valor << (8 - bits))) & 0xFF;
}
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

// ---------------------- FUNCION DE TRANSFORMACIÓN ----------------------
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

QString nombreArchivoPaso(int paso) {
    return QString("M%1.txt").arg(paso);
}
