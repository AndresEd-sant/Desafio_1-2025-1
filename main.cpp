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
QString nombreArchivoPaso(int paso);

bool verificarTransformacionIzq(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                                int seed, int size, int bits);

bool verificarTransformacionDer(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                                int seed, int size, int bits);

bool verificarXoR(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                  int seed, int size, unsigned char* pixelData2);

void aplicarTransformacion(unsigned char* pixelData,unsigned short int modo,unsigned short int bits =0,unsigned int tamanio_im = 0 );
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

        bool encontrado = false;

        for (int modo = 1; modo <= 5; ++modo) {

            // Tranformacion de Desplazamiento de 1 hasta 8 bits
            for (int bits = 1; bits <= 8; ++bits) {
                if (verificarTransformacionIzq(pixelData, mascaraData, maskingData, seed, tamanioMascara, bits)) {
                    cout << "Transformacion encontrada: desplazamiento izquierda " << bits << " bits." << endl;
                    encontrado = true;
                    break;
                }

                if (verificarTransformacionDer(pixelData, mascaraData, maskingData, seed, tamanioMascara, bits)) {
                    cout << "Transformacion encontrada: desplazamiento derecha " << bits << " bits." << endl;
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado) {
                int wi = 0, hi = 0;
                unsigned char* pixelData_I_M = loadPixels("I_M.bmp", wi, hi);

                if (verificarXoR(pixelData, mascaraData, maskingData, seed, tamanioMascara, pixelData_I_M)) {
                    cout << "Transformacion encontrada: XOR con I_M.bmp" << endl;
                    encontrado = true;
                    aplicarTransformacion()
                }

                delete[] pixelData_I_M;
            }

            //Transformacion de Rotacion a la izquierda
            if (!encontrado){
                cout<<endl<<"APlicacion de rotacion a la izquierda: "<<endl;
            }

            //Transformacion de Rotacion a la Derecha
            if (!encontrado){
                cout<<endl<<"APlicacion de rotacion a la izquierda: "<<endl;
            }

            if (encontrado) {
                delete[] maskingData;
                maskingData = nullptr;
                break;
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

uint8_t RotacionBitsIzq(uint8_t valor) {

}

uint8_t RotacionBitsDer(uint8_t valor) {

}
// ---------------------- FUNCIONES AUXILIARES ----------------------

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
        //cout <<endl<<"canal 1 : "<<valor1<<endl;
        unsigned int valor2 = IM_mascara[seed + i];
       // cout <<endl<<"canal 2 : "<<valor2<<endl;
        //cout <<endl<<"Xor entre canales : "<<Xor(valor1, valor2)<<endl;
        int x = mascara[i];
        cout <<endl<<"Mascara : "<<x<<endl;

        unsigned int enmascaramiento = Xor(valor1, valor2) + mascara[i];
       // cout <<endl<<"Enmascaramiento : "<<enmascaramiento<<endl;
        if (enmascaramiento != referencia[i]) return false;
    }
    return true;
}

bool verificarRotacionIzq(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                  int seed, int size, int argumento) {
}

bool verificarRotacionDer(unsigned char* pixelData, unsigned char* mascara, unsigned int* referencia,
                          int seed, int size, int argumento) {
}

void aplicarTransformacion(unsigned char* pixelData,unsigned short int modo,unsigned short int bits,unsigned int tamanio_im,
                           unsigned char* pixeldata2 ) {

    if (modo == 1){
        for (unsigned int i = 0; i < tamanio_im; ++i) {
            uint8_t original = pixelData[i];
            uint8_t transformado =  desplazarBitsIzq(original, bits);
            pixelData[i] = transformado;
        }

    }
    if (modo == 2){
        for (unsigned int i = 0; i < tamanio_im; ++i) {
            uint8_t original = pixelData[i];
            uint8_t transformado =  desplazarBitsDer(original, bits);
            pixelData[i] = transformado;
        }
    }
    if (modo == 3){
        for (unsigned int i = 0; i < tamanio_im; ++i) {
            unsigned int Im_original = pixelData[i];
            unsigned int Im_mascara = pixeldata2[i];
            unsigned int transformado =  Xor(Im_original,Im_mascara );
            pixelData[i] = transformado;
        }
    }
    if (modo == 4){
        for (unsigned int i = 0; i < tamanio_im; ++i) {
            uint8_t original = pixelData[i];
            uint8_t transformado =  RotacionBitsIzq(original);
            pixelData[i] = transformado;
        }
    }
    if (modo == 5){
        for (unsigned int i = 0; i < tamanio_im; ++i) {
            uint8_t original = pixelData[i];
            uint8_t transformado =  RotacionBitsDer(original);
            pixelData[i] = transformado;
        }
    }


}

void registrarTransformacion(unsigned char* transformaciones, char nombre) {
    int tamanio_tran = sizeof(transformaciones);



}

QString nombreArchivoPaso(int paso) {
    return QString("M%1.txt").arg(paso);
}
