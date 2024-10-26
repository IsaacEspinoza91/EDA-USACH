#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodo
{
  int dato;
  struct nodo* puntero;
}nodo;

typedef nodo* TDAlista;

/*------------- operaciones -------------*/

TDAlista crearListaVacia()
{
  TDAlista lista=(TDAlista)malloc(sizeof(TDAlista));
  lista=NULL;
  return lista;
}

int esListaVacia(TDAlista lista)
{
  if (lista == NULL)
    return 1;
  else
    return 0;
}

void recorrerLista(TDAlista lista)
{
  if (!esListaVacia(lista))
  {
    nodo* auxiliar=lista;
    while (auxiliar!=NULL)
    {
      printf("%d ",auxiliar->dato);
      auxiliar=auxiliar->puntero;
    }
    printf("\n");
  }
  else
    printf("La lista está vacía\n");
}

void insertarInicio(TDAlista* lista, int dato)
{
  nodo* nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->dato=dato;
  nuevo->puntero=*lista;
  *lista=nuevo;
}

void eliminarInicio(TDAlista* lista)
{
  nodo* auxiliar;
  if(!esListaVacia(*lista))
  {
    auxiliar=*lista;
    *lista=(*lista)->puntero;
    free(auxiliar);
  }
}

/*------------- Actividad 1 -------------*/
int obtenerNumNodos(TDAlista lista){
  if (!esListaVacia(lista)){
   int cuenta=0;
   nodo* auxiliar=lista;
   while(auxiliar!=NULL){
    cuenta++;
    auxiliar=auxiliar->puntero;
   }
   return cuenta;
  }
  else{
    return 0;
  }
}

/*------------- Actividad 2 -------------*/
// Función para buscar un dato en la lista
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

/*------------- Actividad 3 -------------*/
void insertarNodoFinal(TDAlista *lista, int dato) {
    
    nodo *final = *lista;
    while (final->puntero != NULL) {
      final = final->puntero;
    }
    nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->puntero = NULL;
    final->puntero = nuevoNodo;
}


void insertarNodoDespues(TDAlista* lista, int dato, int datoAnterior) {
    nodo* anterior = *lista;
    while (anterior != NULL && anterior->dato != datoAnterior) {
        anterior = anterior->puntero;
    }
    nodo* nuevoNodo = (nodo*)malloc(sizeof(nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->puntero = anterior->puntero;
    anterior->puntero = nuevoNodo;
}


/*------------- Actividad 4 -------------*/
void eliminarFinal(TDAlista* lista) {
  nodo *final, *anteriorFinal;
  final = *lista;
  anteriorFinal = NULL;

  /* Recorremos la lista hasta encontrar el último nodo */
  while (final->puntero != NULL) {
    anteriorFinal = final;
    final = final->puntero;
  }
  anteriorFinal->puntero = NULL;

  /* Liberamos la memoria del nodo final */
  free(final);
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


/*------------- Actividad 5 -------------*/
nodo* obtenerNodo(TDAlista lista, int posicion)
{
  if (esListaVacia(lista))
  {
    printf("La lista está vacía. No se puede obtener un nodo en una posición específica.\n");
    return NULL;
  }

  if (posicion < 0)
  {
    printf("La posición debe ser un número no negativo.\n");
    return NULL;
  }

  int contador = 0;
  nodo* auxiliar = lista;

  while (auxiliar != NULL)
  {
    if (contador == posicion)
    {
      return auxiliar; // Se encontró el nodo en la posición deseada
    }
    auxiliar = auxiliar->puntero;
    contador++;
  }

  // Si la posición no se encuentra en la lista
  printf("La posición %d no se encontró en la lista.\n", posicion);
  return NULL;
}


//Actividad 1
/*Funcion que libera la memeoria utilizada por la lista enlazada
Entrada: TDAlista puntero*/
void liberarMemoria(TDAlista* lista)
{
  nodo* aux;
  while (!esListaVacia(*lista))
  {
    aux = *lista;
    *lista = (*lista)->puntero;
    free(aux);
  }

}



//Actividad 2
TDAlista sumaVecinos(TDAlista lista1)
{
  TDAlista listaSalida=crearListaVacia();
  if (!esListaVacia(lista1))
  {
    nodo* auxiliar = lista1;
    nodo* auxiliar2 = lista1;
    int cont = -1;
    while (auxiliar != NULL)
    {
      cont = cont + 1;
      auxiliar = auxiliar->puntero;
      if(auxiliar != NULL & cont>0) //condicion cont>0 es para que en el primer elemento no sume el anterior
      {
        insertarNodoFinal(&listaSalida, auxiliar->dato + auxiliar2->dato);
      }else if(cont==0)
      {
        insertarNodoFinal(&listaSalida, auxiliar->dato);     //caso primer elemento
      }else
      {
        insertarNodoFinal(&listaSalida, auxiliar2->dato);    //caso ultimo elemento
      }
      auxiliar2 = auxiliar2->puntero;
    }
  }
  return listaSalida;
}




//Actividad 3
/*Funcion que compara dos listas, devuelve 1 si son iguales
y devuelve 2 si no lo son
Entrada: TDAlista1, TDAlista2*/
int compararListas(TDAlista lista1, TDAlista lista2)
{
  int contadorL1 = 0, contadorL2 = 0;
  if (!esListaVacia(lista1))  //obtenemos largo lita 1
  {
    nodo* auxiliarL1 = lista1;
    while (auxiliarL1 != NULL)
    {
      contadorL1 = contadorL1 + 1;
      auxiliarL1 = auxiliarL1->puntero;
    }
  }

  if (!esListaVacia(lista2))  //obtenemos largo lista 2
  {
    nodo* auxiliarL2 = lista2;
    while (auxiliarL2 != NULL)
    {
      contadorL2 = contadorL2 + 1;
      auxiliarL2 = auxiliarL2->puntero;
    }
  }

  if(contadorL1 == contadorL2)  //caso en que las listas tengan el mismo largo
  {
    //ahora compardo las listas
    if (!esListaVacia(lista1))
    {
      nodo* auxL1 = lista1;
      nodo* auxL2 = lista2;
      while (auxL1 != NULL)
      {
        if(auxL1->dato != auxL2->dato)
        {
          return 0;
        }
        auxL1 = auxL1->puntero;
        auxL2 = auxL2->puntero;
      }
      return 1;
    }
  }
  else
  {
    return 0; //las listas no son iguales
  }

}