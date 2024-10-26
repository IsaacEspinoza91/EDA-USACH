#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"

int main()
{
  TDAlista lista=crearListaVacia();


  /*ACTIVIDAD 1*/
  //insertar al incio nodos en el siguiente orden: 4,1,3,2
  insertarInicio(&lista, 4);
  insertarInicio(&lista, 1);
  insertarInicio(&lista, 3);
  insertarInicio(&lista, 2);

  //recorremos lista resultante
  recorrerLista(lista);

  //eliminar nodod al inicio
  eliminarInicio(&lista);

  //recorremos lista resultante
  recorrerLista(lista);

  //insertar al inicio nodo con valor 2
  insertarInicio(&lista, 2);

  //recorremos lista resultante
  recorrerLista(lista);



  //obtener cantidad de nodos
  int numNodos = obtenerNumNodos(lista);
  printf("La lista tiene %i nodos\n",numNodos);

  //verificar si un dato esta en la lista
  buscarDatoLista(lista, 7);
  buscarDatoLista(lista, 1);

  //insertar nodo al final
  insertarNodoFinal(&lista, 99);  

  return 1;
}