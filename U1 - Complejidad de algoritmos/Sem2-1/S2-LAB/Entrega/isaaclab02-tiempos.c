#include <stdio.h>
#include <time.h>
#include <stdlib.h>

long potenciaIterativa(int base, int exponente){
	int resultado = 1;
	int i = 1;
	if(exponente==0){
		return resultado;
	}
	while(i<=exponente){
		resultado = resultado*base;
		i = i + 1;
	}
	return resultado;
};

long potenciaRecursiva(int base, int exponente){
	if(exponente==0){
		return 1;
	}else{
		return base*potenciaRecursiva(base,exponente-1);
	}
};

int main (int argc, char * argv[]){

	/*
	int a,b;
	a = 5;
	b = 7;
	printf("%i elevado a %i es %ld        iterativo\n\n",a,b,potenciaIterativa(a,b));
	printf("%i elevado a %i es %ld        recursivo\n\n",a,b,potenciaRecursiva(a,b));
	*/
	
	int base=atoi(argv[1]);
	int exponente=atoi(argv[2]);
	long potIt=0, potRe=0;
	clock_t ciniIt, cfinIt, ciniRe, cfinRe;
	double tiempoIt, tiempoRe;
	
	ciniIt=clock();
	potIt=potenciaIterativa(base,exponente);
	cfinIt=clock();
		
	ciniRe=clock();
	potRe=potenciaRecursiva(base,exponente);
	cfinRe=clock();
			
	tiempoIt= (double)(cfinIt-ciniIt)/CLOCKS_PER_SEC;
	tiempoRe= (double)(cfinRe-ciniRe)/CLOCKS_PER_SEC;

	printf(" %i^%i		%ld		%f		%ld		%f\n\n",base,exponente,potIt,tiempoIt,potRe,tiempoRe);
	
	return 1;	
} 

