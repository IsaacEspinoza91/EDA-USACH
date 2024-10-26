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
