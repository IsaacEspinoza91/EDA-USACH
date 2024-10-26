#include <stdio.h>
#include <stdlib.h>

//Actividad 2: muestra el valor del menor elemento de un arreglo
void menorArreglo(int* arregloA, int n){
	int i = 0;
	int valor = arregloA[0];
	for(int i=0;i<n;i=i+1){
		if(arregloA[i]<valor){
			valor=arregloA[i];
		}
	}
	printf(" El menor valor del arreglo es %d\n\n",valor);
};

//Actividad 3: muestra la suma de los elementos de un arreglo 
void sumaArreglo(int* arregloA, int n){
	int suma = 0;
	for(int i=0;i<n;i=i+1){
		suma = suma + arregloA[i];
	}
	printf(" La suma de los valores del arreglo es %d \n\n",suma);
};
	
//Actividad 4: devuelve el promedio de los elementos de un arreglo 
float promedioArreglo(int* arregloA, int n){
	float suma = 0;
	for(int i=0;i<n;i=i+1){
		suma = suma + arregloA[i];
	}
	float prom = suma/n;
	return prom;
};


int main()
{
	FILE * archivo; //puntero a tipo FILE
	//modo lectura
	archivo =fopen("entrada_arreglo1.in","r");
	
	int cantmax, elemento,i;	
	
	fscanf(archivo, "%d", &cantmax); 
	int arreglolab1[cantmax];
	printf("cantidad de elementos %d \n", cantmax);
	
	//lee los elementos de un arreglo desde un archivo
	for(i=0;i<cantmax;i++)
	{
		fscanf(archivo,"%d",&elemento);
		arreglolab1[i]=elemento;
	}
	fclose(archivo);
	
	//muestra los elementos del arreglo	
	for (i=0; i<cantmax; ++i)
	{
		printf("%d\t",arreglolab1[i]);
	}
	printf("\n");



	menorArreglo(arreglolab1,cantmax);
	sumaArreglo(arreglolab1,cantmax);
	printf("\nEl promedio es %f",promedioArreglo(arreglolab1,cantmax));
	
	return 0;
}