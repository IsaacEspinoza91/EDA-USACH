#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAGrafoMA.h"
//#include <time.h>
//#include <ctype.h>


/*Funcion que lee el archivo de palabras y crea un array con palabras
Entrada: nombre archivo Lista de palabras (array char), direccion de memoria de variable int que guarda 
la cantidad de palabras (puntero)
Salida: array de array de char (nombres leidos, array de palabras)*/
char** leerPalabras(char* nombreArchivo, int* nPalabras){

    int cantidadPalabras;
    char varAux;

    FILE *archivo = fopen(nombreArchivo, "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo de palabras\n");
        return NULL;
    }else{
        printf("\nEl archivo %s se abrio correctamente\n",nombreArchivo);
    }

    fscanf(archivo, "%d", &cantidadPalabras);
    *nPalabras = cantidadPalabras;

    //creamos array de arrays
    char** arrayPalabras = (char**)malloc(sizeof(char*)*cantidadPalabras);
    for(int i=0; i<cantidadPalabras; i++){
        arrayPalabras[i] = (char*)malloc(sizeof(char)*18);  //limite de 18 letras cada palarba
        fscanf(archivo,"%s",arrayPalabras[i]);
    }
    
    fclose(archivo);
    return arrayPalabras;
}


void imprimirPalabras(char** array, int cantidadPalabras){
    for(int o=0; o<cantidadPalabras; o++){
        printf("%s",array[o]);
        printf("\n");
    }
}


/*Funcion que lee el archivo del tablero y crea un grafo no direccionado no ponderado con los caracteres leidos
Entrada: nombre archivo Tablero (array char), direccion de memoria variable int tamanio del tablero
Salida: puntero a grafo ND y NP con matriz de adyacencia(TDAGrafoMA* ). Este grafo considera a cada letra como un vertice que tiene
como aristas a todos los otros vertices cercanos a distancia 1 (adyacentes)*/
TDAGrafoMA *leerTablero(char* nombreArchivo, int* tamanioTablero) {

    int filas, columnas, indiceActual, indiceVertiAdy;
    char varAux;

    //abremos el tableroLeido del tablero
    FILE *tableroLeido = fopen(nombreArchivo, "r");
    if(tableroLeido == NULL){
        printf("Error al abrir el tableroLeido\n");
        return NULL;
    }else{
        printf("\nEl archivo %s se abrio correctamente\n",nombreArchivo);
    }

    //leer cantidad filas y columnas, luego hay  filas*filas  vertices
    fscanf(tableroLeido, "%d %d", &filas, &columnas);
    *tamanioTablero = filas;    //guardamos los datos de fila (tablero cuadrado) variables ingresadas como parametro

    //creamos grafo vacio 
    TDAGrafoMA *G = crearGrafoVacioMA(filas*filas);

    //recorro el tablero guardando los vertices en el array de vertices y creando la matriz de adyacencia
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            indiceActual = i * columnas + j; //indice actual dentro del array de vertices != al de matriz
            fscanf(tableroLeido, " %c", &varAux);                //guardar la letra de cada vertice en el array de vertices
            G->V[indiceActual] = varAux;

            
            //agregar hori adya derecha
            if(j < columnas - 1){
                indiceVertiAdy = i * columnas + (j + 1); //indice vertice lado derecho en el array de vertices
                agregar_aristaMA_NP(G, indiceActual, indiceVertiAdy);
                agregar_aristaMA_NP(G, indiceVertiAdy, indiceActual);
            }
            //agregar vertical adya abajo
            if(i < filas - 1){
                indiceVertiAdy = (i + 1) * columnas + j;
                agregar_aristaMA_NP(G, indiceActual, indiceVertiAdy);
                agregar_aristaMA_NP(G, indiceVertiAdy, indiceActual);
            }
            //agregar diagonal 1 \esta
            if(i < filas - 1 && j < columnas - 1){
                indiceVertiAdy = (i + 1) * columnas + (j + 1);
                agregar_aristaMA_NP(G, indiceActual, indiceVertiAdy);
                agregar_aristaMA_NP(G, indiceVertiAdy, indiceActual);
            }
            //agregar diagonal 2 /esta
            if(i < filas - 1 && j > 0){
                indiceVertiAdy = (i + 1) * columnas + (j - 1);
                agregar_aristaMA_NP(G, indiceActual, indiceVertiAdy);
                agregar_aristaMA_NP(G, indiceVertiAdy, indiceActual);
            }
        }
    }
    fclose(tableroLeido);
    G->m = ((filas-1)*3+filas)+(filas-1);        //operacion matematica que entrega la cantidad de aristas del grafo y las guarda en G->m
    return G;
}


/*Funcion que imprime en pantalla el tablero representado como un grafo ND y NP con MA
Entradas: puntero a grafo (TDAGrafoMA*), tamanio del tablero (int)*/
void imprimirTablero(TDAGrafoMA *G, int tamanioTablero){
    printf("\n\n");
    for(int w=0; w<tamanioTablero; w++){
        for(int q=0; q<tamanioTablero; q++){
            printf("%c ",G->V[w*tamanioTablero + q]);
        }
        printf("\n");
    }
}


/*Funcion que escribe el tablero representado como un grafo ND y NP con MA en un archivo de texto
Entradas: puntero a grafo (TDAGrafoMA*), archivo a escribir (FILE*)*/
void escribirTablero(TDAGrafoMA *G, FILE* archivo, int tamanioTablero){
    for(int w=0; w<tamanioTablero; w++){
        for(int q=0; q<tamanioTablero; q++){
            fprintf(archivo,"%c ",G->V[w*tamanioTablero + q]);
        }
        fprintf(archivo,"\n");
    }
    fprintf(archivo,"\n");
    return;
}

/*Funcion que busca palabras dentro del tablero como grafo ND y NP con MA, y entrega un int con su resultado.
Ademas, escribe el tablero con la palabra destacada con * en un archivo externo, y si encuentra una palabra
la escribe junto con su posicion en el tablero en un archivo externo
Entrada: puntero a grafo (TDAGrafoMA*), array de char palabra a buscar (char*), tamaniotablero (int),
FILE* flujo del archivo a escribir lista.out, FILE* flujo del archivo a escribir tablero.out
Salida: int 1 (palabra encontrada), int 0 (palabra no encontrada)*/
int buscarPalabras(TDAGrafoMA* g, char* word, int cantFilas, FILE* archivoCoorde, FILE* archivoTableros){

    int largoWord = strlen(word), auxBus, palabraEncontrada, fi, co;
    char letraActual;

    //primero recorro el array de vertices y analizo cada uno
    for(int i=0; i<g->n; i++){

        if(word[0] == g->V[i]){         //coincidencia primera letra

            //busqueda horizontal derecha
            palabraEncontrada = 1;
            if(i+largoWord-1 < g->n){         //condicion para no llegar al limite del tablero

                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra
                    //obviamente es adaycente con el de al lado pero igual se usa la funcion por si saltamos de fila en el tablero
                    auxBus = sonVerticesAdyacentes(g, i+j-1, i+j-1+1);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j-1+1]){
                            palabraEncontrada = 0;      //si las letras son distintas, no es la palabra
                        }
                    }else{
                        palabraEncontrada = 0;  //no son adyacentes por lo que no es la palabra
                    }
                }
                if(palabraEncontrada==1){

                    //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO
                    for(int c=0; c<largoWord; c++){
                        g->V[i+c-1+1] = '*';    //cambiar letras palabra por asteriscos
                    }

                    escribirTablero(g, archivoTableros, cantFilas);  //escribimos el tablero en el archivo de salida

                    for(int c=0; c<largoWord; c++){
                        g->V[i+c-1+1] = word[c];    //cambiar asteriscos por letras originales
                    }

                    //proceso imprimir posicion palabra en tablero
                    fprintf(archivoCoorde,"%d %d (%s)\n", i/cantFilas + 1, i%cantFilas + 1, word); //con la div entera + 1 obtenemosla fila y con el modulo + 1 obtenemos la columna
                    return palabraEncontrada;
                }
            }

            //busqueda hacia abajo
            palabraEncontrada = 1;
            if(i+cantFilas*(largoWord-1) < g->n){       //condicion para no llegar al limite de abajo del tablero

                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra
                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1), i+cantFilas*j);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }
                }
                if(palabraEncontrada==1){

                    //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO
                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas] = '*';    //cambiar letras palabra por asteriscos
                    }

                    escribirTablero(g, archivoTableros, cantFilas);  //escribimos el tablero en el archivo de salida

                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas] = word[c];    //cambiar asteriscos por letras originales
                    }

                    //proceso imprimir posicion palabra en tablero
                    fprintf(archivoCoorde,"%d %d (%s)\n", i/cantFilas + 1, i%cantFilas + 1, word);
                    return palabraEncontrada;
                }
            }

            //busqueda hacia abajo izq \esta
            palabraEncontrada = 1;
            if(i+cantFilas*(largoWord-1) < g->n && i+largoWord < g->n){     //condiciones limites tablero

                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra
                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1)+j-1, i+cantFilas*j +j);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas+j]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }
                }
                if(palabraEncontrada==1){

                    //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO
                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas+c] = '*';    //cambiar letras palabra por asteriscos
                    }

                    escribirTablero(g, archivoTableros, cantFilas);  //escribimos el tablero en el archivo de salida

                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas+c] = word[c];    //cambiar asteriscos por letras originales
                    }


                    //proceso imprimir posicion palabra en tablero
                    fprintf(archivoCoorde,"%d %d (%s)\n", i/cantFilas + 1, i%cantFilas + 1, word);
                    return palabraEncontrada;

                }
            }

            //busqueda hacia abajo dere /esta
            palabraEncontrada = 1;
            if(i+cantFilas*(largoWord-1) < g->n && i+1-largoWord >= 0){

                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra
                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1)-j+1, i+cantFilas*j -j);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas-j]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }
                }
                if(palabraEncontrada==1){

                    //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO
                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas-c] = '*';    //cambiar letras palabra por asteriscos
                    }

                    escribirTablero(g, archivoTableros, cantFilas);  //escribimos el tablero en el archivo de salida

                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas-c] = word[c];    //cambiar asteriscos por letras originales
                    }


                    //proceso imprimir posicion palabra en tablero
                    fprintf(archivoCoorde,"%d %d (%s)\n", i/cantFilas + 1, i%cantFilas + 1, word);
                    return palabraEncontrada;

                }
            }
        }
    }



    //busqueda de la palabra inversa
    strrev(word);   //invertimos palabra
    for(int i=0; i<g->n; i++){

        if(word[0] == g->V[i]){         //coincidencia primera letra

            //busqueda horizontal derecha
            palabraEncontrada = 1;
            if(i+largoWord-1 < g->n){         //condicion para no llegar al limite del tablero
                
                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra
                    auxBus = sonVerticesAdyacentes(g, i+j-1, i+j-1+1);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j-1+1]){
                            palabraEncontrada = 0;
                            break;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }
                }
                if(palabraEncontrada==1){

                    //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO
                    for(int c=0; c<largoWord; c++){
                        g->V[i+c-1+1] = '*';    //cambiar letras palabra por asteriscos
                    }

                    escribirTablero(g, archivoTableros, cantFilas);  //escribimos el tablero en el archivo de salida

                    for(int c=0; c<largoWord; c++){
                        g->V[i+c-1+1] = word[c];    //cambiar asteriscos por letras originales
                    }

                    //proceso imprimir posicion palabra en tablero
                    strrev(word);
                    fprintf(archivoCoorde,"%d %d (%s)\n", i/cantFilas + 1, i%cantFilas +largoWord, word);
                    return palabraEncontrada;
                }
            }

            //busqueda hacia abajo
            palabraEncontrada = 1;
            if(i+cantFilas*(largoWord-1) < g->n){       //condicion para no llegar al limite de abajo del tablero

                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra
                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1), i+cantFilas*j);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }
                }
                if(palabraEncontrada==1){

                    //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO
                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas] = '*';    //cambiar letras palabra por asteriscos
                    }

                    escribirTablero(g, archivoTableros, cantFilas);  //escribimos el tablero en el archivo de salida

                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas] = word[c];    //cambiar asteriscos por letras originales
                    }


                    //proceso imprimir posicion palabra en tablero
                    strrev(word);
                    fprintf(archivoCoorde,"%d %d (%s)\n", i/cantFilas +largoWord, i%cantFilas + 1, word);
                    return palabraEncontrada;
                }   
            }

            //busqueda hacia abajo izq \esta
            palabraEncontrada = 1;
            if(i+cantFilas*(largoWord-1) < g->n && i+largoWord < g->n){     //condiciones limites tablero

                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra
                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1)+j-1, i+cantFilas*j +j);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas+j]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }
                }
                if(palabraEncontrada==1){

                    //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO
                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas+c] = '*';    //cambiar letras palabra por asteriscos
                    }

                    escribirTablero(g, archivoTableros, cantFilas);  //escribimos el tablero en el archivo de salida

                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas+c] = word[c];    //cambiar asteriscos por letras originales
                    }


                    //proceso imprimir posicion palabra en tablero
                    strrev(word);
                    fprintf(archivoCoorde,"%d %d (%s)\n", i/cantFilas +largoWord, i%cantFilas+largoWord, word);
                    return palabraEncontrada;
                }
            }

            //busqueda hacia abajo dere /esta
            palabraEncontrada = 1;
            if(i+cantFilas*(largoWord-1) < g->n && i+1-largoWord >= 0){

                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra
                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1)-j+1, i+cantFilas*j -j);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas-j]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }
                }
                if(palabraEncontrada==1){

                    //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO
                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas+c] = '*';    //cambiar letras palabra por asteriscos
                    }

                    escribirTablero(g, archivoTableros, cantFilas);  //escribimos el tablero en el archivo de salida

                    for(int c=0; c<largoWord; c++){
                        g->V[i+c*cantFilas+c] = word[c];    //cambiar asteriscos por letras originales
                    }


                    //proceso imprimir posicion palabra en tablero
                    strrev(word);
                    fprintf(archivoCoorde,"%d %d (%s)\n", i/cantFilas+largoWord, i%cantFilas +1-largoWord+1,word);
                    return palabraEncontrada;
                }
            }
        }
    }

    strrev(word);   //vuelvo a invertir la palabra a su estado normal
    return 0;

}


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

    int nTablero = 0, cantPalabras = 0, cantPalabrasEncontradas = 0, resultadoFuncion;

    char* nombreLista = (char*)malloc(sizeof(char)*12);//limite de 12 letras en el nombre a buscar
    char* nombreTablero = (char*)malloc(sizeof(char)*12);

    printf("\nIngresar el nombre del archivo lista (con su extension .lst): ");
    scanf("%s",nombreLista);
    printf("Ingresar el nombre del archivo tablero (con su extension .ini): ");
    scanf("%s",nombreTablero);

    /* ------- Proceso creacion tablero y array de palabras ---------*/
    TDAGrafoMA *g = leerTablero(nombreTablero, &nTablero); 
    char** arrayPalabras = leerPalabras(nombreLista, &cantPalabras);

    // Medir tiempo
    //clock_t inicio, fin;
    //double tiempo;
    //inicio = clock();


    /* ------- Proceso cambiar nombre y creacion de archivos de salida ---------*/
    cambiarExtension3char(nombreLista, "out");
    cambiarExtension3char(nombreTablero, "out");
    FILE* salidaCoordenadas = fopen(nombreLista, "w");
    if(salidaCoordenadas == NULL){
        printf("\nNo se pudo crear el archivo");
        return;
    }else{
        printf("\nSe creo correctamente el archivo %s",nombreLista);
    }
    fprintf(salidaCoordenadas,"         \n");//escribimos salto para despues volver al inicio sin comernos escritura de coordenadas

    FILE* salidaTablero = fopen(nombreTablero, "w");
    if(salidaTablero == NULL){
        printf("\nNo se pudo crear el archivo");
        return;
    }else{
        printf("\nSe creo correctamente el archivo %s\n",nombreTablero);
    }



    /* ------- Proceso de busqueda de palabras ------------------------------*/
    for(int x=0; x<cantPalabras; x++){
        resultadoFuncion = buscarPalabras(g, arrayPalabras[x], nTablero, salidaCoordenadas, salidaTablero);
        if(resultadoFuncion==1){
            cantPalabrasEncontradas++;
        }
    }

    /* ------- Escribir en archivo salida de coordenadas la cantidad de palabras encontradas ----------*/
    rewind(salidaCoordenadas);                              //voy a la primera linea del archivo
    fprintf(salidaCoordenadas, "%d\n", cantPalabrasEncontradas);


    /* ------- Proceso imprimir en pantalla datos palabras encontradas y buscadas ----------*/
    printf("\nPalabras buscadas: %d\nPalabras encontradas: %d\n",cantPalabras, cantPalabrasEncontradas);
    fclose(salidaCoordenadas);
    fclose(salidaTablero);


    /* ------ Proceso liberar memoria ------------------------------------------------------*/
    for(int t=0; t<cantPalabras; t++){
        free(arrayPalabras[t]);
    }
    free(arrayPalabras);
    liberarGrafo(g);


    //medir tiempo
    //fin = clock();
    //tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    //printf("El tiempo  %f segundos\n", tiempo);

    return;
}