#include <stdio.h>
#include <stdlib.h>

//STRUCT TDA NODO
typedef struct nodo
{
  int dato;
  struct nodo* puntero;
}nodo;

typedef nodo* TDAlista;


//OPERACIONES
TDAlista crearListaVacia(){
  TDAlista lista=(TDAlista)malloc(sizeof(TDAlista));
  lista=NULL;
  return lista;
}


int esListaVacia(TDAlista lista){
  if (lista == NULL)
    return 1;
  else
    return 0;
}


void recorrerLista(TDAlista lista){
  if (!esListaVacia(lista)){
    nodo* auxiliar=lista;
    while (auxiliar!=NULL){
      printf("%d ",auxiliar->dato);
      auxiliar=auxiliar->puntero;
    }
    printf("\n");
  }else
    printf("La lista está vacía\n");
}


void insertarInicio(TDAlista* lista, int dato){
  nodo* nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->dato=dato;
  nuevo->puntero=*lista;
  *lista=nuevo;
}


void eliminarInicio(TDAlista* lista){
  nodo* auxiliar;
  if(!esListaVacia(*lista)){
    auxiliar=*lista;
    *lista=(*lista)->puntero;
    free(auxiliar);
  }
}


int obtenerNumNodos(TDAlista lista){
  if (!esListaVacia(lista)){
    int cuenta=0;
    nodo* auxiliar=lista;
    while(auxiliar!=NULL){
      cuenta++;
      auxiliar=auxiliar->puntero;
    }
    return cuenta;
  }else{
    return 0;
  }
}


int buscarDatoLista(TDAlista lista, int dato){
  nodo* actual = lista;
  while (actual != NULL) {
    if (actual->dato == dato) {
      return 1; // Dato encontrado
    }
    actual = actual->puntero;
  }
  return 0; // Dato no encontrado
}


void insertarNodoFinal(TDAlista *lista, int valor){
  nodo *final = *lista;
  while(final->puntero != NULL){
    final = final->puntero;
  }
  nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo));
  nuevoNodo->dato = valor;
  nuevoNodo->puntero = NULL;
  final->puntero = nuevoNodo;
}


void insertarNodoDespues(TDAlista* lista, int dato, int datoAnterior){
  nodo* anterior = *lista;
  while (anterior != NULL && anterior->dato != datoAnterior){
    anterior = anterior->puntero;
  }
  nodo* nuevoNodo = (nodo*)malloc(sizeof(nodo));
  nuevoNodo->dato = dato;
  nuevoNodo->puntero = anterior->puntero;
  anterior->puntero = nuevoNodo;
}


void eliminarFinal(TDAlista* lista) {
  nodo *final, *anteriorFinal;
  final = *lista;
  anteriorFinal = NULL;
  while (final->puntero != NULL){ //buscamos ultimo nodo
    anteriorFinal = final;
    final = final->puntero;
  }
  anteriorFinal->puntero = NULL;
  free(final);  //liberamos memoria ultimo nodo
}


void eliminarDato(TDAlista* lista, int dato){
 nodo *indicado,*anteriorIndicado;
 indicado = *lista;
 anteriorIndicado = NULL;
 while (indicado->dato != dato){
    anteriorIndicado = indicado;
    indicado = indicado->puntero;
 }
 anteriorIndicado->puntero = indicado->puntero;
 free(indicado);
}


nodo* obtenerNodo(TDAlista lista, int posicion){      //las pociones empiezan desde el 0
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

  while (auxiliar != NULL){
    if (conta == posicion){
      return auxiliar; //retornamos el nodo que este en la posicion correcta
    }
    auxiliar = auxiliar->puntero;
    conta++;
  }

  printf("La posicion %d no se encontro en la lista.\n", posicion);
  return NULL;
}


//Actividad 1 L6
/*Funcion que libera la memeoria utilizada por la lista enlazada
Entrada: TDAlista puntero*/
void liberarLista(TDAlista* lista){
  nodo* aux;
  while (!esListaVacia(*lista)){
    aux = *lista;
    *lista = (*lista)->puntero;
    free(aux);
  }
}



//Actividad 2 L6
/*Funcion que suma los datos del nodo anterior y el nodo siguiente en cada nodo de una lista nueva
Entrada: TDA lista
Salida: TDA lista*/
TDAlista sumaVecinos(TDAlista lista1){
  TDAlista listaSalida=crearListaVacia();

  int cantNodos = obtenerNumNodos(lista1);

  if(cantNodos==1){
    return lista1;    //solo en el caso de una lista de 1 elemento, queda igual
  }
  for(int k=0;k<cantNodos;k++){

    nodo* nodoAnte;
    nodo* nodoSigui;
    int sumaParcial = 0;

    //Determinar nodo anterior
    if(k == 0){    //caso primer elemento, solo sumo el dato siguiente
      nodoAnte->dato = 0;
    }else{
      nodoAnte = obtenerNodo(lista1,k-1);
    }

    //Determinar nodo siguiente
    if(k ==cantNodos -1){
      nodoSigui->dato = 0;
    }else{
      nodoSigui = obtenerNodo(lista1,k+1);
    }

    sumaParcial = sumaParcial + nodoAnte->dato + nodoSigui->dato;

    if(k==0){ //solo en el caso que sea el primer dato, se debe insertar en el inicio, los demas al final.
      insertarInicio(&listaSalida, sumaParcial);
    }else{
      insertarNodoFinal(&listaSalida, sumaParcial);
    }
  }

  return listaSalida;
}




//Actividad 3 L6
/*Funcion que compara dos listas, devuelve 1 si son iguales y devuelve 2 si no lo son
Entrada: TDAlista1, TDAlista2
Salida: 1 (listas iguales), 2 (listas distitas)*/
int compararListas(TDAlista lista1, TDAlista lista2){

  int numNodosL1 = obtenerNumNodos(lista1);
  int numNodosL2 = obtenerNumNodos(lista2);

  if(numNodosL1 == numNodosL2){  //caso en que las listas tengan el mismo largo
    //ahora compardo las listas
    if (!esListaVacia(lista1)){
      nodo* auxL1 = lista1;
      nodo* auxL2 = lista2;
      while (auxL1 != NULL){
        if(auxL1->dato != auxL2->dato){   //si los datos llegan a ser diferentes, retorno 0
          return 0;
        }
        auxL1 = auxL1->puntero;
        auxL2 = auxL2->puntero;
      }
      return 1; //caso que iteramos en los datos de las listas y no son diferentes
    }
  }
  else{ //si las listas no tienen el mismo largo no son iguales
    return 0;
  }
}

//Actividad 4 L6
/*Funcion que invierte los numeros de una lista enlazada
Entrada: TDA lista
Salida: TDA lista*/
TDAlista listaInversa(TDAlista lista){
  TDAlista listaSalida = crearListaVacia();
  int cantNodos = obtenerNumNodos(lista);

  if (!esListaVacia(lista)){
    nodo* auxiliar=lista;
    while (auxiliar!=NULL){
      insertarInicio(&listaSalida, auxiliar->dato);
      auxiliar=auxiliar->puntero;
    }
  }else{
    printf("Es una lista vacia. No se puede invertir");
  }
  return listaSalida;
}

//Actividad 5 L6
/*Funcion que intercambia los numeros de dos posiciones (empezando de la posicion 0) de una lista enlazada
Entradas: TDA lista, posicion 1 int, posicion 2 int*/
void elementoCambiados(TDAlista* lista, int posicion1, int posicion2){

  int num1 = (obtenerNodo(*lista,posicion1))->dato;
  int num2 = (obtenerNodo(*lista,posicion2))->dato;
  int cantNodos = obtenerNumNodos(*lista);
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

}