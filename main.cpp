#include <QCoreApplication>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <QString>
#include <iostream>
#include <cstring>
#include "funciones_imagen.h"

using namespace std;

uint8_t desplazarBitsIzq(uint8_t valor, int bits);

uint8_t desplazarBitsDer(uint8_t valor, int bits);

bool verificarTransformacionIzq(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                                int seed, int size,  int argumento);

bool verificarTransformacionDer(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                                int seed, int size,  int argumento);


void aplicarTransformacion(unsigned char* pixelData, int seed, int size, int argumento);

QString nombreArchivoPaso(int paso);



// ---------------------- MAIN ----------------------

int main() {
    QString archivoEntrada = "I_D.bmp";
    QString archivoMascara = "M.bmp";

    int width_img = 0, height_img = 0;
    unsigned char* pixelData = loadPixels(archivoEntrada, width_img, height_img);

    int width_mask = 0, height_mask = 0;
    unsigned char* mascaraData = loadPixels(archivoMascara, width_mask, height_mask);


    //int DimensionImagen = width_img * height_img * 3;
    int DimensionMascara = width_mask * height_mask * 3;

    char** transformaciones = nullptr;
    int totalTransformaciones = 0;

    int pasos = 0;
    cout << "Ingrese el numero total de archivos Mx.txt: ";
    cin >> pasos;

    for (int paso = pasos; paso >= 1; --paso) {
        QString archivoPaso = nombreArchivoPaso(paso);
        if (!QFile::exists(archivoPaso)) {
            cout << "Archivo no encontrado: " << archivoPaso.toStdString() << endl;
            continue;
        }

        int seed = 0;
        int n_pixels = 0;
        unsigned int* maskingData = loadSeedMasking(archivoPaso.toStdString().c_str(), seed, n_pixels);
        if (!maskingData) continue;

        int tamanioMascara = n_pixels * 3;
        if (tamanioMascara > DimensionMascara) {
            cerr << "La mascara es mas pequena que el bloque requerido por " << archivoPaso.toStdString() << endl;
            delete[] maskingData;
            continue;
        }

        bool encontrado = false;

        for (int modo = 1; modo < 2; ++modo) {
            for (int bits = 1; bits <= 8; ++bits) {

                if (modo == 1){
                    if (verificarTransformacionIzq(
                        pixelData, mascaraData, maskingData,
                            seed, tamanioMascara, bits))
                    {
                        aplicarTransformacion(
                            pixelData, seed, tamanioMascara, bits);


                        encontrado = true;
                        break;
                    }
                }


                if (modo == 2){
                    if (verificarTransformacionDer(
                            pixelData, mascaraData, maskingData,
                            seed, tamanioMascara, bits))
                    {
                        aplicarTransformacion(
                            pixelData, seed, tamanioMascara, bits);

                        encontrado = true;
                        break;
                    }




                }

            }
            if (encontrado) break;
        }

        if (!encontrado)
            cout << "Ninguna transformacion valida para " << archivoPaso.toStdString() << endl;

        delete[] maskingData;
    }

    cout << "\nTransformaciones aplicadas (orden inverso):" << endl;
    for (int i = 0; i < totalTransformaciones; ++i) {
        cout << "- " << transformaciones[i] << endl;
        free(transformaciones[i]);
    }
    free(transformaciones);

    delete[] pixelData;
    delete[] mascaraData;

    return 0;
}



// ---------------------- FUNCIONES DE TRANSFORMACION ----------------------

uint8_t desplazarBitsIzq(uint8_t valor, int bits) {
    return (valor << bits) & 0xFF;
}

uint8_t desplazarBitsDer(uint8_t valor, int bits) {
    return (valor >> bits);
}

// ---------------------- FUNCIONES AUXILIARES ----------------------

bool verificarTransformacionIzq(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                                int seed, int size, int argumento) {
    for (int i = 0; i < size; ++i) {
        int idx = seed + i;
        //if (idx >= totalImageSize) return false;

        uint8_t original = pixelData[idx];
        uint8_t transformado = desplazarBitsIzq(original, argumento);
        uint8_t enmascarado = (transformado + mascara[i]) & 0xFF;
        cout<<endl<<enmascarado-'0' << " "<< referencia[i]<<endl;

        if (enmascarado != referencia[i]) return false;
    }
    return true;
}

bool verificarTransformacionDer(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                                int seed, int size, int argumento) {
    for (int i = 0; i < size; ++i) {
        int idx = seed + i;
        //if (idx >= totalImageSize) return false;

        uint8_t original = pixelData[idx];
        uint8_t transformado = desplazarBitsDer(original, argumento);
        uint8_t enmascarado = (transformado + mascara[i]) & 0xFF;
        cout<<endl<<enmascarado-'0' << " "<< referencia[i]<<endl;

        if (enmascarado != referencia[i]) return false;
    }
    return true;
}


void aplicarTransformacion(unsigned char* pixelData, int seed, int size, int argumento) {

}

void registrarTransformacion(const char* nombre) {

}

QString nombreArchivoPaso(int paso) {
    return QString("M%1.txt").arg(paso);
}
