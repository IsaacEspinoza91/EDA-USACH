#include <stdio.h>
#include <stdlib.h>
#include "TDAGrafoLA.h"



TDAGrafoMA* crearLeerTablero(char* nombreArchivo/*, int* tamanioTablero*/){
    int nFilas;
    char varAux;


    FILE* tableroLeido = fopen(nombreArchivo, "r");
    if(nombreArchivo == NULL){
        printf("Error al leer el tablero\n");
        exit(1);
    }else{
        printf("\nEl archivo %s se abrio correctamente",nombreArchivo);
    }

    //proceso leer pimer numero del documento y guardarlo en nfilas   ej    x x
    //lectura de la primera linea de texto, tamanio tablero filasxcolumnas
    int columTablero;
    fscanf(tableroLeido,"%d %d", &nFilas, &columTablero);




    //int u;
    int cantVertices = nFilas*nFilas;
    TDAGrafoMA* G = crearGrafoVacioMA(cantVertices);

    int k = 1;          //numeracion del vertice, ojo que hay que restar uno para posicionarlos en la matriz, ver funcion agregar_aristaMA
    for(int i=0; i<nFilas; i++){
        for(int j=0; j<nFilas; j++){

            fscanf(tableroLeido, " %c", &varAux);
            G->V[k-1] = varAux;                            //guardar la letra de cada vertice en el array de vertices

            //u = i * nFilas + j;

            //agregar hori derecha
            if(j< nFilas - 1){        //ultimo vertice de la fila
                agregar_aristaMA_NP(G, k, k+1);
                agregar_aristaMA_NP(G, k+1, k);
            }
            //agregar diagonal 1 \esta
            if(j < nFilas - 1 && i < nFilas){
                agregar_aristaMA_NP(G, k, k+nFilas+1);
                agregar_aristaMA_NP(G, k+nFilas+1, k);
            }
            //agregar diagonal 2 /esta
            if(j > 0 && i < nFilas - 1){
                agregar_aristaMA_NP(G, k, k+nFilas-1);
                agregar_aristaMA_NP(G, k+nFilas-1, k);
            }
            //agregar vertical abajo
            if(i < nFilas - 1){
                agregar_aristaMA_NP(G, k, k+nFilas);
                agregar_aristaMA_NP(G, k+nFilas, k);
            }


            k = k + 1;
        }

    }



    G->m = ((nFilas-1)*3+nFilas)+(nFilas-1);        //operacion matematica que entrega la cantidad de aristas del grafo y las guarda en G->m

    return G;
}



void main(){
    
	//TDAGrafoLA *grafo = crearGrafoVacio(5);

    TDAGrafoMA *g = crearLeerTablero("tab2.ini"); 

    if(g != NULL){
        // Imprime la matriz de adyacencia del grafo
        printf("Matriz de adyacencia del grafo:\n");
        for (int i = 0; i < g->n; i++) {
            for (int j = 0; j < g->n; j++) {
                printf("%d ", g->A[i][j]);
            }
            printf("\n");
        }
    }

}
