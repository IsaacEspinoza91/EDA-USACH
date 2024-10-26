#include <stdio.h>
#include <stdlib.h>


/*------------- estructura de datos -------------*/

typedef struct nodoGenericoCola{
   int dato;
   struct nodoGenericoCola* puntero;
}nodoCola;

typedef struct{
  int capacidad;
  nodoCola* frente;
  nodoCola* final;
}TDAcola;

/*------------- operaciones -------------*/

TDAcola* crearColaVacia(int capacidad){
  TDAcola* cola = (TDAcola*)malloc(sizeof(TDAcola));
  cola->capacidad = capacidad;
  cola->final = NULL;
  cola->frente = cola->final;
  return cola;
}

int esColaVacia(TDAcola* cola){
  if(cola->frente == NULL)
    return 1;
  else
    return 0;
}

void encolar(TDAcola* cola, int valor){
  nodoCola* nuevoNodo = (nodoCola*)malloc(sizeof(nodoCola));
  nuevoNodo->dato = valor;
  nuevoNodo->puntero = NULL;

  if(esColaVacia(cola)){
    cola->frente = cola->final = nuevoNodo;
  }else{
    cola->final->puntero = nuevoNodo;
    cola->final = nuevoNodo;
  }

}

void descolar(TDAcola* cola){
  if(esColaVacia(cola)){
    printf("Cola vacia, no se puede descolar\n");
    return;
  }

  nodoCola* nodo = cola->frente;
  cola->frente = nodo->puntero;
  free(nodo);

  //caso en que la cola se vacio despues de descolar
  if(esColaVacia(cola)){
    cola->final = NULL;
  }
}

int frente(TDAcola* cola){
  return cola->frente->dato;
}

int final(TDAcola* cola){
  return cola->final->dato;
}

void recoCola(TDAcola* cola){
  nodoCola* nodoAux = cola->frente;
  while(nodoAux!=NULL){
    printf(" %d ",nodoAux->dato);
    nodoAux = nodoAux->puntero;
  }
  printf("\n");
}