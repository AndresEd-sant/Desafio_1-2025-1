
#include <QCoreApplication>
#include <QImage>
#include <QDebug>
#include <iostream>
#include "funciones_imagen.h"

using namespace std;
int main()
{
    // Definición de rutas de archivo de entrada (imagen Dañada)
    QString archivoEntrada = "I_D.bmp";

    // Variables para almacenar las dimensiones de la imagen
    int height = 0;
    int width = 0;

    // Carga la imagen BMP en memoria dinámica y obtiene ancho y alto
    unsigned char *pixelData = loadPixels(archivoEntrada, width, height);

    cout << "el tamano de la imagen es: "<<height<<"x"<<width<<endl;

    // Muestreo de pixeles de la imagen dañada convertidos a numeros

    for (int i = 0; i < width * height * 3; i += 3) {
        cout << pixelData[i] - '0' <<" ";     // Canal rojo
        cout << pixelData[i + 1] - '0' <<" "; // Canal verde
        cout << pixelData[i + 2] - '0' <<endl; // Canal azul
    }
    for (int i = 0; i < 4; i ++) {
        cout << "" <<endl;
    }



    // Libera la memoria usada para los píxeles de la imagen
    delete[] pixelData;
    pixelData = nullptr;

    // Variables para almacenar la semilla y el número de píxeles leídos del archivo de enmascaramiento
    int seed = 0;
    int n_pixels = 0;

    // Carga de los datos de enmascaramiento de un archivo .txt (semilla + valores RGB)
    unsigned int *maskingData = loadSeedMasking("M2.txt", seed, n_pixels);

    // Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
    for (int i = 0; i < n_pixels * 3; i += 3) {
        cout << "Pixel " << i / 3 << ": ("
             << maskingData[i] << ", "
             << maskingData[i + 1] << ", "
             << maskingData[i + 2] << ")" << endl;
    }

    // Libera la memoria usada para los datos de enmascaramiento
    if (maskingData != nullptr){
        delete[] maskingData;
        maskingData = nullptr;
    }

    return 0; // Fin del programa
}

