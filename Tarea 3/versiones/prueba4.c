#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAGrafoLA.h"





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






TDAGrafoMA *leer_tablero(char* nombreArchivo, int* tamanioTablero) {

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


void imprimirTablero(TDAGrafoMA *G, int tamanioTablero){
    printf("\n\n");
    for(int w=0; w<tamanioTablero; w++){
        for(int q=0; q<tamanioTablero; q++){
            printf("%c ",G->V[w*tamanioTablero + q]);
        }
        printf("\n");
    }
}



int buscarPalabras(TDAGrafoMA* g, char* word, int cantFilas){

    int largoWord = strlen(word), auxBus, palabraEncontrada, fi, co;
    //printf(" largo palabra  %d\n",largoWord);
    char letraActual;

    //primero recorro el array de vertices y analizo cada uno
    for(int i=0; i<g->n; i++){


        if(word[0] == g->V[i]){         //coincidencia primera letra


            palabraEncontrada = 1;
            //printf("buscando una word\n\n");
            for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra

                
                //busqueda horizontal derecha
                if(i+largoWord < g->n){         //condicion para no llegar al limite del tablero
                    
                    //obviamente es adaycente con el de al lado pero igual se usa la funcion por si saltamos de fila en el tablero
                    auxBus = sonVerticesAdyacentes(g, i+j-1, i+j-1+1);
                    //printf("los vertices num %d y %d son adyacentes  tipo %d\n",i+j-1, i+j-1+1, auxBus);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j-1+1]){
                            palabraEncontrada = 0;      //si las letras son distintas, no es la palabra
                        }
                    }else{
                        //no son adyacentes por lo que no es la palabra
                        palabraEncontrada = 0;
                    }

                    if(palabraEncontrada==1){

                        //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO



                        //proceso imprimir coordenadas palabra en tablero
                        co = i%cantFilas + 1;       //con el modulo + 1 obtenemos la columna
                        fi = i/cantFilas + 1;       //con la div entera + 1 obtenemosla fila
                        printf("%d %d (%s)\n", fi, co,word);
                        return palabraEncontrada;

                    }
                }

                
                //busqueda hacia abajo
                if(i+cantFilas*(largoWord-1) < g->n){       //condicion para no llegar al limite de abajo del tablero

                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1), i+cantFilas*j);
                    //printf("los vertices num %d y %d son adyacentes  tipo %d\n", i+cantFilas*(j-1), i+cantFilas*j, auxBus);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }

                    if(palabraEncontrada==1){

                        //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO



                        //proceso imprimir coordenadas palabra en tablero
                        co = i%cantFilas + 1;       //con el modulo + 1 obtenemos la columna
                        fi = i/cantFilas + 1;       //con la div entera + 1 obtenemosla fila
                        printf("%d %d (%s)\n", fi, co,word);
                        return palabraEncontrada;

                    }
                }


                //busqueda hacia abajo izq \esta
                if(i+cantFilas*(largoWord-1) < g->n && i+largoWord < g->n){     //condiciones limites tablero

                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1)+j-1, i+cantFilas*j +j);
                    //printf("los vertices num %d y %d son adyacentes  tipo %d\n", i+cantFilas*(j-1)+j-1, i+cantFilas*j +j, auxBus);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas+j]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }

                    if(palabraEncontrada==1){

                        //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO



                        //proceso imprimir coordenadas palabra en tablero
                        co = i%cantFilas + 1;       //con el modulo + 1 obtenemos la columna
                        fi = i/cantFilas + 1;       //con la div entera + 1 obtenemosla fila
                        printf("%d %d (%s)\n", fi, co,word);
                        return palabraEncontrada;

                    }
                }


                //busqueda hacia abajo dere /esta
                if(i+cantFilas*(largoWord-1) < g->n && i+1-largoWord >= 0){

                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1)-j+1, i+cantFilas*j -j);
                    //printf("los vertices num %d y %d son adyacentes  tipo %d\n", i+cantFilas*(j-1)-j+1, i+cantFilas*j -j, auxBus);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas-j]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }

                    if(palabraEncontrada==1){

                        //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO



                        //proceso imprimir coordenadas palabra en tablero
                        co = i%cantFilas + 1;       //con el modulo + 1 obtenemos la columna
                        fi = i/cantFilas + 1;       //con la div entera + 1 obtenemosla fila
                        printf("%d %d (%s)\n", fi, co,word);
                        return palabraEncontrada;

                    }
                }


                

            }






        }

    }



    //busqueda de la palabra inversa
    strrev(word);

    for(int i=0; i<g->n; i++){


        if(word[0] == g->V[i]){         //coincidencia primera letra


            palabraEncontrada = 1;
            //printf("buscando una word\n\n");
            //for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra

                
                //busqueda horizontal derecha
            if(i+largoWord < g->n){         //condicion para no llegar al limite del tablero
                

                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra

                    //obviamente es adaycente con el de al lado pero igual se usa la funcion por si saltamos de fila en el tablero
                    auxBus = sonVerticesAdyacentes(g, i+j-1, i+j-1+1);
                    //printf("los vertices num %d y %d son adyacentes  tipo %d\n",i+j-1, i+j-1+1, auxBus);
                    if(auxBus == 1){
                        printf(" comparacion    %c == %c\n",word[j] ,g->V[i+j-1+1]);
                        if(word[j] != g->V[i+j-1+1]){
                            palabraEncontrada = 0;      //si las letras son distintas, no es la palabra
                            break;
                        }
                    }else{
                        //no son adyacentes por lo que no es la palabra
                        palabraEncontrada = 0;
                    }

                    if(palabraEncontrada==1){

                        //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO



                        //proceso imprimir coordenadas palabra en tablero
                        strrev(word);
                        co = i%cantFilas + 1;       //con el modulo + 1 obtenemos la columna
                        fi = i/cantFilas + 1;       //con la div entera + 1 obtenemosla fila
                        printf("%d %d (%s)\n", fi, co+largoWord-1,word);
                        return palabraEncontrada;

                    }
                }
            }

                
                //busqueda hacia abajo
            if(i+cantFilas*(largoWord-1) < g->n){       //condicion para no llegar al limite de abajo del tablero

                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra
                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1), i+cantFilas*j);
                    //printf("los vertices num %d y %d son adyacentes  tipo %d\n", i+cantFilas*(j-1), i+cantFilas*j, auxBus);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }

                    if(palabraEncontrada==1){

                        //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO



                        //proceso imprimir coordenadas palabra en tablero
                        strrev(word);
                        co = i%cantFilas + 1;       //con el modulo + 1 obtenemos la columna
                        fi = i/cantFilas + 1;       //con la div entera + 1 obtenemosla fila
                        printf("%d %d (%s)\n", fi+largoWord-1, co,word);
                        return palabraEncontrada;

                    }
                }
            }


                //busqueda hacia abajo izq \esta
            if(i+cantFilas*(largoWord-1) < g->n && i+largoWord < g->n){     //condiciones limites tablero

                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra

                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1)+j-1, i+cantFilas*j +j);
                    //printf("los vertices num %d y %d son adyacentes  tipo %d\n", i+cantFilas*(j-1)+j-1, i+cantFilas*j +j, auxBus);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas+j]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }

                    if(palabraEncontrada==1){

                        //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO



                        //proceso imprimir coordenadas palabra en tablero
                        strrev(word);
                        co = i%cantFilas + 1;       //con el modulo + 1 obtenemos la columna
                        fi = i/cantFilas + 1;       //con la div entera + 1 obtenemosla fila
                        printf("%d %d (%s)\n", fi+largoWord-1, co+largoWord-1,word);
                        return palabraEncontrada;

                    }
                }
            }


                //busqueda hacia abajo dere /esta
            if(i+cantFilas*(largoWord-1) < g->n && i+1-largoWord >= 0){


                for(int j=1; j<largoWord; j++){         //iteramos en la palabra desde la 2da letra
                    auxBus = sonVerticesAdyacentes(g, i+cantFilas*(j-1)-j+1, i+cantFilas*j -j);
                    //printf("los vertices num %d y %d son adyacentes  tipo %d\n", i+cantFilas*(j-1)-j+1, i+cantFilas*j -j, auxBus);
                    if(auxBus == 1){
                        if(word[j] != g->V[i+j*cantFilas-j]){
                            palabraEncontrada = 0;
                        }
                    }else{
                        palabraEncontrada = 0;
                    }

                    if(palabraEncontrada==1){

                        //  PROCESO ESCRIBIR TABLERO CON * EN TEXTO



                        //proceso imprimir coordenadas palabra en tablero
                        strrev(word);
                        co = i%cantFilas + 1;       //con el modulo + 1 obtenemos la columna
                        fi = i/cantFilas + 1;       //con la div entera + 1 obtenemosla fila
                        printf("%d %d (%s)\n", fi+largoWord-1, co-largoWord+1,word);
                        return palabraEncontrada;

                    }
                }
            }


                

            //}






        }

    }


    strrev(word);   //vuelvo a invertir la palabra a su estado normal
    return palabraEncontrada;

}


void main(){
    
	//TDAGrafoLA *grafo = crearGrafoVacio(5);

    int nTablero = 0, cantPalabras = 0;
    TDAGrafoMA *g = leer_tablero("tab2.ini",&nTablero); 

    /*
    if(g != NULL){
        //imprimir la matriz de adyacencia del grafo/tablero
        printf("Matriz de adyacencia del grafo:\n");
        for(int i = 0; i < g->n; i++){
            for(int j = 0; j < g->n; j++){
                printf("%d ", g->A[i][j]);
            }
            printf("\n");
        }
    }*/


    imprimirTablero(g,nTablero);




    printf("\n\n");
    char** arrayPalabras = leerPalabras("lista1.lst",&cantPalabras);
    //imprimirPalabras(arrayPalabras, cantPalabras);

    int resultadoFuncion;
    //for(int x=0; x<cantPalabras; x++){
    //    resultadoFuncion = buscarPalabras(g, arrayPalabras[x], nTablero);
    //}
    
    resultadoFuncion = buscarPalabras(g, arrayPalabras[0], nTablero);
}
