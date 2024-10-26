#include <stdio.h>
#include <stdlib.h>
#include "TDAlistaInt.h"

void main(){
  
  //PROBANDO TDA LISTA ENLAZADA SIMPLE

  TDAlista lista = crearListaVacia();


  insertarNodoFinal(&lista,2022);
  insertarNodoFinal(&lista, 1);
  insertarNodoFinal(&lista, 123);


  recorrerLista(lista);

  elementosCambiados(&lista, 2,1);
  recorrerLista(lista);

  


}
