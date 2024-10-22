#include <stdio.h>
#include <stdlib.h>

//Estructura de datos TDA Coordenadas 

typedef struct nodoGenericoCoordenada{
    int fila;
    int colum;
    struct nodoGenericoCoordenada* puntero;
}nodoCoordenadasPalabra;

typedef nodoCoordenadasPalabra* TDAlistaCoordenadas;

//OPERACIONES
TDAlistaCoordenadas crearListaCoordenadasVacia(){
  TDAlistaCoordenadas lista = (TDAlistaCoordenadas)malloc(sizeof(TDAlistaCoordenadas));
  lista = NULL;
  return lista;
}

/*Funcion que comprueba si una lista enlazada simple esta vacia o no
Entrada: TDAlistaCoordenada
Salida: int 1 (lista vacia), 0 (lista con elementos)*/
int esListaCoordenadasVacia(TDAlistaCoordenadas lista){
  if(lista == NULL)
    return 1;
  else
    return 0;
}

/*Funcion que imprime los elementos char de una lista enlazada simple de coordenadas
Entrada: TDAlistaCoordenadas*/
void recorrerListaCoordenadas(TDAlistaCoordenadas lista){
  if (!esListaCoordenadasVacia(lista)){
    nodoCoordenadasPalabra* auxiliar = lista;
    while (auxiliar != NULL){
      printf("   (%d,%d)",auxiliar->fila, auxiliar->colum);
      auxiliar = auxiliar->puntero;
    }
    printf("\n");
  }else
    printf("La lista de coordenadas esta vacia\n");
}


/*Funcion que entrega la cantidad de elementos/nodos de una lista enlazada simple de coordenadas
Entrada: TDAlistaCoordenadas
Salida: int cantidad nodos*/
int cantidadNodosListaCoordenadas(TDAlistaCoordenadas lista){
  if(!esListaCoordenadasVacia(lista)){
    int cantidad = 0;
    nodoCoordenadasPalabra* auxiliar = lista;
    while(auxiliar != NULL){
      cantidad ++;
      auxiliar = auxiliar->puntero;
    }
    return cantidad;
  }else{
    return 0;
  }
}


/*Funcion que inserta un nodo al inicio de una lista enlazada simple de coordenadas
Entrada: TDAlistaCoordenadas (referencia) puntero, int fila, int columna*/
void insertarNodoInicioListaCoordenadas(TDAlistaCoordenadas* lista, int fila, int columna){
  nodoCoordenadasPalabra* nuevo = (nodoCoordenadasPalabra*)malloc(sizeof(nodoCoordenadasPalabra));
  nuevo->fila = fila;
  nuevo->colum = columna;
  nuevo->puntero = *lista;
  *lista = nuevo;
}


/*Funcion que inserta un nodo al final de una lista enlazada simple de coordenadas
Entrada: TDAlistaCoordendas (ref) puntero,  int fila, int columna*/
void insertarNodoFinalListaCoordenadas(TDAlistaCoordenadas *lista,  int fila, int columna){
  if(!esListaCoordenadasVacia(*lista)){
    nodoCoordenadasPalabra *final = *lista;
    while(final->puntero != NULL){
      final = final->puntero;
    }
    nodoCoordenadasPalabra *nuevoNodo = (nodoCoordenadasPalabra*)malloc(sizeof(nodoCoordenadasPalabra)); //crearNodoVacio()
    nuevoNodo->fila = fila;
    nuevoNodo->colum = columna;
    nuevoNodo->puntero = NULL;
    final->puntero = nuevoNodo;
  }else{  //condicion para el caso en que se quiera insertar al final y sea lista vacia, evita error
    insertarNodoInicioListaCoordenadas(lista, fila, columna);
  }
}



/*Funcion que elimina el primer nodo de una lista enlazada simple de coordenadas
Entrada: TDAlistaCoordenadas (ref) puntero*/
void eliminarNodoInicioListaCoordenadas(TDAlistaCoordenadas* lista){
  if(!esListaCoordenadasVacia(*lista)){
    nodoCoordenadasPalabra* auxiliar;
    auxiliar = *lista;
    *lista = (*lista)->puntero;
    free(auxiliar);
  }else{
    printf("No se puede eliminar un nodo coordendasde una lista vacia\n");
  }
}


/*Funcion que elimina el ultimo nodo de una lista enlazada simple de coordenadas
Entrada: TDAlistaCoordenadas (ref) puntero*/
void eliminarNodoFinalListaCoordenadas(TDAlistaCoordenadas* lista){
  if(!esListaCoordenadasVacia(*lista)){
    nodoCoordenadasPalabra *final, *anteriorFinal;
    final = *lista;
    anteriorFinal = NULL;
    while (final->puntero != NULL){ //buscamos ultimo nodo
      anteriorFinal = final;
      final = final->puntero;
    }
    anteriorFinal->puntero = NULL;
    free(final);
  }else{
    printf("No se puede eliminar un nodo coordendas de una lista vacia\n");
  }
}


/*Funcion que busca el nodo de una posicion especifica (comienza en 0) de una lista 
enlazada simple de coordendas y lo retorna
Entrada: TDAlistaChar, int posicion nodo
Salida: nodo* (puntero a nodo)*/
nodoCoordenadasPalabra* obtenerNodoListaCoordenadas(TDAlistaCoordenadas lista, int posicion){     //las posiciones desde el 0
  if(esListaCoordenadasVacia(lista)){
    printf("La lista esta vacia. No se puede obtener un nodo especifico.\n");
    return NULL;
  }
  if(posicion < 0){
    printf("La posicion debe ser un numero no negativo.\n");
    return NULL;
  }
  int conta = 0;
  nodoCoordenadasPalabra* auxiliar = lista;
  while(auxiliar != NULL){
    if(conta == posicion){
      return auxiliar; //retornamos el nodo que este en la posicion correcta
    }
    auxiliar = auxiliar->puntero;
    conta++;
  }
  printf("La posicion %d no se encontro en la lista.\n", posicion);
  return NULL;
}


/*Funcion que libera la memeoria utilizada por la lista enlazada de coordenadas
Entrada: TDAlistaCoordenadas puntero*/
void liberarListaCoordenadas(TDAlistaCoordenadas* lista){
  nodoCoordenadasPalabra* aux;
  while (!esListaCoordenadasVacia(*lista)){
    aux = *lista;
    *lista = (*lista)->puntero;
    free(aux);
  }
}