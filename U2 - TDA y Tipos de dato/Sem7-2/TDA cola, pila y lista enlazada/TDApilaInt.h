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
  TDApila* pila = (TDApila*)malloc(sizeof(TDApila));
  pila->capacidad = capacidad;
  pila->size = 0;
  pila->tope = NULL;
  return pila;
}

/*Funcion que verifica si una pila esta vacia o no
Entrada: TDApila
Salida: int 1 (pila vacia), 0 (pila no vacia)*/
int esPilaVacia(TDApila* pila){
  if (pila->size == 0)
    return 1;
  else
    return 0;
}


/*Funcion TOP que entrega el nodo tope de una pila con sus elementos (su dato y su puntero)
Entrada: TDApila*/
nodo* topePila(TDApila* pila){
  return pila->tope;
}

/*Funcion TOP que retorna el numero del tope de la pila
Entrada: TDApila*/
int datoTopePila(TDApila* pila){
  nodo* top = pila->tope;
  //rintf("El dato tope es %i\n",top->dato);
  return top->dato;
}

/*Funcion PUSH que apila en el tope los datos en una pila
Entrada: TDApila, int dato a ingresar*/
void apilar(TDApila* pila, int dato){
  if(pila->size < pila->capacidad){   //condicion la pila no esta llena
    nodo* nodoNuevo = (nodo*)malloc(sizeof(nodo));
    nodoNuevo->dato = dato;
    nodoNuevo->puntero = pila->tope;
    pila->tope = nodoNuevo;
    pila->size = pila->size + 1;
  }else{
    printf("No se puede seguir apilando elemento, se supero el maximo\n");
  }
}


/*Funcion POP que desapila los elementos de una pila mientras sea posible
Entrada: TDApila*/
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

/*Funcion que bus un dato en una pila devuelve un resultado
Entrada: TDApila, int dato buscado
Salida: int 1 (dato encontrado), 0 (dato no encontrado)*/
int buscarDatoPila(TDApila* pila, int dato){
  if(!esPilaVacia(pila)){
    nodo* aux = pila->tope;
    while(aux != NULL){
      if(aux->dato == dato){
        return 1;
      }
      aux = aux->puntero;
    }
    return 0;
  }else{
    printf("La pila esta vacia, no se puede buscar algun dato\n");
    return 0;
  }
}

/*Funcion que me entrega una pila con los elementos invertidos de otra pila
Entrada: TDApila
Salida: TDApila*/
TDApila* pilaInvertida(TDApila *pila){
  int capacidadPila = pila->capacidad;
  TDApila* pilaSalida = crearPilaVacia(capacidadPila);
  TDApila* pilaAuxiliar = crearPilaVacia(capacidadPila);
  int i=1, valorTope;
  for(i; i<=(capacidadPila); i++){
    valorTope = datoTopePila(pila);
    desapilar(pila);
    apilar(pilaSalida, valorTope);
    apilar(pilaAuxiliar, valorTope);
  }
  for(i=1; i<=capacidadPila; i++){
    valorTope = datoTopePila(pilaAuxiliar);
    desapilar(pilaAuxiliar);
    apilar(pila, valorTope);
  }
  return pilaSalida;
}

/*Funcion que muestra en pantalla los elementos de una pila,
el primero es el tope
Entrada: TDApila*/
void mostrarPila(TDApila* pila){
  if(!esPilaVacia(pila)){
    nodo* aux = pila->tope;
    while(aux != NULL){
      printf(" %i ",aux->dato);
      aux = aux->puntero;
    }
    printf("\n");
  }else{
    printf("La pila esta vacia\n");
  }
}
