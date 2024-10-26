/* grafo no dirigido no ponderado usando LISTA DE ADYACENCIA */
#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h" 
//#include "TDAlistaTripleta.h"
//#include "TDAcola.h"


/*------------- estructura de datos -------------*/

struct grafo{
	TDAlista* A; 					//Arreglo donde cada celda representa un vertice y de tipo Lista
	int* V;							//Arreglo donde cada celda representa un vertice y de tipo entero
	int n; 							//número de vértices del grafo
	int m; 							//numero de aristas del grafo
};
typedef struct grafo TDAGrafoLA;


struct grafoNDNP{
	int ** A;						//array de arrays (matriz de adyacencia), donde cada vertices es un numero entero 
	char* V;						//array de vertices como letras char
	int n;							//numero de vertices
	int m;							//numero de aristas
};
typedef struct grafoNDNP TDAGrafoMA;


/*------------- operaciones -------------*/

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

void agregar_aristaMA_NP(TDAGrafoMA* G, int nVertice1, int nVertice2){
	G->A[nVertice1][nVertice2] = 1;
}


int sonVerticesAdyacentes(TDAGrafoMA* G, int nV1, int nV2){
	if(G->A[nV1][nV2] == 1){
		return 1;
	}else{
		return 0;
	}
}

void imprimirMatrizAdyacencia(TDAGrafoMA* g){
	printf("Matriz de adyacencia del grafo:\n");
	for(int i = 0; i < g->n; i++){
		for(int j = 0; j < g->n; j++){
			printf("%d ", g->A[i][j]);
		}
		printf("\n");
	}
}


void liberarGrafo(TDAGrafoMA *g){
  	for(int i = 0; i < g->n; i++){
    	free(g->A[i]);
  	}
	free(g->A);
  	free(g->V);
  	free(g);
}




TDAGrafoLA* crearGrafoVacio(int n){
	int i;

	TDAGrafoLA* G = malloc(sizeof(TDAGrafoLA));
    G->A = (TDAlista*)malloc(sizeof(TDAlista)*n);
    G->V = (int*)malloc(sizeof(int)*n);

	for (i=0; i<n; i++){
      G->A[i] = crearListaVacia(); 
	  G->V[i] = i+1; 	
	}
	G->n = n;
	G->m = 0;

	return  G;	
}

void imprimirListaAdyacencia(TDAGrafoLA* G){
	int i; 
	printf("Numero de vertices:%d \n",G->n);
	for (i=0; i<G->n; i++){
		printf("%d  ",G->V[i]);
	}
	printf("\nNumero de aristas:%d \n",G->m);
	for (i=0; i<G->n; i++){
		printf("%d  |",i+1 );
		recorrerLista(G->A[i]);
	}
}



/*
void agregar_arista(TDAGrafoLA* G, int v, int w){
	insertarInicio(&(G->A[v-1]),w);
}

void agregar_arista_peso(TDAGrafoLA *G, int v, int w, int peso){
	insertarInicioTripleta(&(G->A[v-1]),v,w,peso);	
}


//NoDirigido NoPonderado
TDAGrafoLA* leerGrafoNoDirigido(char *nombreArchivo){
	int n_vertices, m_aristas;
	int i,j,k;
	TDAGrafoLA* G;

	FILE* pf=fopen(nombreArchivo,"r");
	if (pf ==NULL){
		printf("Error de archivo\n");
		return NULL;
	}else{
		//Cantidad de vértices y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas);
		G = crearGrafoVacio(n_vertices);
		G->n = n_vertices;
		G->m = m_aristas;
		
		for(k=0;k<m_aristas;k++){
			fscanf(pf,"%d %d",&i, &j);
			agregar_arista(G, i, j);
			agregar_arista(G, j, i);			
		}
		fclose(pf);
		return  G;	
	}
}
*/

//NoDirigido Ponderado
/*
TDAGrafoLA* leerGrafoNoDirigidoPond(char *nombreArchivo){
	FILE*pf;		   					
	pf = fopen(nombreArchivo,"r");
	int n_vertices, m_aristas, peso;
	int i,j,k,p;
	if (pf ==NULL){
		printf("Error de archivo\n");
		return NULL;
	}else{
		//Cantidad de nodos y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		
		TDAGrafoLA *G=crearGrafoVacio(n_vertices);	
		G->n=n_vertices;
		G->m=m_aristas;
		//dependiendo de las lineas de archivo, 
		for(k=0;k<m_aristas;k++){
			fscanf(pf,"%d %d %d",&i, &j, &p);
			agregar_arista_peso(G, i, j, p);
			agregar_arista_peso(G, j, i, p);			
		}
		fclose(pf);
		return  G;	
	}
}


TDAlista obtenerAdyacentes(TDAGrafoLA* grafo, int vertice){
	TDAlista adyacentes=crearListaVacia();
	nodo* aux= grafo->A[vertice-1];
	while (aux!=NULL) 
	{
		insertarInicio(&adyacentes, aux->dato);
		aux=aux->puntero;		
	}
	return(adyacentes);
}


//Actividades asíncronas
int adyacenciaNodos(TDAGrafoLA* G, int vertice1, int vertice2);
int esCompleto(TDAGrafoLA* G);
int esCamino(TDAGrafoLA* G, TDAlista* secuencia);
int esComplemento(TDAGrafoLA* G1, TDAGrafoLA* G2);
int gradodeVertice(TDAGrafoLA* G, int vertice);
int gradoPromedio(TDAGrafoLA* G); 
int esRegular(TDAGrafoLA* G); 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++

-------- semana 9 -------------

void marcarVisitado(int* visitados, int vertice);
int adyacenteNoVisitado(TDAlista adyacentes, int* visitados);
void recorridoDFS(TDAGrafoLA* grafo, int inicio);
int estaVisitado(int vertice);
void recorridoBFS(TDAGrafoLA* grafo, int vertice);

-------- semana 10 -----------

//void caminoMinimoDijkstra(TDAGrafoLA* grafo, int inicio);
//TDAlista* mstPrim(TDAGrafoLA* grafo, int inicio); TDAlistaTripleta* 

TDAlistaTripleta* msrtKruskal(TDAGrafoLA* grafo){
	
	TDAlistaTripleta MST = crearListaVaciaTripleta();

	//TDAcola colaAristas = grafo;

}
*/