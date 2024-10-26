#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"

void main()
{
  
  //PROBANDO TDA LISTA ENLAZADA SIMPLE

  TDAlista lista = crearListaVacia();

  insertarNodoFinal(&lista,2022);
  insertarNodoInicio(&lista,4);
  insertarNodoInicio(&lista,1);
  insertarNodoInicio(&lista,3);
  insertarNodoInicio(&lista,2);
  //insertarNodoFinal(&lista, 99);

  recorrerLista(lista);

  //insertarNodoDespues(&lista, 77,4);
  insertarNodoDespues(&lista, 77,2022);

  recorrerLista(lista);

  eliminarNodoDato(&lista,4);
  eliminarNodoDato(&lista, 77);
  recorrerLista(lista);

  printf("la lista tiene %i elementos\n",cantidadNodosLista(lista));
  printf("el numero 2022 esta?   %i\n", buscarDatoLista(lista, 2022));

  int posix = posicionDatoBuscadoLista(lista,2022);
  printf( "el 2022 esta en la posicion %i\n\n",posix);
  nodo* nodoBUscado = obtenerNodo(lista,posix);
  printf(" el nodo buscado del 2022 es      posicion: %i", nodoBUscado->dato);

}
