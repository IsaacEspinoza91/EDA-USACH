#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"

int main()
{
  TDAlista lista=crearListaVacia();

  //L%
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






  //L6

  //Creamos lista para probar liberarMemoria
  TDAlista listax=crearListaVacia();
  insertarInicio(&listax, 99);
  insertarInicio(&listax, 4);
  insertarInicio(&listax, 1);
  liberarMemoria(&listax);



  //probamos sumar vecinos
  printf("\nlista original:  ");
  recorrerLista(lista);
  TDAlista listaVecinos = sumaVecinos(lista);
  printf("\n\nlista vecinos sumados:  ");
  recorrerLista(listaVecinos);







  //creamos lista2 para probar funciones
  TDAlista lista2=crearListaVacia();
  insertarInicio(&lista2, 99);
  insertarInicio(&lista2, 4);
  insertarInicio(&lista2, 1);
  insertarInicio(&lista2, 3);
  insertarInicio(&lista2, 2);

  printf("\n\nLab 6\nLas listas a comparar son :\n");
  recorrerLista(lista);
  recorrerLista(lista2);






  //comparar listas
  int k = compararListas(lista, lista2);
  printf("\n Resultado comparacion de listas %d\n",k);





  //lista inversa no sea weon

  return 1;
}