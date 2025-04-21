
#include <QCoreApplication>
#include <QImage>
#include <QDebug>
#include <iostream>
#include "funciones_imagen.h"

using namespace std;

short int Dezplazamiento_bits_izq(short int numero,short unsigned int bit);
short int Dezplazamiento_bits_der(short int numero,short unsigned int bit);

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

   // for (int i = 0; i < width * height * 3; i += 3) {
   //     cout << pixelData[i] - '0' <<" ";     // Canal rojo
   //     cout << pixelData[i + 1] - '0' <<" "; // Canal verde
   //     cout << pixelData[i + 2] - '0' <<endl; // Canal azul
   // }
   // for (int i = 0; i < 4; i ++) {
   //     cout << "" <<endl;
   // }

    // Variables para almacenar la semilla y el número de píxeles leídos del archivo de enmascaramiento
    int seed = 0;
    int n_pixels = 0;

    // Carga de los datos de enmascaramiento de un archivo .txt (semilla + valores RGB)
    unsigned int *maskingData = loadSeedMasking("M2.txt", seed, n_pixels);


    cout << endl<<"Numeros en el txt "<<endl;
    for(int i= 0;i<n_pixels;i+=3){
         cout << maskingData[ i]  <<" ";     // Canal rojo
         cout << maskingData[ i + 1]  <<" "; // Canal verde
         cout << maskingData[ i + 2]  <<endl; // Canal azul
    }



    unsigned int seed_temp = seed;

    cout << "Dezplazamiento a la izquierda de  bits"<<endl;
    for(unsigned short int i= 1;i<9;i++)
    {
        cout << "mov de "<< i <<" bits"<<endl;
        for(unsigned short int m= 0;m<n_pixels;m+=3)
        {
        short int val = pixelData[seed_temp+m ] - '0';
        cout << Dezplazamiento_bits_izq(val,i) <<" ";
        short int val2 = pixelData[seed_temp+m+1 ] - '0';
        cout << Dezplazamiento_bits_izq(val2,i) <<" ";
        short int val3 = pixelData[seed_temp+m+2 ] - '0';
        cout << Dezplazamiento_bits_izq(val3,i) <<endl;




        seed_temp = seed_temp + 3;
        }
        seed_temp = seed;
    }

    cout<<endl << "Dezplazamiento a la derecha de  bits"<<endl;
    for(unsigned short int i= 1;i<9;i++)
    {
        cout << "mov de "<< i <<" bits"<<endl;
        for(unsigned short int m= 0;m<n_pixels;m+=3)
        {
            short int val = pixelData[seed_temp+m ] - '0';
            cout << Dezplazamiento_bits_der(val,i) <<" ";
            short int val2 = pixelData[seed_temp+m+1 ] - '0';
            cout << Dezplazamiento_bits_der(val2,i) <<" ";
            short int val3 = pixelData[seed_temp+m+2 ] - '0';
            cout << Dezplazamiento_bits_der(val3,i) <<endl;


            seed_temp = seed_temp + 3;
        }
        seed_temp = seed;
    }


    // Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
    //for (int i = 0; i < n_pixels * 3; i += 3) {
    //    cout << "Pixel " << i / 3 << ": ("
    //         << maskingData[i] << ", "
    //         << maskingData[i + 1] << ", "
    //         << maskingData[i + 2] << ")" << endl;
    //}

    // Libera la memoria usada para los datos de enmascaramiento
    if (maskingData != nullptr){
        delete[] maskingData;
        maskingData = nullptr;
    }

    // Libera la memoria usada para los píxeles de la imagen
    delete[] pixelData;
    pixelData = nullptr;

    int height2 = 0;
    int width2 = 0;



    // Extraccion de pixeles de la mascara para usarse en el enmascaramiento

    QString archivoEntrada2 = "M.bmp";

    unsigned char *pixelmascara = loadPixels(archivoEntrada2, width2, height2);
    cout<<endl << "el tamano de la imagen es: "<<height2<<"x"<<width2<<endl;

    for (int i = 0; i < width2 * height2 * 3; i += 3) {
             cout << pixelmascara[i] - '0' <<" ";     // Canal rojo
             cout << pixelmascara[i + 1] - '0' <<" "; // Canal verde
             cout << pixelmascara[i + 2] - '0' <<endl; // Canal azul
         }

    delete[] pixelmascara;
    pixelmascara = nullptr;

    return 0; // Fin del programa
}


short int Dezplazamiento_bits_izq(short int numero,short unsigned int bit){

   short int transformado = numero >> bit;

    return transformado;
}

short int Dezplazamiento_bits_der(short int numero,short unsigned int bit){

    short int transformado  = numero << bit;

    return transformado;
}


