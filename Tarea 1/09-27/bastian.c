#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 50 // Longitud máxima de una palabra
#define MAX_BOARD_SIZE 100 // Tamaño máximo del tablero

typedef struct {
    int fila;
    int columna;
} Coordenada;

void buscarPalabraEnTablero(char tablero[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int filas, int columnas, char palabra[MAX_WORD_LENGTH], Coordenada *coordenadas) {
    int longitud = strlen(palabra);

    // Buscar la palabra de izquierda a derecha y de arriba hacia abajo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            // Intentar encontrar la palabra hacia la derecha
            if (j + longitud <= columnas) {
                int encontrado = 1;
                for (int k = 0; k < longitud; k++) {
                    if (tablero[i][j + k] != palabra[k]) {
                        encontrado = 0;
                        break;
                    }
                }
                if (encontrado) {
                    /*
                    // Marcar la palabra encontrada en el tablero con '*'
                    for (int k = 0; k < longitud; k++) {
                        tablero[i][j + k] = '*';
                    }*/
                    // Almacenar las coordenadas de la primera ocurrencia
                    coordenadas->fila = i + 1;
                    coordenadas->columna = j + 1;
                    return;
                }
            }



            // Intentar encontrar la palabra hacia abajo
            if (i + longitud <= filas) {
                int encontrado = 1;
                for (int k = 0; k < longitud; k++) {
                    if (tablero[i + k][j] != palabra[k]) {
                        encontrado = 0;
                        break;
                    }
                }
                if (encontrado) {
                    /*
                    // Marcar la palabra encontrada en el tablero con '*'
                    for (int k = 0; k < longitud; k++) {
                        tablero[i + k][j] = '*';
                    }
                    */
                    // Almacenar las coordenadas de la primera ocurrencia
                    coordenadas->fila = i + 1;
                    coordenadas->columna = j + 1;
                    return;
                }
            }
        }
    }

    // Buscar la palabra al revés
    char palabraReversa[MAX_WORD_LENGTH];
    for (int i = 0; i < longitud; i++) {
        palabraReversa[i] = palabra[longitud - i - 1];
    }
    palabraReversa[longitud] = '\0';

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            // Intentar encontrar la palabra al revés hacia la derecha
            if (j + longitud <= columnas) {
                int encontrado = 1;
                for (int k = 0; k < longitud; k++) {
                    if (tablero[i][j + k] != palabraReversa[k]) {
                        encontrado = 0;
                        break;
                    }
                }
                if (encontrado) {
                    /*
                    // Marcar la palabra encontrada en el tablero con '*'
                    for (int k = 0; k < longitud; k++) {
                        tablero[i][j + k] = '*';
                    }*/
                    // Almacenar las coordenadas de la primera ocurrencia
                    coordenadas->fila = i + 1;
                    coordenadas->columna = j + 1;
                    return;
                }
            }

            // Intentar encontrar la palabra al revés hacia abajo
            if (i + longitud <= filas) {
                int encontrado = 1;
                for (int k = 0; k < longitud; k++) {
                    if (tablero[i + k][j] != palabraReversa[k]) {
                        encontrado = 0;
                        break;
                    }
                }
                if (encontrado) {
                    /*
                    // Marcar la palabra encontrada en el tablero con '*'
                    for (int k = 0; k < longitud; k++) {
                        tablero[i + k][j] = '*';
                    }*/
                    // Almacenar las coordenadas de la primera ocurrencia
                    coordenadas->fila = i + 1;
                    coordenadas->columna = j + 1;
                    return;
                }
            }
        }
    }
}

void imprimirTableroEnArchivo(FILE *archivo, char tablero[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fprintf(archivo, "%c ", tablero[i][j]);
        }
        fprintf(archivo, "\n");
    }
    fprintf(archivo, "\n");
}

int main() {
    char nombreArchivo[100]; // Nombre del archivo .ini
    int k; // Número de palabras a buscar
    FILE *archivo;
    int filas, columnas;

    printf("Ingrese el nombre del archivo .ini: ");
    scanf("%s", nombreArchivo);

    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s.\n", nombreArchivo);
        return 1;
    }

    // Leer filas y columnas desde el archivo
    fscanf(archivo, "%d %d", &filas, &columnas);

    // Declarar una matriz para almacenar el tablero de letras
    char tablero[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

    // Leer el tablero de letras desde el archivo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fscanf(archivo, " %c", &tablero[i][j]); // Usamos " %c" para omitir espacios en blanco
        }
    }

    // Cerrar el archivo
    fclose(archivo);

    printf("Ingrese el nombre del archivo .lst: ");
    char nombreArchivo2[100]; // Nombre del archivo .lst
    scanf("%s", nombreArchivo2);

    // Abrir el archivo en modo lectura
    FILE *archivo2 = fopen(nombreArchivo2, "r");

    printf("\n\n\n\n");
    if (archivo2 == NULL) {
        printf("No se pudo abrir el archivo %s.\n", nombreArchivo2);
        return 1;
    }

    // Leer el número k de palabras a buscar
    fscanf(archivo2, "%d", &k);

    // Leer y procesar las k palabras
    char palabras[k][MAX_WORD_LENGTH];
    Coordenada coordenadas[k]; // Arreglo para almacenar las coordenadas de la primera ocurrencia de cada palabra

    for (int i = 0; i < k; i++) {
        fscanf(archivo2, "%s", palabras[i]);
    }

    // Cerrar el archivo
    fclose(archivo2);

    // Crear un archivo de salida .out con el mismo nombre que el archivo .ini
    char nombreSalida[100];
    strcpy(nombreSalida, nombreArchivo);
    strcat(nombreSalida, ".out");

    // Abrir el archivo de salida
    FILE *archivoSalida = fopen(nombreSalida, "w");

    if (archivoSalida == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        return 1;
    }

    // Buscar y marcar las palabras en el tablero y escribir los tableros en el archivo de salida
    for (int i = 0; i < k; i++) {
        buscarPalabraEnTablero(tablero, filas, columnas, palabras[i], &coordenadas[i]);
        printf("Palabra encontrada: %s (fila: %d, columna: %d)\n", palabras[i], coordenadas[i].fila, coordenadas[i].columna);
        imprimirTableroEnArchivo(archivoSalida, tablero, filas, columnas);
    }

    // Cerrar el archivo de salida
    fclose(archivoSalida);

    // Abrir el archivo de salida para lista1.lst.out
    FILE *archivoSalidaLista = fopen("lista1.lst.out", "w");

    if (archivoSalidaLista == NULL) {
        printf("No se pudo crear el archivo de salida para lista1.lst.out.\n");
        return 1;
    }

    // Escribir el número de palabras encontradas en el archivo de salida para lista1.lst.out
    fprintf(archivoSalidaLista, "%d\n", k);

    // Escribir las palabras encontradas y sus coordenadas en el archivo de salida para lista1.lst.out
    for (int i = 0; i < k; i++) {
        fprintf(archivoSalidaLista, "%s %d %d\n", palabras[i], coordenadas[i].fila, coordenadas[i].columna);
    }

    // Cerrar el archivo de salida para lista1.lst.out
    fclose(archivoSalidaLista);

    printf("Se han generado los archivos de salida \"%s\" y \"lista1.lst.out\".\n", nombreSalida);

    return 0;
}
