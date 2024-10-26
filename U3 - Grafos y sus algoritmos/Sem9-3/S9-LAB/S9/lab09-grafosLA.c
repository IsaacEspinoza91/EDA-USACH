#include <stdio.h>
#include <stdlib.h>
#include "TDAGrafoLA.h"
#include "TDAlistaInt.h"
#include "TDApilaInt.h"
#include "TDAcolaInt.h"

int main() 
{
    TDAGrafoLA* grafo = leerGrafoNoDirigido("grafoND-NP.ini");

    imprimirListaAdyacencia(grafo);

    TDAlista verticesAdyaA2 = obtenerAdyacentes(grafo, 2);
    recorrerLista(verticesAdyaA2);

 	return 0;
}
