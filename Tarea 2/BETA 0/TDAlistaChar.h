#include <stdio.h>
#include <stdlib.h>

//Estructura de datos TDA NODO
typedef struct nodoGenerico{
  char dato;
  struct nodoGenerico* puntero;
}nodo;

typedef nodo* TDAlistaChar;




//OPERACIONES
TDAlistaChar crearListaVacia(){
  TDAlistaChar lista = (TDAlistaChar)malloc(sizeof(TDAlistaChar));
  lista = NULL;
  return lista;
}


/*Funcion que comprueba si una lista enlazada simple esta vacia o no
Entrada: TDAlistaChar
Salida: int 1 (lista vacia), 0 (lista con elementos)*/
int esListaVacia(TDAlistaChar lista){
  if(lista == NULL)
    return 1;
  else
    return 0;
}


/*Funcion que imprime los elementos char de una lista enlazada simple
Entrada: TDAlistaChar*/
void recorrerLista(TDAlistaChar lista){
  if (!esListaVacia(lista)){
    nodo* auxiliar = lista;
    while (auxiliar != NULL){
      printf("%c ",auxiliar->dato);
      auxiliar = auxiliar->puntero;
    }
    printf("\n");
  }else
    printf("La lista esta vacia\n");
}

/*Funcion que entrega la cantidad de elementos/nodos de una lista enlazada simple
Entrada: TDAlistaChar
Salida: int cantidad nodos*/
int cantidadNodosLista(TDAlistaChar lista){
  if(!esListaVacia(lista)){
    int cantidad = 0;
    nodo* auxiliar = lista;
    while(auxiliar != NULL){
      cantidad ++;
      auxiliar = auxiliar->puntero;
    }
    return cantidad;
  }else{
    return 0;
  }
}



/*Funcion que inserta un nodo al inicio de una lista enlazada simple
Entrada: TDAlistaChar (referencia) puntero, char dato del nodo*/
void insertarNodoInicio(TDAlistaChar* lista, char dato){
  nodo* nuevo = (nodo*)malloc(sizeof(nodo));  //crearNodoVacio()
  nuevo->dato = dato;
  nuevo->puntero = *lista;
  *lista = nuevo;
}


/*Funcion que inserta un nodo al final de una lista enlazada simple
Entrada: TDAlistaChar (ref) puntero, char dato del nodo*/
void insertarNodoFinal(TDAlistaChar *lista, char valor){
  if(!esListaVacia(*lista)){
    nodo *final = *lista;
    while(final->puntero != NULL){
      final = final->puntero;
    }
    nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo)); //crearNodoVacio()
    nuevoNodo->dato = valor;
    nuevoNodo->puntero = NULL;
    final->puntero = nuevoNodo;
  }else{  //condicion para el caso en que se quiera insertar al final y sea lista vacia, evita error
    insertarNodoInicio(lista, valor);
  }
}


/*Funcion que inserta un nodo despues de un datoChar en una lista enlazada simple
Entrada: TDAlistaChar (ref) puntero, char dato nodo, char dato nodo anterior*/
void insertarNodoDespues(TDAlistaChar* lista, char dato, char datoAnterior){
  if(!esListaVacia(*lista)){
    nodo* anterior = *lista;
    //anterior != NULL condicion para no hacer en listas vacia
    while(anterior != NULL && anterior->dato != datoAnterior){
      anterior = anterior->puntero;
    }
    nodo* nuevoNodo = (nodo*)malloc(sizeof(nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->puntero = anterior->puntero;
    anterior->puntero = nuevoNodo;
  }else{
    printf("No se puede agregar un nodo despues de un dato en una lista vacia\n");
  }
}


/*Funcion que elimina el primer nodo de una lista enlazada simple
Entrada: TDAlistaChar (ref) puntero*/
void eliminarNodoInicio(TDAlistaChar* lista){
  if(!esListaVacia(*lista)){
    nodo* auxiliar;
    auxiliar = *lista;
    *lista = (*lista)->puntero;
    free(auxiliar);
  }else{
    printf("No se puede eliminar un nodo de una lista vacia\n");
  }
}


/*Funcion que elimina el ultimo nodo de una lista enlazada simple
Entrada: TDAlistaChar (ref) puntero*/
void eliminarNodoFinal(TDAlistaChar* lista){
  if(!esListaVacia(*lista)){
    nodo *final, *anteriorFinal;
    final = *lista;
    anteriorFinal = NULL;
    while (final->puntero != NULL){ //buscamos ultimo nodo
      anteriorFinal = final;
      final = final->puntero;
    }
    anteriorFinal->puntero = NULL;
    free(final);
  }else{
    printf("No se puede eliminar un nodo de una lista vacia\n");
  }
}


/*Funcion que elimina un nodo con un dato char especifico en una lista enlazada simple
Entrada: TDAlistaChar (ref) puntero, char dato a eliminar*/
void eliminarNodoDato(TDAlistaChar* lista, int dato){
  if(!esListaVacia(*lista)){
    nodo *indicado,*anteriorIndicado;
    indicado = *lista;
    anteriorIndicado = NULL;
    while (indicado->dato != dato){
        anteriorIndicado = indicado;
        indicado = indicado->puntero;
    }
    anteriorIndicado->puntero = indicado->puntero;
    free(indicado);
  }else{
    printf("No se puede eliminar un nodo de una lista vacia\n");
  }
}



/*Funcion que busca la posicion de un char en una lista enlazada simple,
en el caso que el char este mas de una vez, se retorna la primera aparicion
Entrada: TDAlistaChar, char dato buscado
Salida: int posicion dato (comienza de la posicion 0), int -1 (dato no encontrado)*/
int posicionDatoBuscadoLista(TDAlistaChar lista, char dato){
  if(!esListaVacia(lista)){
    nodo* actual = lista;
    int posicion = 0;
    while (actual != NULL) {
      if (actual->dato == dato) {
        return posicion; // Dato encontrado
      }
      posicion ++;
      actual = actual->puntero;
    }
    return -1; // Dato no encontrado, posicion -1
  }else{
    printf("No se puede buscar un dato de una lista vacia\n");
    return -1;
  }
}


/*Funcion que busca el nodo de una posicion especifica (comienza en 0) de una lista enlazada simple y lo retorna
Entrada: TDAlistaChar, int posicion nodo
Salida: nodo* (puntero a nodo)*/
nodo* obtenerNodo(TDAlistaChar lista, int posicion){      //las posiciones empiezan desde el 0
  if(esListaVacia(lista)){
    printf("La lista esta vacia. No se puede obtener un nodo especifico.\n");
    return NULL;
  }
  if(posicion < 0){
    printf("La posicion debe ser un numero no negativo.\n");
    return NULL;
  }
  int conta = 0;
  nodo* auxiliar = lista;
  while(auxiliar != NULL){
    if (conta == posicion){
      return auxiliar; //retornamos el nodo que este en la posicion correcta
    }
    auxiliar = auxiliar->puntero;
    conta++;
  }
  printf("La posicion %d no se encontro en la lista.\n", posicion);
  return NULL;
}


/*Funcion que libera la memeoria utilizada por la lista enlazada
Entrada: TDAlistaChar puntero*/
void liberarLista(TDAlistaChar* lista){
  nodo* aux;
  while (!esListaVacia(*lista)){
    aux = *lista;
    *lista = (*lista)->puntero;
    free(aux);
  }
}


/*Funcion que compara dos listas enlazadas simple
Entrada: TDAlista1, TDAlista2
Salida: 1 (listas iguales), 0 (listas distitas)*/
int compararListas(TDAlistaChar lista1, TDAlistaChar lista2){

  int numNodosL1 = cantidadNodosLista(lista1);
  int numNodosL2 = cantidadNodosLista(lista2);

  if(numNodosL1 == numNodosL2){  //listas mismo largo
    //ahora comparo las listas
    if (!esListaVacia(lista1)){
      nodo* auxL1 = lista1;
      nodo* auxL2 = lista2;
      while (auxL1 != NULL){
        if(auxL1->dato != auxL2->dato){
          return 0;
        }
        auxL1 = auxL1->puntero;
        auxL2 = auxL2->puntero;
      }
      return 1;
    }
  }
  else{ //listas distinto largo no son iguales
    return 0;
  }
}


/*Funcion que invierte los elementos de una lista enlazada
Entrada: TDA lista
Salida: TDA lista*/
TDAlistaChar listaInversa(TDAlistaChar lista){
  TDAlistaChar listaSalida = crearListaVacia();
  int cantNodos = cantidadNodosLista(lista);
  if (!esListaVacia(lista)){
    nodo* auxiliar = lista;
    while (auxiliar != NULL){
      insertarNodoInicio(&listaSalida, auxiliar->dato);
      auxiliar = auxiliar->puntero;
    }
  }else{
    printf("Es una lista vacia, no se puede invertir");
  }
  return listaSalida;
}


/*Funcion que intercambia los char de dos posiciones (empezando de la posicion 0) de una lista enlazada
Entradas: TDA lista puntero, posicion 1 int, posicion 2 int*/
void elementosCambiados(TDAlistaChar* lista, int posicion1, int posicion2){
  if(!esListaVacia(*lista)){
    int num1 = (obtenerNodo(*lista,posicion1))->dato;
    int num2 = (obtenerNodo(*lista,posicion2))->dato;
    int cantNodos = cantidadNodosLista(*lista);
    if(cantNodos>=posicion1 || cantNodos>=posicion2){
      printf("Las posiciones son invalidas\n");
    }
    nodo* aux = *lista;
    for(int i=0;i<cantNodos;i++){
      if(i==posicion1){
        aux->dato = num2;
      }
      if(i==posicion2){
        aux->dato = num1;
      }
      aux = aux->puntero;

    }
  }else if(posicion1<0 || posicion2<0){
    printf("Las posiciones son invalidas\n");
  }else{
    printf("Es una lista vacia, no se puede permutar elementos\n");
  }
}


/*Funcion que reemplaza un elemento de una posicion (desde el 0) de una lista enlazada simple de char
Entrada: TDAlistaChar puntero, int posicion, char caracter a cambiar*/
void reemplazarElementosListaChar(TDAlistaChar* lista, int posicion, char caracterNuevo){
  int cantNodos = cantidadNodosLista(*lista);
  nodo* aux = *lista;
  for(int i=0;i<cantNodos;i++){
    if(i == posicion){
      aux->dato = caracterNuevo;
      break;
    }
    aux = aux->puntero;
  }
}























//Estructura de datos TDA lista Char 2D, (idea - array de TDAlistaChar)

typedef struct nodoGenericoTDAlistaChar2D{
  TDAlistaChar dato;
  struct nodoGenericoTDAlistaChar2D* puntero;
}nodoTDAlistaChar;

typedef nodoTDAlistaChar* TDAlistaChar2D;



//OPERACIONES 

TDAlistaChar2D crearListaVacia2D(){
  TDAlistaChar2D lista2D = (TDAlistaChar2D)malloc(sizeof(TDAlistaChar2D));
  lista2D = NULL;
  return lista2D;
}


/*Funcion que comprueba si una lista enlazada simple 2D esta vacia o no
Entrada: TDAlistaChar2D
Salida: int 1 (lista vacia), 0 (lista con elementos)*/
int esListaVacia2D(TDAlistaChar2D lista2D){
  if(lista2D == NULL)
    return 1;
  else
    return 0;
}


/*Funcion que imprime los elementos char de una lista enlazada simple
Entrada: TDAlistaChar2D*/
void recorrerLista2D(TDAlistaChar2D lista2D){
  if (!esListaVacia2D(lista2D)){
    nodoTDAlistaChar* auxiliar = lista2D;
    while(auxiliar != NULL){
      nodo* aux2 = auxiliar->dato;
      while(aux2 != NULL){
        printf(" %c",aux2->dato);
        aux2 = aux2->puntero;
      }
      auxiliar = auxiliar->puntero;
      printf("\n");
    }
    printf("\n");
  }else
    printf("La lista 2D esta vacia\n");
}


/*Funcion que entrega la cantidad de elementos/nodos de una lista enlazada simple 2D
Entrada: TDAlistaChar2D
Salida: int cantidad nodos*/
int cantidadNodosLista2D(TDAlistaChar2D lista2D){
  if(!esListaVacia2D(lista2D)){
    int cantidad = 0;
    nodoTDAlistaChar* auxiliar = lista2D;
    while(auxiliar != NULL){
      cantidad ++;
      auxiliar = auxiliar->puntero;
    }
    return cantidad;
  }else{
    return 0;
  }
}


/*Funcion que inserta un nodo al inicio de una lista enlazada simple 2D
Entrada: TDAlistaChar2D (referencia) puntero, char dato del nodo*/
void insertarNodoInicio2D(TDAlistaChar2D* lista2D, TDAlistaChar dato){
  nodoTDAlistaChar* nuevo = (nodoTDAlistaChar*)malloc(sizeof(nodoTDAlistaChar));  //crearNodoVacio()
  nuevo->dato = dato;
  nuevo->puntero = *lista2D;
  *lista2D = nuevo;
}


/*Funcion que inserta un nodo al final de una lista enlazada simple 2D
Entrada: TDAlistaChar2D (ref) puntero, char dato del nodo*/
void insertarNodoFinal2D(TDAlistaChar2D *lista2D, TDAlistaChar dato){
  if(!esListaVacia2D(*lista2D)){
    nodoTDAlistaChar* final = *lista2D;
    while(final->puntero != NULL){  //llegamos al nodo final
      final = final->puntero;
    }
    nodoTDAlistaChar* nuevoNodo = (nodoTDAlistaChar*)malloc(sizeof(nodoTDAlistaChar));
    nuevoNodo->dato = dato;
    nuevoNodo->puntero = NULL;
    final->puntero = nuevoNodo;
  }else{
    insertarNodoInicio2D(lista2D, dato);
  }
}


/*Funcion que elimina el primer nodo de una lista enlazada simple 2D
Entrada: TDAlistaChar2D (ref) puntero*/
void eliminarNodoInicio2D(TDAlistaChar2D* lista2D){
  if(!esListaVacia2D(*lista2D)){
    nodoTDAlistaChar* auxiliar = *lista2D;
    *lista2D = (*lista2D)->puntero;
    free(auxiliar);
  }else{
    printf("No se puede eliminar un nodo de una lista vacia 2D\n");
  }
}


/*Funcion que elimina el ultimo nodo de una lista enlazada simple
Entrada: TDAlistaChar2D (ref) puntero*/
void eliminarNodoFinal2D(TDAlistaChar2D* lista2D){
  if(!esListaVacia2D(*lista2D)){
    nodoTDAlistaChar *final, *anteriorFinal;
    final = *lista2D;
    anteriorFinal = NULL;
    while (final->puntero != NULL){ //buscamos ultimo nodo
      anteriorFinal = final;
      final = final->puntero;
    }
    anteriorFinal->puntero = NULL;
    free(final);
  }else{
    printf("No se puede eliminar un nodo de una lista vacia 2D\n");
  }
}


