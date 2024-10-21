#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>     //pausas de tiempo


typedef struct producto{
    int fila;
    int columna;
    int direccion;  //1 = → , 2 = ↓ , 3 = ↙, 4 = ↘, 5 = ←, 6 = ↑, 7 = ⭧, 8 = ⭦
}datosPalab;



/*Funcion que lee el archivo de palabras
Entrada: nombre del archivo (array char), direccion de memoria de variable int que guarda 
la cantidad de palabras (puntero)
Salida: array de array de char (nombres leidos)*/
char** lecturaPalabras(char* nombreArchivo, int* cantidadPalabrasPuntero){

    char caracterLeido;

    FILE* archivoLeido = fopen(nombreArchivo, "r");
    if(archivoLeido == NULL){
        printf("Error al leer el archivo\n");
        exit(1);
    }

    int cantPalabras;       //lectura de la primera linea del texto, cantidad de palabras
    fscanf(archivoLeido, "%d", &cantPalabras);

    char** arrayPalabras = (char**)malloc(sizeof(char*)*cantPalabras);         //array dinamico de las palabras leidas
    for(int i=0; i<cantPalabras; i++){    //iteracion que recorre las n palabras   
        arrayPalabras[i] = (char*)malloc(sizeof(char)*18);      //limite de 18 letras cada palabra
        fscanf(archivoLeido,"%s",arrayPalabras[i]);
    }

    fclose(archivoLeido);
    *cantidadPalabrasPuntero = cantPalabras;
    
    return arrayPalabras;
}

/*Funcion que lee el archivo del tablero
Entrada: nombre del archivo (array char), direccion de memoria variable int filas del tablero,
direccion de memoria variable int columnas del tablero
Salida: array de array de char, matriz del tablero*/
char** lecturaTablero(char* nombreArchivo, int* filasTableroPuntero, int* columTableroPuntero){

    FILE* tableroLeido = fopen(nombreArchivo, "r");
    if(nombreArchivo == NULL){
        printf("Error al leer el tablero\n");
        exit(1);
    }

    int filasTablero, columTablero;     //lectura de la primera linea de texto, tamanio tablero filasxcolumnas
    fscanf(tableroLeido,"%d %d", &filasTablero, &columTablero);
    *filasTableroPuntero = filasTablero;        //guardamos los datos de fila y columna en las variables ingresadas como parametro
    *columTableroPuntero = columTablero;

    char** tablero = (char**)malloc(sizeof(char*)*filasTablero);        //creamos matriz del tablero
    for (int i=0; i<filasTablero; i++) {
        tablero[i] = (char*)malloc(sizeof(char)*columTablero);
        for (int j=0; j<columTablero; j++) {
            fscanf(tableroLeido, " %c", &tablero[i][j]);        //leemos los caracteres de cada linea sin el espacio entremedio
        }
    }

    fclose(tableroLeido);
    return tablero;
}

/*Funcion que busca las palabras dentro del tablero
Entrada: palabra a buscar (array de char), tablero (array de array de char, char**)
invertida y falso si no lo esta
Salida: booleano true si encuentra palabra, falso si no encuentra palabra*/
bool buscarPalabras(char* palabra, char** tablero, int filas, int columnas, datosPalab *palabraActual, bool palabraInversa){

    bool pEncontrada;
    int largoPalabra = strlen(palabra);     //la funcion srtlen obtiene el largo de la palabra ingresada, cant de char
    
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){         //con estos dos bucles anidados se recorren todos los char del tablero
            if(tablero[i][j]==palabra[0]){  //caso en que encuentra la primera letra de la palabra en el tablero


                //BUSQUEDA DERECHA A IZQ ->
                if((j+largoPalabra-1)<columnas){
                    pEncontrada = true;
                    for(int u=1; u<largoPalabra; u++){      //partimos de 1 porque ya sabemos que la primera letra si coincide
                        if(tablero[i][j+u] != palabra[u]){      //solo en el caso en que todas las demas palabras no coincidan
                            pEncontrada = false;            //se podria para la iteracion del u aqui
                            break;
                        }
                    }
                    if(pEncontrada==true){
                        sleep(1);
                        if(palabraInversa==false){
                            printf("\n\n\nla palabra encontrada esta en la posicion  %d,%d\n\n", i+1,j+1);//las coordenadas son i+1,j+1
                            palabraActual->fila = i+1;
                            palabraActual->columna = j+1;
                            palabraActual->direccion = 1; //1 significa ->
                            return true;
                        }else{
                            printf("\n\n\nla palabra encontrada esta en la posicion  %d,%d\n\n", i+1,j+largoPalabra);
                            palabraActual->fila = i+1;
                            palabraActual->columna = j+largoPalabra;
                            palabraActual->direccion = 5; //5 significa <-
                            return true;
                        }
                    }
                }



                //BUSQUEDA ARRIBA HACIA ABAJO ↓
                if((i+largoPalabra-1)<filas){
                    pEncontrada = true;
                    for(int u=1; u<largoPalabra; u++){
                        if(tablero[i+u][j] != palabra[u]){      //vamos buscando en la fila siguiente, entonces i+u
                            pEncontrada = false;
                            break;
                        }
                    }
                    if(pEncontrada==true){
                        sleep(1);
                        if(palabraInversa==false){
                            printf("\n\n\nla palabra encontrada esta en la posicion  %d,%d\n\n", i+1,j+1);
                            palabraActual->fila = i+1;
                            palabraActual->columna = j+1;
                            palabraActual->direccion = 2; //2 significa ↓
                            return true;
                        }else{
                            printf("\n\n\nla palabra encontrada esta en la posicion  %d,%d\n\n", i+largoPalabra,j+1);
                            palabraActual->fila = i+largoPalabra;
                            palabraActual->columna = j+1;
                            palabraActual->direccion = 6; //6 significa ↑
                            return true;
                        }
                    }
                }



                //BUSQUEDA DIAGONAL ABAJO/IZQ ↙
                if(((i+largoPalabra-1) < filas) && ((j-largoPalabra+1) >= 0)){
                    pEncontrada = true;
                    for(int u=1; u<largoPalabra; u++){
                        if(tablero[i+u][j-u] != palabra[u]){      //vamos buscando en la fila siguiente, entonces i+u
                            pEncontrada = false;
                            break;
                        }
                    }
                    if(pEncontrada==true){
                        sleep(1);
                        if(palabraInversa==false){
                            printf("\n\n\nla palabra encontrada esta en la posicion  %d,%d\n\n", i+1,j+1);
                            palabraActual->fila = i+1;
                            palabraActual->columna = j+1;
                            palabraActual->direccion = 3; //3 significa ↙
                            return true;
                        }else{
                            printf("\n\n\nla palabra encontrada esta en la posicion  %d,%d\n\n", i+largoPalabra,j-largoPalabra+2);
                            palabraActual->fila = i+largoPalabra;
                            palabraActual->columna = j-largoPalabra+2;
                            palabraActual->direccion = 7; //7 significa ⭧
                            return true;
                        }
                    }
                }



                //BUSQUEDA DIAGONAL ABAJO/DERE ↘
                if(((i+largoPalabra-1) < filas) && ((j+largoPalabra-1)<columnas)){
                    pEncontrada = true;
                    for(int u=1; u<largoPalabra; u++){
                        if(tablero[i+u][j+u] != palabra[u]){      //vamos buscando en la fila siguiente, entonces i+u
                            pEncontrada = false;
                            break;
                        }
                    }
                    if(pEncontrada==true){
                        sleep(1);
                        if(palabraInversa==false){
                            printf("\n\n\nla palabra encontrada esta en la posicion  %d,%d\n\n", i+1,j+1);
                            palabraActual->fila = i+1;
                            palabraActual->columna = j+1;
                            palabraActual->direccion = 4; //4 significa ↘
                            return true;
                        }else{
                            printf("\n\n\nla palabra encontrada esta en la posicion  %d,%d\n\n", i+largoPalabra,j+largoPalabra);
                            palabraActual->fila = i+largoPalabra;
                            palabraActual->columna = j+largoPalabra;
                            palabraActual->direccion = 8; //8 significa ⭦
                            return true;
                        }
                        
                    }
                }


            }
        }
    }


    palabraActual->fila = -1;
    palabraActual->columna = -1;
    palabraActual->direccion = -1;
    return false;

}



void main(){
    char nombre[20];
    int cantPalabrasArray, numBuscar, resultBusqueda, filasM, columnasN;
    bool palabraEncontrada, palabraInvertidaEncontrada;
    //printf("Por favor ingrese el nombre del archivo para generar el array: ");
    //scanf("%s",nombre);

    char** palabrasTablero = lecturaPalabras("lista1.lst",&cantPalabrasArray);

    printf("\n\n\nEl array leido es:\n");
    for(int i=0; i<cantPalabrasArray; i++){
        printf("%s\n", palabrasTablero[i]);
    }
    printf("\nla cantida de palabras es  %d\n\n",cantPalabrasArray);


    char** tablero = lecturaTablero("tablero1.ini",&filasM, &columnasN);
    printf("\nel tablero ess:\n\n");
    for (int i=0; i<filasM; i++) {
        for (int j=0; j<columnasN; j++) {
            printf(" %c",tablero[i][j]);
        }
        printf("\n");
    }



    datosPalab* datosPalabras = (datosPalab*)malloc(sizeof(datosPalab)*cantPalabrasArray);
    //datosPalab datosPalabras[cantPalabrasArray];
    //buscamos las palabras y sus posciones y las agregamos al array de datos
    
    for(int t=0; t<cantPalabrasArray; t++){
        sleep(1);
        palabraEncontrada = buscarPalabras(palabrasTablero[t], tablero, filasM, columnasN, &datosPalabras[t], false);
        
        if(palabraEncontrada==false){//en el caso que en un inicio no encontro la palabra, ahora se busca las misma palabra pero al reves
            

            strrev(palabrasTablero[t]);     //funcion que invierte el array de char
            palabraEncontrada = buscarPalabras(palabrasTablero[t], tablero, filasM, columnasN, &datosPalabras[t], true);   //con palabra invertida
            strrev(palabrasTablero[t]);      //volvemos a invertirlo para que vuelva a estar normal
            sleep(1);

        }

    }

    /*
    for(int i=3; i<cantPalabrasArray; i++){
        printf(" %d.- %s\n",i+1,palabrasTablero[i]);
        datosPalabras[i].fila=0;
        datosPalabras[i].columna=0;
        datosPalabras[i].direccion=0;

        palabraEncontrada = buscarPalabras(palabrasTablero[i], tablero, filasM, columnasN, &datosPalabras[i], false);
        
        if(palabraEncontrada==false){//en el caso que en un inicio no encontro la palabra, ahora se busca las misma palabra pero al reves
            

            strrev(palabrasTablero[i]);     //funcion que invierte el array de char
            palabraInvertidaEncontrada = buscarPalabras(palabrasTablero[i], tablero, filasM, columnasN, &datosPalabras[i], true);   //con palabra invertida
            strrev(palabrasTablero[i]);      //volvemos a invertirlo para que vuelva a estar normal
            sleep(1);

        }
        
    }*/

    //palabraEncontrada = buscarPalabras("internet", tablero, filasM, columnasN, &datosPalabras[0], true);
    

    //PROCESO IMPRIMIR LAS PALABRAS Y SUS DATOS
    for(int r=0; r<cantPalabrasArray; r++){
        printf("%d.- %s (%d,%d)\n", r+1, palabrasTablero[r], datosPalabras[r].fila, datosPalabras[r].columna);
    }


    //pRECORDAR LIBERAR MEMORIA

}