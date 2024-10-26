#include <stdio.h>
#include <stdlib.h>


/*Funcion que lee un archivo con la cantidad de elementos y numeros, creando un array apartir de el
Entrada: nombre del archivo, cadena de char (array referencia)
Salida: arreglo de enteros
*/
int* leerArchivo(char* nombreArchi, int* largo){

    FILE* archivo = fopen(nombreArchi, "r");
    if(archivo==NULL){
        printf("Error al abrir el archivo\n");//caso que no exista la ruta
        exit(1);
    }

    //leemos la primera linea, largo del arreglo
    int n;
    fscanf(archivo, "%d", &n);

    //creo un arragl dinamico
    int* array = (int*)malloc(sizeof(int)*n);

    //leo cada elemento y lo paso al array
    for(int i=0; i<n; i++){
        fscanf(archivo, "%d", &array[i]);
    }
    fclose(archivo);
    *largo = n;
    
    return array;
}

/*Funcion que ordena mediaente Burbuja un array de enteros
Entradas: array de enteros, largo array (int)
Salida: array de enteros ordenado*/
int* ordenamientoBurbuja(int* array,int n){
    int valor;
    //n es el largo del array
    for(int i=n-1; i>=0; i=i-1){
        for(int j=0;j<=i-1; j=j+1){
            if(array[j]>array[j+1]){
                valor = array[j];   //se usa una variable externa para relizar el intercambio entre array[j] y array[j+1]
                array[j]=array[j+1];
                array[j+1]=valor;
            }
        }
    }
    return array;
}

/*Funcion que busca un dato en un array numerico y entre un valor si lo encuentra o no lo encuentra
Entrada: array de enteros (int* ref direccion memoria), incio indice array (int), fin indice array (int), dato a buscar (int)
Salida: 1 si encuentra el dato, 0 si no lo encuentra*/
int busquedaBinariaRecursiva(int* array,int inicio, int fin, int dato){
    int centro = ((inicio + fin) / 2);

    // Comparar el número buscado con el elemento del centro
    if(array[centro] == dato){            // Si son iguales, se encontró el número
        return 1;
    }else if(inicio==fin){                  //condicion para de que no encontro el valor
        return 0;
    }else{
        if(array[centro]>dato){             //el pivote es mayor que el dato, se descarta el array de derecha
            return busquedaBinariaRecursiva(array, inicio, centro-1,dato);
        }else{                              //el pivote es menor que el dato, se descarta el array de la izquierda
            return busquedaBinariaRecursiva(array, centro+1, fin, dato);
        }
    }
}


/*Funcion que busca un dato en un array numerico y entre un valor si lo encuentra o no lo encuentra
Entrada: array de enteros, largo array (int), dato buscado (int)
Salida: (int) 0 no encuentra dato, 1 si lo encuentra*/
int busquedaBinariaIterativa(int* array, int largo_array, int numero_buscado) {             //FUNCION ITERATIVA, COMO PIDE LA ACTIVIDAD
    // Variables para almacenar los límites de la búsqueda
    int inicio = 0;
    int fin = largo_array - 1;

    // Mientras haya elementos donde buscar
    while (inicio <= fin) {
        // Calcular el punto medio del intervalo
        int medio = (inicio + fin) / 2;
        // Comparar el número buscado con el elemento del medio
        if (numero_buscado == array[medio]) {
            // Si son iguales, se encontró el número
            return 1;
        } else if (numero_buscado < array[medio]) {
            // Si el número buscado es menor, se descarta la mitad derecha
            fin = medio - 1;
        } else {
            // Si el número buscado es mayor, se descarta la mitad izquierda
            inicio = medio + 1;
        }
    }
    // Si se llega aquí, significa que no se encontró el número
    return 0;
}












/*Funcion que ordena un array de numeros mediante ordenamiento por insercion
Entradas: array de enteros, largo array (int)
Salida: array de enteros ordenado*/
int* ordenamientoInsercion(int* array, int n){
    int i,j,valor;
    for(i=1;i<=n-1;i++){
        j=i;
        while(j>=1 && array[j]<array[j-1]){
            valor = array[j];
            array[j] = array[j-1];
            array[j-1] = valor;
            j = j - 1;
        }
    }
    return array;

}


/*Funcion que busca un dato en un array numerico y entre un valor si lo encuentra o no lo encuentra
Entrada: array de enteros, largo array (int), dato a buscar (int)
Salida: (int) 0 no lo encuentra, 1 si lo encuentra*/
int busquedaSecuencial(int* array, int n, int dato){
    for(int i=0;i<=n;i++){
        if(array[i]==dato){
            return 1;           //si encuentra el dato
        }
    }
    return 0;                   //no encuentra el dato
}



void main(){
    char nombre[20];
    int largoArray, numBuscar, resultBusqueda;
    printf("Por favor ingrese el nombre del archivo para generar el array: ");
    scanf("%s",nombre);

    int* arrayleido = leerArchivo(nombre,&largoArray);

    printf("El array leido es:\n");
    for(int i = 0; i < largoArray; i++){
        printf("%d ", arrayleido[i]);
    }
    printf("\n");


    int* arrayOrdenadoBurbuja = ordenamientoBurbuja(arrayleido, largoArray);
    printf("\nEl array ordenado por burbuja es:\n");
    for(int i = 0; i < largoArray; i++){
        printf("%d ", arrayOrdenadoBurbuja[i]);
    }
    printf("\n");


    printf("\nPor favor, ingrese un numero a buscar por buscqueda binaria en el array (0 no lo encuentra, 1 lo encuentra): ");
    scanf("%d",&numBuscar);
    resultBusqueda = busquedaBinariaRecursiva(arrayOrdenadoBurbuja,0,largoArray-1,numBuscar);

    if(resultBusqueda==0){
        printf("El numero no esta en el array");
    }else if(resultBusqueda==1){
        printf("El nuemro si esta en el array");
    }


    int* arrayOrdenadoInsercion = ordenamientoInsercion(arrayleido,largoArray);
    printf("\n\n\nEl array ordenado por insercion es:\n");
    for(int i = 0; i < largoArray; i++){
        printf("%d ", arrayOrdenadoBurbuja[i]);
    }
    printf("\n");

    printf("\nPor favor, ingrese un numero a buscar por busqueda lineal en el array (0 no lo encuentra, 1 lo encuentra): ");
    scanf("%d",&numBuscar);
    resultBusqueda = busquedaSecuencial(arrayOrdenadoBurbuja,largoArray,numBuscar);

    if(resultBusqueda==0){
        printf("El numero no esta en el array");
    }else if(resultBusqueda==1){
        printf("El nuemro si esta en el array");
    }

}