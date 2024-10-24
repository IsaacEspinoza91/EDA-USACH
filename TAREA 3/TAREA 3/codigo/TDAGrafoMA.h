/* grafo no dirigido no ponderado usando MATRIZ DE ADYACENCIA */
#include <stdio.h>
#include <stdlib.h>




/*------------- estructura de datos -------------*/

struct grafoNDNP{
	int ** A;						//array de arrays (matriz de adyacencia), donde cada vertices es un numero entero 
	char* V;						//array de vertices como letras char
	int n;							//numero de vertices
	int m;							//numero de aristas
};
typedef struct grafoNDNP TDAGrafoMA;


/*------------- operaciones -------------*/

/*Funcion que crea un grafo vacio ND NP con MA 
Entrada: cantidad vertices (int)
Salida: puntero a grafo (TDAGrafoMA*)*/
TDAGrafoMA* crearGrafoVacioMA(int n){
	TDAGrafoMA* G = malloc(sizeof(TDAGrafoMA));
	G->A = (int**)malloc(sizeof(int*)*n);
	for(int a = 0; a<n; a++){
		G->A[a] = (int*)malloc(sizeof(int)*n);
		for(int y=0; y<n; y++){
			G->A[a][y] = 0;
		}
	}

	G->V = (char*)malloc(sizeof(char)*n);
	G->n = n;
	G->m = 0;
	return  G;	
}

/*Funcion que agrega una arista entre vertices de un grafo ND NP con MA
Entrada: puntero a grafo (TDAGrafoMA*), numero Vertice1 (int), numero Vertice2 (int)*/
void agregar_aristaMA_NP(TDAGrafoMA* G, int nVertice1, int nVertice2){
	G->A[nVertice1][nVertice2] = 1;
}

/*Funcion que indica si un vertices es adyacente a otro vertice (en una direccion) para
un grafo ND NP MA
Entrada: puntero a grafo (TDAGrafoMA*), numero Vertice1 origen (int), numero Vertice2 llegada (int) 
Salida: int 1 si son adyacentes, int 0 si no son adyacentes*/
int sonVerticesAdyacentes(TDAGrafoMA* G, int nV1, int nV2){
	if(G->A[nV1][nV2] == 1){
		return 1;
	}else{
		return 0;
	}
}

/*Funcion que imprime en pantalla la matriz de adyacencia de un grafo ND NP con MA
Entrada: puntero a grafo (TDAGrafoMA*)*/
void imprimirMatrizAdyacencia(TDAGrafoMA* g){
	printf("Matriz de adyacencia del grafo:\n");
	for(int i = 0; i < g->n; i++){
		for(int j = 0; j < g->n; j++){
			printf("%d ", g->A[i][j]);
		}
		printf("\n");
	}
}

/*Funcion que libera la memoria utiliada por el grafo
Entrada: el grafo (TDAGrafoMA puntero)*/
void liberarGrafo(TDAGrafoMA *g){
  	for(int i = 0; i < g->n; i++){
    	free(g->A[i]);
  	}
	free(g->A);
  	free(g->V);
  	free(g);
}
