#include <stdio.h>
#include <stdlib.h>

//STRUCT TDA NODO
typedef struct nodoGenerico{
  int dato;
  struct nodoGenerico* puntero;
}nodo;

typedef nodo* TDAlista;


//OPERACIONES
TDAlista crearListaVacia(){
  TDAlista lista = (TDAlista)malloc(sizeof(TDAlista));
  lista = NULL;
  return lista;
}


/*Funcion que comprueba si una lista enlazada simple esta vacia o no
Entrada: TDAlista
Salida: int 1 (lista vacia), 0 (lista con elementos)*/
int esListaVacia(TDAlista lista){
  if(lista == NULL)
    return 1;
  else
    return 0;
}


/*Funcion que imprime los elementos int de una lista enlazada simple
Entrada: TDAlista*/
void recorrerLista(TDAlista lista){
  if (!esListaVacia(lista)){
    nodo* auxiliar = lista;
    while (auxiliar != NULL){
      printf("%d ",auxiliar->dato);
      auxiliar = auxiliar->puntero;
    }
    printf("\n");
  }else
    printf("La lista esta vacia\n");
}

/*Funcion que entrega la cantidad de elementos/nodos de una lista enlazada simple
Entrada: TDAlista
Salida: int cantidad nodos*/
int cantidadNodosLista(TDAlista lista){
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

/*Funcion que entrega el promedio simple de los datos de una lista enlazada simple
Entrada: TDAlista
Salida: flotante*/
float promedioSimpleNumLista(TDAlista lista){
  if(!esListaVacia(lista)){
    float cantidad = 0;
    float sumaElementos = 0;
    nodo* auxiliar=lista;
    while(auxiliar != NULL){
      cantidad ++;
      sumaElementos = sumaElementos + auxiliar->dato;
      auxiliar = auxiliar->puntero;
    }
    return (sumaElementos/cantidad);
  }else{
    return 0;
  }
}

/*Funcion que inserta un nodo al inicio de una lista enlazada simple
Entrada: TDAlista (referencia) puntero, int dato del nodo*/
void insertarNodoInicio(TDAlista* lista, int dato){
  nodo* nuevo = (nodo*)malloc(sizeof(nodo));  //crearNodoVacio()
  nuevo->dato = dato;
  nuevo->puntero = *lista;
  *lista = nuevo;
}


/*Funcion que inserta un nodo al final de una lista enlazada simple
Entrada: TDAlista (ref) puntero, int dato del nodo*/
void insertarNodoFinal(TDAlista *lista, int valor){
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


/*Funcion que inserta un nodo despues de un datoNum en una lista enlazada simple
Entrada: TDAlista (ref) puntero, int dato nodo, int dato nodo anterior*/
void insertarNodoDespues(TDAlista* lista, int dato, int datoAnterior){
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
Entrada: TDAlista (ref) puntero*/
void eliminarNodoInicio(TDAlista* lista){
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
Entrada: TDAlista (ref) puntero*/
void eliminarNodoFinal(TDAlista* lista){
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


/*Funcion que elimina un nodo con un dato num especifico en una lista enlazada simple
Entrada: TDAlista (ref) puntero, int dato a eliminar*/
void eliminarNodoDato(TDAlista* lista, int dato){
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


/*Funcion que verifica si un dato int esta en una lista enlazada simple,
Entrada: TDAlista, int dato a buscar
Salida: int 1 (dato encontrado), 0 (dato no encontrado)*/
int buscarDatoLista(TDAlista lista, int dato){
  if(!esListaVacia(lista)){
    nodo* actual = lista;
    while (actual != NULL) {
      if (actual->dato == dato) {
        return 1; // Dato encontrado
      }
      actual = actual->puntero;
    }
    return 0; // Dato no encontrado
  }else{
    printf("No se puede buscar un dato de una lista vacia\n");
    return 0;
  }
}

/*Funcion que busca la posicion de un numero en una lista enlazada simple,
en el caso que el numero este mas de una vez, se retorna la primera aparicion
Entrada: TDAlista, int dato buscado
Salida: int posicion dato (comienza de la posicion 0), int -1 (dato no encontrado)*/
int posicionDatoBuscadoLista(TDAlista lista, int dato){
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
Entrada: TDAlista, int posicion nodo
Salida: nodo* (puntero a nodo)*/
nodo* obtenerNodo(TDAlista lista, int posicion){      //las posiciones empiezan desde el 0
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
Entrada: TDAlista puntero*/
void liberarLista(TDAlista* lista){
  nodo* aux;
  while (!esListaVacia(*lista)){
    aux = *lista;
    *lista = (*lista)->puntero;
    free(aux);
  }
}


/*Funcion que suma los datos del nodo anterior y el nodo siguiente en cada nodo de una lista nueva
Entrada: TDA lista
Salida: TDA lista*/
TDAlista sumaVecinos(TDAlista lista1){
  TDAlista listaSalida=crearListaVacia();
  int cantNodos = cantidadNodosLista(lista1);

  if(cantNodos==1)
    return lista1;    //solo en el caso de una lista de 1 elemento, queda igual
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
      insertarNodoInicio(&listaSalida, sumaParcial);
    }else{
      insertarNodoFinal(&listaSalida, sumaParcial);
    }
  }

  return listaSalida;
}


/*Funcion que compara dos listas enlazadas simple
Entrada: TDAlista1, TDAlista2
Salida: 1 (listas iguales), 0 (listas distitas)*/
int compararListas(TDAlista lista1, TDAlista lista2){

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


/*Funcion que invierte los numeros de una lista enlazada
Entrada: TDA lista
Salida: TDA lista*/
TDAlista listaInversa(TDAlista lista){
  TDAlista listaSalida = crearListaVacia();
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


/*Funcion que intercambia los numeros de dos posiciones (empezando de la posicion 0) de una lista enlazada
Entradas: TDA lista, posicion 1 int, posicion 2 int*/
void elementosCambiados(TDAlista* lista, int posicion1, int posicion2){
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