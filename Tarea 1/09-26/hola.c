#include <stdio.h>
#include <stdlib.h>

/*Funcion que lee el archivo
Entrada: nombre del archivo (direccion de memoria char*), direccion de memoria de variable int que guarda la cantidad de palabras 
Salida: array de array de char (nombres leidos)*/
char** LecturaPalabras(char* nombreArchivo, int* cantidadPalabrasPuntero){

    char caracterLeido;


    FILE* archivoLeido = fopen(nombreArchivo, "r");
    if(archivoLeido == NULL){
        printf("Error al leer el archivo\n");
        exit(1);
    }

    int cantPalabras;       //lectura de la primera linea del texto, cantidad de palabras
    fscanf(archivoLeido, "%d", &cantPalabras);

    char** arrayPalabras = (char**)malloc(sizeof(char)*cantPalabras);         //array dinamico

    for(int i=0;i<cantPalabras;i++){    //iteracion que recorre las n palabras
        

        char palabraActual[18];
        while(!feof(archivoLeido)){        //mientras no estemos en el final del archivo, ejecuta
            fgets(palabraActual, 18,archivoLeido);
            printf("%s-",palabraActual);
        }

        arrayPalabras[i] = palabraActual;
        //fgets(arrayPalabras[i], 20,archivoLeido);
    
        /*
        while(caracterLeido != EOF){
            caracterLeido = fgetc(archivoLeido);
            printf("%c",caracterLeido)
        }
        fscanf(archivoLeido, "%c", &arrayPalabras[i]);
        */
    }

    fclose(archivoLeido);
    *cantidadPalabrasPuntero = cantPalabras;
    
    return arrayPalabras;
}





void main(){
    char nombre[20];
    int largoArray, numBuscar, resultBusqueda;
    printf("Por favor ingrese el nombre del archivo para generar el array: ");
    scanf("%s",nombre);

    char** arrayleido = LecturaPalabras(nombre,&largoArray);

    printf("El array leido es:\n");
    for(int i = 0; i < largoArray; i++){
        printf("%s", arrayleido[i]);

        printf("\n\n");
    }
    printf("\n");

    printf("la cantida de palabras es  %d",largoArray);

}