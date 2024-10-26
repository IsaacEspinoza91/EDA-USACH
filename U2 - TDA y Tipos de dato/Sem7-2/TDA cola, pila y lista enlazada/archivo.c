#include <stdio.h>
#include <stdlib.h>
#include "TDAcolaInt.h"






void main(){


    printf("hola mundo\n\n");

    TDAcola* miCola= crearColaVacia(6);

    printf("tengo mi cola\n");

    encolar(miCola, 1);
    encolar(miCola, 2);
    encolar(miCola, 5);
    recoCola(miCola);

    printf("ahora descolamos no sea\n");
    descolar(miCola);
    recoCola(miCola);

    printf("\n");

    descolar(miCola);
    recoCola(miCola);

    encolar(miCola, 99);
    printf("ahora los datos vamos a agregar un 99 que va a estar en el final\n el dato frente es        %d     y final es      %d", frente(miCola), final(miCola));


}