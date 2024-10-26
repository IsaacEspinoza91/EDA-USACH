#include <stdio.h>
#include <stdlib.h>
#include "TDAGrafoLA.h"





TDAGrafoMA *leer_tablero(char *nombreArchivo, int* tamanioTablero) {

    int filas, columnas, indiceActual, indiceVertiAdy;
    char varAux;

    //abremos el tableroLeido del tablero
    FILE *tableroLeido = fopen(nombreArchivo, "r");
    if(tableroLeido == NULL){
        printf("Error al abrir el tableroLeido\n");
        return NULL;
    }else{
        printf("\nEl archivo %s se abrio correctamente",nombreArchivo);
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
            if (j < columnas - 1) {
                indiceVertiAdy = i * columnas + (j + 1); //indice vertice lado derecho en el array de vertices
                agregar_aristaMA_NP(G, indiceActual, indiceVertiAdy);
                agregar_aristaMA_NP(G, indiceVertiAdy, indiceActual);
            }
            //agregar vertical adya abajo
            if (i < filas - 1) {
                indiceVertiAdy = (i + 1) * columnas + j;
                agregar_aristaMA_NP(G, indiceActual, indiceVertiAdy);
                agregar_aristaMA_NP(G, indiceVertiAdy, indiceActual);
            }
            //agregar diagonal 1 \esta
            if (i < filas - 1 && j < columnas - 1) {
                indiceVertiAdy = (i + 1) * columnas + (j + 1);
                agregar_aristaMA_NP(G, indiceActual, indiceVertiAdy);
                agregar_aristaMA_NP(G, indiceVertiAdy, indiceActual);
            }
            //agregar diagonal 2 /esta
            if (i < filas - 1 && j > 0) {
                indiceVertiAdy = (i + 1) * columnas + (j - 1);
                agregar_aristaMA_NP(G, indiceActual, indiceVertiAdy);
                agregar_aristaMA_NP(G, indiceVertiAdy, indiceActual);
            }
        }
    }
    fclose(tableroLeido);
    return G;
}


void imprimirTablero(TDAGrafoMA *G, int tamanioTablero){
    printf("\n\n");
    for(int q=0; q<tamanioTablero; q++){
        for(int w=0; w<tamanioTablero; w++){
            printf("%c",G->V[q+w]);
        }
        printf("\n");
    }
}




void main(){
    
	//TDAGrafoLA *grafo = crearGrafoVacio(5);

    int nTablero = 0;
    TDAGrafoMA *g = leer_tablero("tab2.ini",&nTablero); 

    if(g != NULL){
        //imprimir la matriz de adyacencia del grafo/tablero
        printf("Matriz de adyacencia del grafo:\n");
        for (int i = 0; i < g->n; i++) {
            for (int j = 0; j < g->n; j++) {
                printf("%d ", g->A[i][j]);
            }
            printf("\n");
        }
    }


    imprimirTablero(g,nTablero);


}
