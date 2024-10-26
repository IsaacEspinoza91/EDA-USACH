#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico{
   int dato;
   struct nodoGenerico* puntero;
}nodo;

typedef struct{
  int capacidad;
  int size;
  nodo* tope;
}TDApila;

/*------------- operaciones -------------*/

TDApila* crearPilaVacia(int capacidad){
  TDApila* pila=(TDApila*)malloc(sizeof(TDApila));
  pila->capacidad=capacidad;
  pila->size=0;
  pila->tope=NULL;
  return pila;
}

/*Funcion que verifica si una pila esta vacia o no
Entrada: TDApila puntero
Salida: int, 1 pila vacia, 0 pila no vacia*/
int esPilaVacia(TDApila* pila){
  if (pila->size == 0)
    return 1;
  else
    return 0;
}


/*------------- Actividad 2 -------------*/
/*Funcion quue entrega los datos del tope de una pila (su dato y su puntero)
Entrada: TDApila puntero*/
nodo* tope(TDApila* pila){
  return pila->tope;
}

/*------------- Actividad 3 -------------*/
/*Funcion que aplica en el tope los datos en una pila
Entrada: TDApila puntero, numero entero dato a ingresar*/
void apilar(TDApila* pila, int dato){
  if(pila->size < pila->capacidad){
    nodo* nodoNuevo = (nodo*)malloc(sizeof(nodo));
    nodoNuevo->dato = dato;
    nodoNuevo->puntero = pila->tope;
    pila->tope = nodoNuevo;
    pila->size = pila->size + 1;
  }else{
    printf("No se puede seguir apilando elemento, se supero el maximo\n");
  }
}

/*------------- Actividad 4 -------------*/
/*Funcion que desapila los elementos de una pila mientras sea posible
Entrada: TDApila puntero*/
void desapilar(TDApila* pila){
  if(pila->size > 0){
    nodo* nodoActual = pila->tope;
    pila->tope = nodoActual->puntero;
    pila->size = pila->size - 1;
    free(nodoActual);
  }else{
    printf("No se puede seguir desapilando elementos\n");
  }
}

/*------------- Actividad 5 -------------*/
int buscarDatoPila(TDApila* pila, int dato);




