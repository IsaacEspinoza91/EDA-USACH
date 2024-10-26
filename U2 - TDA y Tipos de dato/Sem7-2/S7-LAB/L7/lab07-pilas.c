#include <stdio.h>
#include <stdlib.h>
#include "TDApila.h"

int main()
{
  
  /*------------- Actividad 6 -------------*/


  /*ACT 1*/
  //creamos pila vacia de capcidad 8
  TDApila* pila1 = crearPilaVacia(8);

  //verificar si la pila creada esta vacia
  int resulPilaVacia = esPilaVacia(pila1);
  if(resulPilaVacia == 1){
    printf("\nLa pila esta vacia\n");
  }else{
    printf("\nLa pila NO esta vacia\n");
  }


  /*ACT 2*/



  /*ACT 3*/
  //crear la pila (tope) 8 5 9 6 2, u despues de apilar cada dato se muestra el tope
  printf("\nAct 3\nApilando datos en la pila\n\n");
  
  apilar(pila1,2);
  printf("El dato es %d\n",tope(pila1)->dato);
  apilar(pila1,6);
  printf("El dato es %d\n",tope(pila1)->dato);
  apilar(pila1,9);
  printf("El dato es %d\n",tope(pila1)->dato);
  apilar(pila1,5);
  printf("El dato es %d\n",tope(pila1)->dato);
  apilar(pila1,8);
  printf("El dato es %d\n",tope(pila1)->dato);


  /*ACT 4*/
  //crear la pila (tope) 8 5 9 6 2, u despues de apilar cada dato se muestra el tope
  printf("\nAct 4\nDesapilando datos en la pila\n\n");
  
  printf("El dato tope es %d\n",tope(pila1)->dato);
  desapilar(pila1);
  printf("El dato tope es %d\n",tope(pila1)->dato);
  desapilar(pila1);
  printf("El dato tope es %d\n",tope(pila1)->dato);
  desapilar(pila1);
  printf("El dato tope es %d\n",tope(pila1)->dato);
  desapilar(pila1);
  printf("El dato tope es %d\n",tope(pila1)->dato);
  desapilar(pila1);     //si en este punto se vuelve a desapilar, se muestra un mensaje que dice que ya no es posible

  return 0;
}
