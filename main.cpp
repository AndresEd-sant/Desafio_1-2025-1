#include <QCoreApplication>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <QString>
#include <iostream>
#include <cstring>
#include "funciones_imagen.h"
#include "funciones_de_transformacion.h"
#include "Funciones_de_verificacion.h"

using namespace std;


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

    unsigned int pasos = 0;
    cout << "Ingrese el numero total de archivos Mx.txt: ";
    cin >> pasos;
    unsigned short int pasosrec =1;

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

        for (unsigned short int bits = 1; bits <= 8 && !encontrado; ++bits) {

            if (verificarDesplazamientoIzq(pixelData, mascaraData, maskingData, seed, tamanioMascara, bits))
            {
                cout <<"Paso "<<pasosrec <<" :" <<"desplazamiento a la izquierda de "<< bits <<"bits\n";
                pasosrec++;
                aplicarTransformacion(pixelData, 1, bits, DimensionImagen);
                encontrado = true;
            } else if (verificarDesplazamientoDer(pixelData, mascaraData, maskingData, seed, tamanioMascara, bits)) {
                cout <<"Paso "<<pasosrec <<" :" <<"desplazamiento a la derecha de "<< bits <<"bits\n";
                pasosrec++;
                aplicarTransformacion(pixelData, 2, bits, DimensionImagen);
                encontrado = true;
            }
        }

        if (!encontrado) {
            int w2 = 0, h2 = 0;
            unsigned char* pixelData_I_M = loadPixels("I_M.bmp", w2, h2);
            if (verificarXoR(pixelData, mascaraData, maskingData, seed, tamanioMascara, pixelData_I_M)) {
                cout <<"Paso "<<pasosrec <<" :" <<" XOR con I_M.bmp\n";
                pasosrec++;
                aplicarTransformacion(pixelData, 3, 0, DimensionImagen, pixelData_I_M);
                encontrado = true;
            }
            delete[] pixelData_I_M;
        }
        if (!encontrado){

            for (int bits = 1; bits <= 8 && !encontrado; ++bits) {
                if (verificarRotacionIzq(pixelData, mascaraData, maskingData, seed, tamanioMascara, bits)) {
                    cout <<"Paso "<<pasosrec <<" :" <<" rotacion a la izquierda de " << bits << " bits\n";
                    pasosrec++;
                    aplicarTransformacion(pixelData, 4, bits, DimensionImagen);
                    encontrado = true;
                }

                else if (verificarRotacionDer(pixelData, mascaraData, maskingData, seed, tamanioMascara, bits)) {
                    cout <<"Paso "<<pasosrec <<" :" <<" rotacion a la derecha de " << bits << " bits\n";
                    pasosrec++;
                    aplicarTransformacion(pixelData, 5, bits, DimensionImagen);
                    encontrado = true;
                }
            }

        }

        if (!encontrado)
            cout << "Ninguna transformacion a nivel de bits valida para " << archivoPaso.toStdString() << endl;

        delete[] maskingData;
    }

    exportImage(pixelData,width_img,height_img,"Imagen_Arreglada.bmp");

    delete[] pixelData;
    delete[] mascaraData;

    return 0;
}


QString nombreArchivoPaso(int paso) {
    return QString("M%1.txt").arg(paso);
}
