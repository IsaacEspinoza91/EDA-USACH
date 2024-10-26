#include <stdio.h>
#include <stdlib.h>


int** sumaMatricesCuadradas(int** A, int** B, int orden){

    // obtener orden de la matriz
    int n = orden;

    // asigno una nueva matriz nxn con elementos ceros
    int** matrizNueva = (int**)malloc(sizeof(int*)*n);
    for(int i=0;i<n;i=i+1){
        matrizNueva[i] = (int*)malloc(sizeof(int)*n);
    }
    for(int f=0;f<n;f=f+1){
        for(int c=0;c<n;c=c+1){
            matrizNueva[f][c] = 0;
        }
    }

    // sumar los valores de las matrices
    for(int f=0;f<n;f=f+1){
        for(int c=0;c<n;c=c+1){
            matrizNueva[f][c] = A[f][c]+B[f][c];
        }
    }
    return matrizNueva;

}


void main(){
    int n=2;

    // creacion matriz A
    int** A = (int**)malloc(sizeof(int*)*n);
    for(int i=0;i<n;i=i+1){
        A[i] = (int*)malloc(sizeof(int)*n);
    }
    A[0][0]=1;
    A[0][1]=0;
    A[1][0]=2;
    A[1][1]=2;
    /*  1  0
        2  2
    */

    // creacion matriz B
    int** B = (int**)malloc(sizeof(int*)*n);
    for(int i=0;i<n;i=i+1){
        B[i] = (int*)malloc(sizeof(int)*n);
    }
    B[0][0]=1;
    B[0][1]=0;
    B[1][0]=0;
    B[1][1]=1;
    /*  1  0
        0  1
    */

    int** resul = sumaMatricesCuadradas(A,B,n);
    printf("La matriz resultado es: \n\n");
    for(int i=0;i<n;i=i+1){
        for(int y=0;y<n;y=y+1){
            printf("  %i  ",resul[i][y]);
        }
        printf("\n");
    }

}