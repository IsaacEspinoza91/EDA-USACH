#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct pixel{
	int coordenadaX;
    int coordenadaY;
    int color;
}TDA_pixel;


/*Funcion que crea un pixel con coodenadas X, coordenadas Y, y su color
Entrada: int x, int y, int color
Salida: pixel con los datos ingresados TDA_pixel*/
TDA_pixel crearPixel(int coordX, int coordY, int color){
    TDA_pixel pixelCreado;
    pixelCreado.coordenadaX = coordX;
    pixelCreado.coordenadaY = coordY;
    pixelCreado.color = color;
    return pixelCreado;
}

/*Funcion que cambia el color de un pixel ingresado
Entrada: pixel TDA_pixel por referencia, int del nuevo color
Salida: sin salida*/
void cambiarPixel(TDA_pixel *pixelColorViejo, int nuevoColor){
    pixelColorViejo->color = nuevoColor;
    return;
}

/*Funcion que translada horizontalmente la cordenada X de un pixel
Entrada: pixel TDA_pixel por referencia, int de la posicion a desplazar
Salida: sin salida*/
void trasladorHorizontalmentePixel(TDA_pixel *pixel, int desplazamientoEnX){
    pixel->coordenadaX += desplazamientoEnX;
    return;
}

/*Funcion que muestra en pantalla un pixel
Entrada: pixel TDA_pixel
Salida: sin salida*/
void visualizarPixel(TDA_pixel pixel){
    printf("\nDatos del pixel:\n  Coordenada X = %d\n  Coordenada Y = %d\n  Color = %d\n", pixel.coordenadaX, pixel.coordenadaY, pixel.color);
    return;
}



void funcion1(int x){
    x = x + 1;
}

void funcion2(int *x){
    *x = *x + 1;
}

void main(){


    //ACTIVIDAD 1
    //creamos el pixel
    TDA_pixel miPixel = crearPixel(543,40,999);

    //cambiamos color pixel
    cambiarPixel(&miPixel, 432);

    //Trasladamos horizontalmente el pixel
    trasladorHorizontalmentePixel(&miPixel, 100);

    //mostramos en pantalla los datos del pixel
    visualizarPixel(miPixel);




    //ACTIVIDAD 2
    //definimos las variales
    int A = 5, B = 2, resultadoMultiplicacion;
    //inicializamos los punteros
    int* numA;
    int* numB;
    
    numA = &A;
    numB = &B;

    resultadoMultiplicacion = (*numA)*(*numB);
    printf("\nEl resultado de la multiplicacione es: %d",resultadoMultiplicacion);




    //ACTIVIDAD 3
    int a=5;
    funcion1(a);    //funciona correctamente porque "a" es entero, pero "a" no cambia porque no se retorna hacia esta variable, "x" si cambia y aumenta
    //funcion1(&a);
    //funcion1(*a);

    //funcion2(a);
    funcion2(&a);   //funciona correctamente porque se le entrega una direccion de memoria a la funcion, y esta trabaja con los valores apuntados por ella
    //funcion2(*a);


}