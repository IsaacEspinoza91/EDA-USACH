#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TDAlistaChar.h"
#include "TDAlistaCoordenadas.h"



/*Funcion que escribe el tablero en un archivo de texto
Entradas: TDAlistaChar2D (tablero), FILE* (archivo a escribir)*/
void escribirTableroLista2D(TDAlistaChar2D lista2D, FILE* archivo){
    nodoTDAlistaChar* auxiliar = lista2D;
    while(auxiliar != NULL){
        nodo* aux2 = auxiliar->dato;
        while(aux2 != NULL){
            fprintf(archivo," %c",aux2->dato);
            aux2 = aux2->puntero;
        }
        auxiliar = auxiliar->puntero;
        fprintf(archivo,"\n");
    }
    fprintf(archivo,"\n");
    return;
}




/*Funcion que lee el archivo de palabras y crea una lista enlazada con palabras
Entrada: nombre archivo Lista de palabras (array char), direccion de memoria de variable int que guarda 
la cantidad de palabras (puntero)
Salida: TDAlistaChar2D (lista de lista de char de las palabras)*/
TDAlistaChar2D lecturaPalabras(char* nombreArchivo, int* cantidadPalabrasPuntero){
    char varAux;
    FILE* archivoLeido = fopen(nombreArchivo, "r");
    if(archivoLeido == NULL){
        printf("Error al leer las palabras\n");
        exit(1);
    }else{
        printf("\nEl archivo %s se abrio correctamente\n",nombreArchivo);
    }

    //lectura de la primera linea del texto, cantidad de palabras
    int cantPalabras;
    fscanf(archivoLeido, "%d\n", &cantPalabras);

    TDAlistaChar2D listaPalabras = crearListaVacia2D();
    for(int i=0; i<cantPalabras; i++){
        TDAlistaChar listaActual = crearListaVacia();
        while(fscanf(archivoLeido, "%c", &varAux) != EOF){
            if(varAux != '\n'){     //si el char no es un salto de linea
                insertarNodoFinal(&listaActual, varAux);
            }else{
                break;      //salimos de la iteracion cuando hay un salto de linea
            }
        }
        insertarNodoFinal2D(&listaPalabras , listaActual);
    }

    fclose(archivoLeido);
    *cantidadPalabrasPuntero = cantPalabras;
    return listaPalabras;
}




/*Funcion que lee el archivo del tablero y crea una lista enlazada con listas enlazadas con caracteres leidos
Entrada: nombre archivo Tablero (array char), direccion de memoria variable int filas del tablero,
direccion de memoria variable int columnas del tablero
Salida: TDAlistaChar2D (lista de lista de char del tablero)*/
TDAlistaChar2D lecturaTablero(char* nombreArchivo, int* filasTableroPuntero, int* columTableroPuntero){
    char varAux;
    FILE* tableroLeido = fopen(nombreArchivo, "r");
    if(nombreArchivo == NULL){
        printf("Error al leer el tablero\n");
        exit(1);
    }else{
        printf("\nEl archivo %s se abrio correctamente",nombreArchivo);
    }

    //lectura de la primera linea de texto, tamanio tablero filasxcolumnas
    int filasTablero, columTablero;
    fscanf(tableroLeido,"%d %d", &filasTablero, &columTablero);
    *filasTableroPuntero = filasTablero;        //guardamos los datos de fila y columna en las variables ingresadas como parametro
    *columTableroPuntero = columTablero;

    TDAlistaChar2D tablero = crearListaVacia2D();
    for(int i=0; i<filasTablero; i++){
        TDAlistaChar listaActual = crearListaVacia();
        for(int j=0; j<columTablero; j++){
            fscanf(tableroLeido, " %c", &varAux);
            insertarNodoFinal(&listaActual, varAux);
        }
        insertarNodoFinal2D(&tablero, listaActual);
    }

    fclose(tableroLeido);
    return tablero;
}




/*Funcion que busca palabras dentro del tablero y entrega un booleano con su resultado
Entrada: TDAlistaChar2D del tablero, TDAlistaChar palabra a buscar, int fila tablero,
int columna tablero, TDAlistaCoordenada lista de coordenadas, FILE* flujo del archivo a escribir tablero.out
Salida: bool true (palabra encontrada), false (palabra no encontrada)*/
bool buscarPalabras(TDAlistaChar2D tablero, TDAlistaChar palabra, int mFila, int nColumna, TDAlistaCoordenadas* listCoordenadas , FILE* archivo){

    bool palabraEncontrada;
    int largoPalabra = cantidadNodosLista(palabra);
    int fila = 0, columna = 0, numAux = 0;

    //BUSQUEDA PALABRA DERECHA
    nodo* auxPalabra;
    nodoTDAlistaChar* auxiliar = tablero;
    while(auxiliar != NULL){
        nodo* aux2 = auxiliar->dato;
        columna = 0;
        while(aux2 != NULL){
            
            //CONDICIONES DE COINCIDENCIA 1ERA LETRA
            if(aux2->dato == palabra->dato){




                //BUSQUEDA IZQ a DERECHA ->
                auxPalabra = palabra;
                if((columna+largoPalabra-1) < nColumna){

                    nodo* auxTablero1D = aux2;   //en este caso es 1d porque es horizontal
                    palabraEncontrada = true;
                    while(auxPalabra != NULL){
                        if(auxTablero1D->dato != auxPalabra->dato){
                            palabraEncontrada = false;
                            break;
                        }
                        auxTablero1D = auxTablero1D->puntero;
                        auxPalabra = auxPalabra->puntero;
                    }
                    
                    if(palabraEncontrada == true){ 
                        //si la palabra no se encuentra, se busca en otras direcciones
                        insertarNodoFinalListaCoordenadas(listCoordenadas, fila+1, columna+1);

                        //proceso de escribir ***** y cambiar coordenadas
                        auxTablero1D = aux2;
                        auxPalabra = palabra;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero1D, numAux ,'*');
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        escribirTableroLista2D(tablero, archivo);       //printeamos el tablero en el .out

                        auxPalabra = palabra;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero1D, numAux ,auxPalabra->dato);
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        return palabraEncontrada;
                    }
                }




                //BUSQUEDA ARRIBA HACIA ABAJO ↓
                auxPalabra = palabra;
                if((fila+largoPalabra-1) < mFila){

                    nodoTDAlistaChar* auxTablero2D = auxiliar;
                    palabraEncontrada = true;
                    while(auxPalabra != NULL){
                        if(obtenerNodo(auxTablero2D->dato,columna)->dato != auxPalabra->dato){
                            palabraEncontrada = false;
                            break;
                        }
                        auxTablero2D = auxTablero2D->puntero;
                        auxPalabra = auxPalabra->puntero;
                    }

                    if(palabraEncontrada ==true){
                        //palabra vertical encontrada
                        insertarNodoFinalListaCoordenadas(listCoordenadas, fila+1, columna+1);

                        //proceso de escribir ***** y cambiar coordenadas
                        auxTablero2D = auxiliar;
                        auxPalabra = palabra;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna ,'*');
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        escribirTableroLista2D(tablero, archivo);

                        auxTablero2D = auxiliar;
                        auxPalabra = palabra;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna,auxPalabra->dato);
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        return palabraEncontrada;
                    }
                }




                //BUSQUEDA DIAGONAL ABAJO/IZQ ↙
                auxPalabra = palabra;
                if( ((fila+largoPalabra-1) < mFila) && ((columna-largoPalabra+1) >= 0) ){

                    numAux = 0;
                    nodoTDAlistaChar* auxTablero2D = auxiliar;
                    palabraEncontrada = true;
                    while(auxPalabra != NULL){
                        if(obtenerNodo(auxTablero2D->dato,columna - numAux)->dato != auxPalabra->dato){
                            palabraEncontrada = false;
                            break;
                        }
                        numAux ++;
                        auxTablero2D = auxTablero2D->puntero;
                        auxPalabra = auxPalabra->puntero;
                    }

                    if(palabraEncontrada ==true){
                        //palabra ↙ encontrada
                        insertarNodoFinalListaCoordenadas(listCoordenadas, fila+1, columna+1);

                        //proceso de escribir ***** y cambiar coordenadas
                        auxTablero2D = auxiliar;
                        auxPalabra = palabra;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna - numAux,'*');
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        escribirTableroLista2D(tablero, archivo);

                        auxTablero2D = auxiliar;
                        auxPalabra = palabra;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna - numAux, auxPalabra->dato);
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        return palabraEncontrada;
                    }
                }




                //BUSQUEDA DIAGONAL ABAJO/DERE ↘
                auxPalabra = palabra;
                if( ((fila+largoPalabra-1) < mFila) && ((columna+largoPalabra-1) < nColumna)){

                    numAux = 0;
                    nodoTDAlistaChar* auxTablero2D = auxiliar;
                    palabraEncontrada = true;
                    while(auxPalabra != NULL){
                        if(obtenerNodo(auxTablero2D->dato,columna + numAux)->dato != auxPalabra->dato){
                            palabraEncontrada = false;
                            break;
                        }
                        numAux ++;
                        auxTablero2D = auxTablero2D->puntero;
                        auxPalabra = auxPalabra->puntero;
                    }

                    if(palabraEncontrada ==true){
                        //palabra ↘ encontrada
                        insertarNodoFinalListaCoordenadas(listCoordenadas, fila+1, columna+1);

                        //proceso de escribir ***** y cambiar coordenadas
                        auxTablero2D = auxiliar;
                        auxPalabra = palabra;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna + numAux,'*');
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        escribirTableroLista2D(tablero, archivo);

                        auxTablero2D = auxiliar;
                        auxPalabra = palabra;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna + numAux, auxPalabra->dato);
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        return palabraEncontrada;
                    }
                }
            }
            columna ++;
            aux2 = aux2->puntero;
        }
        fila ++;
        auxiliar = auxiliar->puntero;
    }










    //BUSQUEDA PALABRA REVES
    fila = 0;
    columna = 0;
    TDAlistaChar palabraReves = listaInversa(palabra);

    //nodo* auxPalabra;
    auxiliar = tablero;
    while(auxiliar != NULL){
        nodo* aux2 = auxiliar->dato;
        columna = 0;
        while(aux2 != NULL){
            
            //CONDICIONES DE COINCIDENCIA 1ERA LETRA
            if(aux2->dato == palabraReves->dato){




                //BUSQUEDA IZQ a DERECHA ->
                auxPalabra = palabraReves;
                if((columna+largoPalabra-1) < nColumna){

                    nodo* auxTablero1D = aux2;   //en este caso es 1d porque es horizontal
                    palabraEncontrada = true;
                    while(auxPalabra != NULL){
                        if(auxTablero1D->dato != auxPalabra->dato){
                            palabraEncontrada = false;
                            break;
                        }
                        auxTablero1D = auxTablero1D->puntero;
                        auxPalabra = auxPalabra->puntero;
                    }
                    
                    if(palabraEncontrada == true){      //solo en el caso de que si se encuentra la palabra, se retorno,
                        //palabra encontrada -> reves
                        insertarNodoFinalListaCoordenadas(listCoordenadas, fila+1, columna+largoPalabra);

                        //proceso de escribir ***** y cambiar coordenadas
                        auxTablero1D = aux2;
                        auxPalabra = palabraReves;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero1D, numAux ,'*');
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        escribirTableroLista2D(tablero, archivo);

                        auxPalabra = palabraReves;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero1D, numAux ,auxPalabra->dato);
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        return palabraEncontrada;
                    }
                }




                //BUSQUEDA ARRIBA HACIA ABAJO ↓
                auxPalabra = palabraReves;
                if((fila+largoPalabra-1) < mFila){

                    nodoTDAlistaChar* auxTablero2D = auxiliar;
                    palabraEncontrada = true;
                    while(auxPalabra != NULL){
                        if(obtenerNodo(auxTablero2D->dato,columna)->dato != auxPalabra->dato){
                            palabraEncontrada = false;
                            break;
                        }
                        auxTablero2D = auxTablero2D->puntero;
                        auxPalabra = auxPalabra->puntero;
                    }

                    if(palabraEncontrada ==true){
                        //palabra vertical reves encontrada
                        insertarNodoFinalListaCoordenadas(listCoordenadas, fila+largoPalabra, columna+1);

                        //proceso de escribir ***** y cambiar coordenadas
                        auxTablero2D = auxiliar;
                        auxPalabra = palabraReves;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna ,'*');
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        //recorrerLista2D(tablero);
                        escribirTableroLista2D(tablero, archivo);

                        auxTablero2D = auxiliar;
                        auxPalabra = palabraReves;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna,auxPalabra->dato);
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        return palabraEncontrada;
                    }
                }
                



                //BUSQUEDA DIAGONAL ABAJO/IZQ ↙
                auxPalabra = palabraReves;
                if( ((fila+largoPalabra-1) < mFila) && ((columna-largoPalabra+1) >= 0) ){

                    numAux = 0;
                    nodoTDAlistaChar* auxTablero2D = auxiliar;
                    palabraEncontrada = true;
                    while(auxPalabra != NULL){
                        if(obtenerNodo(auxTablero2D->dato,columna - numAux)->dato != auxPalabra->dato){
                            palabraEncontrada = false;
                            break;
                        }
                        numAux ++;
                        auxTablero2D = auxTablero2D->puntero;
                        auxPalabra = auxPalabra->puntero;
                    }

                    if(palabraEncontrada ==true){
                        //palabra ↙ reves encontrada
                        insertarNodoFinalListaCoordenadas(listCoordenadas, fila+largoPalabra, columna-largoPalabra+2);

                        //proceso de escribir ***** y cambiar coordenadas
                        auxTablero2D = auxiliar;
                        auxPalabra = palabraReves;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna - numAux,'*');
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        escribirTableroLista2D(tablero, archivo);

                        auxTablero2D = auxiliar;
                        auxPalabra = palabraReves;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna - numAux, auxPalabra->dato);
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        return palabraEncontrada;
                    }
                }




                //BUSQUEDA DIAGONAL ABAJO/DERE ↘
                auxPalabra = palabraReves;
                if( ((fila+largoPalabra-1) < mFila) && ((columna+largoPalabra-1) < nColumna)){

                    numAux = 0;
                    nodoTDAlistaChar* auxTablero2D = auxiliar;
                    palabraEncontrada = true;
                    while(auxPalabra != NULL){
                        if(obtenerNodo(auxTablero2D->dato,columna + numAux)->dato != auxPalabra->dato){
                            palabraEncontrada = false;
                            break;
                        }
                        numAux ++;
                        auxTablero2D = auxTablero2D->puntero;
                        auxPalabra = auxPalabra->puntero;
                    }

                    if(palabraEncontrada ==true){
                        //palabra ↘ reves encontrada
                        insertarNodoFinalListaCoordenadas(listCoordenadas, fila+largoPalabra, columna+largoPalabra);

                        //proceso de escribir ***** y cambiar coordenadas
                        auxTablero2D = auxiliar;
                        auxPalabra = palabraReves;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna + numAux,'*');
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        escribirTableroLista2D(tablero, archivo);

                        auxTablero2D = auxiliar;
                        auxPalabra = palabraReves;
                        numAux = 0;
                        while(auxPalabra != NULL){
                            reemplazarElementosListaChar(&auxTablero2D->dato, columna + numAux, auxPalabra->dato);
                            auxTablero2D = auxTablero2D->puntero;
                            auxPalabra = auxPalabra->puntero;
                            numAux ++;
                        }

                        return palabraEncontrada;
                    }
                }
            }
            columna ++;
            aux2 = aux2->puntero;
        }
        fila ++;
        auxiliar = auxiliar->puntero;
    }

    //las coordenadas son -1, =1 cuando no se encuentra la palabra
    insertarNodoFinalListaCoordenadas(listCoordenadas, -1, -1);
    return palabraEncontrada;

}




    //NOT YETTTTTTTTTTTTTTTT OJOOO PREGUNTAR A LA PROFE
/*Funcion que reemplaza la extension de formato del nombre de un archivo, 
ejemplo podria reemplazar hola.jpg por hola.png
Entrada: nombre archivo con extension de 3 letras (array de char, char*),
extension a cambiar (array de char, char*)
Salida: array de char con la extension nueva (char*)*/
char* cambiarExtension3char(char* nombreArchivo, char* extension){
    int largoNombre = strlen(nombreArchivo);
    for(int n=1; n<=3; n++){
        nombreArchivo[largoNombre-n] = extension[3-n];
    }
    return nombreArchivo;
}




void main(){

    char* nombreLista = (char*)malloc(sizeof(char)*12);//limite de 12 letras en el nombre a buscar
    char* nombreTablero = (char*)malloc(sizeof(char)*12);
    int cantPalabrasLista, filasM, columnasN, contPalabrasEncontradas=0;
    bool palabraEncontrada, palabraInvertidaEncontrada, resultadoBusqueda;

    printf("\nIngresar el nombre del archivo lista (con su extension .lst): ");
    scanf("%s",nombreLista);
    printf("Ingresar el nombre del archivo tablero (con su extension .ini): ");
    scanf("%s",nombreTablero);

    TDAlistaChar2D tablero = lecturaTablero(nombreTablero, &filasM, &columnasN);
    TDAlistaChar2D listaPalabras = lecturaPalabras(nombreLista, &cantPalabrasLista);
    TDAlistaCoordenadas listaCoordenadas = crearListaCoordenadasVacia();




    /* ------- Proceso cambiar nombre y creacion de archivos de salida ---------*/
    cambiarExtension3char(nombreLista, "out");
    cambiarExtension3char(nombreTablero, "out");
    FILE* salidaListaPalabra = fopen(nombreLista, "w");
    if(salidaListaPalabra == NULL){
        printf("\nNo se pudo crear el archivo");
        return;
    }else{
        printf("\nSe creo correctamente el archivo %s",nombreLista);
    }

    FILE* salidaTablero = fopen(nombreTablero, "w");
    if(salidaTablero == NULL){
        printf("\nNo se pudo crear el archivo");
        return;
    }else{
        printf("\nSe creo correctamente el archivo %s\n",nombreTablero);
    }




    /* ------- Proceso de busqueda de palabras ------------------------------*/
    nodoTDAlistaChar* auxBusqList = listaPalabras;
    for(int a=0; a<cantPalabrasLista; a++){
        resultadoBusqueda = buscarPalabras(tablero, auxBusqList->dato,filasM, columnasN, &listaCoordenadas, salidaTablero);
        auxBusqList = auxBusqList->puntero;
    }




    //Escribimos la cantidad de palabras en el archivo lista.out
    nodoCoordenadasPalabra* auxContCoordenadas = listaCoordenadas;
    for(int r=0; r<cantPalabrasLista; r++){
        if(auxContCoordenadas->fila != -1){   //condicion para contar palabras encontrada
            contPalabrasEncontradas ++;
        }
        auxContCoordenadas = auxContCoordenadas->puntero;
    }
    fprintf(salidaListaPalabra, "%d\n",contPalabrasEncontradas);




    /* ------ Proceso imprimir palabras y datos en lista.out -----------------------------*/
    auxContCoordenadas = listaCoordenadas;
    nodoTDAlistaChar* auxListaPalabrasEncontradas = listaPalabras;
    for(int r=0; r<cantPalabrasLista; r++){
        nodo* auxPalabraActual = auxListaPalabrasEncontradas->dato;
        if(auxContCoordenadas->fila != -1){
            //imprimir datos palabras en el texto de salida lista.out
            fprintf(salidaListaPalabra, "%d %d (", auxContCoordenadas->fila, auxContCoordenadas->colum);
            while((auxPalabraActual) != NULL){
                fprintf(salidaListaPalabra, "%c", auxPalabraActual->dato);
                auxPalabraActual = auxPalabraActual->puntero;
            }
            fprintf(salidaListaPalabra, ")\n");
        }
        auxContCoordenadas = auxContCoordenadas->puntero;
        auxListaPalabrasEncontradas = auxListaPalabrasEncontradas->puntero; //cambiamos de palabra
    }




    /* ------- Proceso imprimir en pantalla datos palabras encontradas y buscadas ----------*/
    printf("\nPalabras buscadas: %d\nPalabras encontradas: %d\n",cantPalabrasLista, contPalabrasEncontradas);
    fclose(salidaListaPalabra);
    fclose(salidaTablero);




    /* ------ Proceso liberar memoria ------------------------------------------------------*/
    nodoTDAlistaChar* auxLibePalabras = listaPalabras;
    for(int t=0; t<cantPalabrasLista; t++){
        liberarLista(&auxLibePalabras->dato);
        auxLibePalabras = auxLibePalabras->puntero;
        free(listaPalabras->puntero);
    }
    free(auxLibePalabras);
    free(listaPalabras);

    nodoTDAlistaChar* auxLibeTablero = tablero;
    for(int y=0; y<filasM; y++){
        liberarLista(&auxLibeTablero->dato);
        auxLibeTablero = auxLibeTablero->puntero;
        free(tablero->puntero);
    }
    free(auxLibeTablero);
    free(tablero);
    liberarListaCoordenadas(&listaCoordenadas);
}