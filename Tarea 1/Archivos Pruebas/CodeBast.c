#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define largo 50 // largo de la palabra
#define capacidad 100 // capacidad de la matriz

typedef struct {
    int fila;
    int columna;
} Coordenada;


void guarda_matriz(FILE *archivo, char matriz[capacidad][capacidad], int filas, int columnas)  //obtener la matriz a guardar 
	{for (int i = 0; i < filas; i++) 
		{for (int j = 0; j < columnas; j++) 
		{fprintf(archivo, "%c ", matriz[i][j]);}
        	fprintf(archivo, "\n");}
    	fprintf(archivo, "\n");}


void buscador(char matriz[capacidad][capacidad], int filas, int columnas, char palabra[largo], Coordenada *coordenadas, FILE *archivo_matriz) {  //funcion para buscar
    int longitud = strlen(palabra);

	for (int i = 0; i < filas; i++)                  // bucle para pasearme por la matriz elemento x elemento
		{for (int j = 0; j < columnas; j++) 
            {if (j + longitud <= columnas)  // ver si es posible buscar horizontamente 
                {int encontrado = 1;
                
                for (int k = 0; k < longitud; k++) 	 //busca horzontamente 
                    {if (matriz[i][j + k] != palabra[k]) 
                        {encontrado = 0;
                                break;}
                    }
                            
                    if (encontrado)    // Marcar la palabra con "*" en la matriz
                        {for (int k = 0; k < longitud; k++) 
                            {matriz[i][j + k] = '*';}
                        guarda_matriz(archivo_matriz, matriz, filas, columnas);
                        for (int k = 0; k < longitud; k++) 
                            {matriz[i][j + k] = palabra[k];}
                        

                    
                            coordenadas->fila = i + 1;      //guardar las coordenadas de la respuesta
                            coordenadas->columna = j + 1;
                        return;}
                }

            if (j  + longitud <= columnas && i + longitud <= filas) // ver si es posible blucar diagonal
                {int encontrado = 1;

                for (int k = 0; k < longitud; k++)   // buscar diagonalmente
                    {if (matriz[i + k][j + k] != palabra[k]) 
                        {encontrado = 0;
                        break;}
                    }
                    

                if (encontrado) 
                    {for (int k = 0; k < longitud; k++)  /// Marcar la palabra con "*" en la matriz
                        {matriz[i + k][j + k] = '*';}
                    guarda_matriz(archivo_matriz, matriz, filas, columnas);
                    for (int k = 0; k < longitud; k++) 
                        {matriz[i + k][j + k] = palabra[k];}

                        coordenadas->fila = i + 1; // Almacenar las coordenadas de la primera ocurrencia
                        coordenadas->columna = j + 1;
                    return;}
                }
            
            if (j  + longitud <= columnas && i + longitud <= filas) // ver si es posible blucar diagonal
                {int encontrado = 1;

                for (int k = 0; k < longitud; k++)   // buscar diagonalmente
                    {if (matriz[i + k][j + k] != palabra[k]) 
                        {encontrado = 0;
                        break;}
                    }
                    

                if (encontrado) 
                    {for (int k = 0; k < longitud; k++)  /// Marcar la palabra con "*" en la matriz
                        {matriz[i + k][j - k] = '*';}
                    guarda_matriz(archivo_matriz, matriz, filas, columnas);
                    for (int k = 0; k < longitud; k++) 
                        {matriz[i + k][j - k] = palabra[k];}

                        coordenadas->fila = i + 1; // Almacenar las coordenadas de la primera ocurrencia
                        coordenadas->columna = j + 1;
                    return;}
                }


            if (i + longitud <= filas)        // ver si es posible buscar verticalmente 
                {int encontrado = 1; 
                    
                    for (int k = 0; k < longitud; k++) //buscar vertical
                        {if (matriz[i + k][j] != palabra[k]) 
                            {encontrado = 0;
                                break;
                            }
                        }
                
                
                    if (encontrado) // Marcar la palabra con "*" en la matriz
                        {for (int k = 0; k < longitud; k++)   
                            {matriz[i + k][j] = '*';}
                        guarda_matriz(archivo_matriz, matriz, filas, columnas);
                        for (int k = 0; k < longitud; k++) 
                            {matriz[i + k][j] = palabra[k];}
        
                        coordenadas->fila = i + 1;      //guardar las coordenadas de la respuesta
                        coordenadas->columna = j + 1;
                    return;}
                }
            }
        }
    


    char palabra_reves[largo];     // Buscar la palabra al revés
    for (int i = 0; i < longitud; i++) {
        palabra_reves[i] = palabra[longitud - i - 1]; //ve la palabra en orden inverso y las almacena
    }
    palabra_reves[longitud] = '\0'; //caracter nulo, llegar al final de la cadena

	for (int i = 0; i < filas; i++)                  // bucle para pasearme por la matriz elemento x elemento
		{for (int j = 0; j < columnas; j++) 
            {if (j + longitud <= columnas)  // ver si es posible buscar horizontamente 
                {int encontrado = 1;
                
                for (int k = 0; k < longitud; k++) 	 //busca horzontamente 
                    {if (matriz[i][j + k] != palabra_reves[k]) 
                        {encontrado = 0;
                                break;}
                    }
                            
                    if (encontrado)    // Marcar la palabra con "*" en la matriz
                        {for (int k = 0; k < longitud; k++) 
                            {matriz[i][j + k] = '*';}
                        guarda_matriz(archivo_matriz, matriz, filas, columnas);
                        for (int k = 0; k < longitud; k++) 
                            {matriz[i][j + k] = palabra_reves[k];}
                        

                    
                            coordenadas->fila = i + 1;      //guardar las coordenadas de la respuesta
                            coordenadas->columna = j + largo;
                        return;}
                }

            if (j  + longitud <= columnas && i + longitud <= filas) // ver si es posible blucar diagonal
                {int encontrado = 1;



                for (int k = 0; k < longitud; k++)   // buscar diagonalmente
                    {if (matriz[i + k][j + k] != palabra_reves[k]) 
                        {encontrado = 0;
                        break;}
                    }
                    

                if (encontrado) 
                    {for (int k = 0; k < longitud; k++)  /// Marcar la palabra con "*" en la matriz
                        {matriz[i + k][j + k] = '*';}
                    guarda_matriz(archivo_matriz, matriz, filas, columnas);
                    for (int k = 0; k < longitud; k++) 
                        {matriz[i + k][j + k] = palabra_reves[k];}

                        coordenadas->fila = i + largo; // Almacenar las coordenadas de la primera ocurrencia
                        coordenadas->columna = j + largo;
                    return;}
                }
            
            if (j  + longitud <= columnas && i + longitud <= filas) // ver si es posible blucar diagonal
                {int encontrado = 1;

                for (int k = 0; k < longitud; k++)   // buscar diagonalmente
                    {if (matriz[i + k][j + k] != palabra_reves[k]) 
                        {encontrado = 0;
                        break;}
                    }
                    

                if (encontrado) 
                    {for (int k = 0; k < longitud; k++)  /// Marcar la palabra con "*" en la matriz
                        {matriz[i + k][j - k] = '*';}
                    guarda_matriz(archivo_matriz, matriz, filas, columnas);
                    for (int k = 0; k < longitud; k++) 
                        {matriz[i + k][j - k] = palabra_reves[k];}

                        coordenadas->fila = i + largo; // Almacenar las coordenadas de la primera ocurrencia
                        coordenadas->columna = j - largo  + 2;
                    return;}
                }


            if (i + longitud <= filas)        // ver si es posible buscar verticalmente 
                {int encontrado = 1; 
                    
                    for (int k = 0; k < longitud; k++) //buscar vertical
                        {if (matriz[i + k][j] != palabra_reves[k]) 
                            {encontrado = 0;
                                break;
                            }
                        }
                
                
                    if (encontrado) // Marcar la palabra con "*" en la matriz
                        {for (int k = 0; k < longitud; k++)   
                            {matriz[i + k][j] = '*';}
                        guarda_matriz(archivo_matriz, matriz, filas, columnas);
                        for (int k = 0; k < longitud; k++) 
                            {matriz[i + k][j] = palabra_reves[k];}
        
                        coordenadas->fila = i + largo;      //guardar las coordenadas de la respuesta
                        coordenadas->columna = j + 1;
                    return;}
                }
            }
        }
    

}






int main() {
    char nombre_archivo[100]; //guardar le nombre del archivo
    int k; // Cantidad de palabras
    int filas, columnas, contador;
    clock_t inicio, fin;
    double tiempo;
    
    

    inicio = clock();
    printf("Ponga el nombre del archivo ->(.ini): ");
    scanf("%s", nombre_archivo);         //leer el nombre del archivo
    FILE *archivo = fopen(nombre_archivo, "r"); //abrir el archivo

    if (archivo == NULL)   //error al abrir el archivo
    {printf("no se pudo abrir el archivo .ini\n");  
        return 1;}

    fscanf(archivo, "%d %d", &filas, &columnas);  // leer ctd filas y columnas desde el archivo


    char matriz[capacidad][capacidad];    // declarar una matriz para almacenar el tablero de letras-------------------------------------------------------

    for (int i = 0; i < filas; i++)   // leer el tablero de letras desde el archivo
        {for (int j = 0; j < columnas; j++) 
    	    {fscanf(archivo, " %c", &matriz[i][j]);
            }
        }// Usamos " %c" para omitir espacios en blanco
    

    

  
    char nombre_archivo2[100]; //guardar le nombre del archivo
    printf("Ponga el nombre del archivo ->(.lst): ");
    scanf("%s", nombre_archivo2); //leer el nombre del archivo
    FILE *archivo2 = fopen(nombre_archivo2, "r");   // Abrir el archivo 

    if (archivo2 == NULL)  //error al abrir el archivo
        {printf("no se pudo abrir el archivo .lst\n");
        return 1;}


    fscanf(archivo2, "%d", &k);    // leer el número de la cantudad a buscar

   
    char palabras[k][largo];  // Leer y procesar las k palabras (almacen las palabras a buscar)
    Coordenada coordenadas[k]; // para almacenar las coordenadas de la primera ocurrencia de cada palabra

    for (int i = 0; i < k; i++) 
        {fscanf(archivo2, "%s", palabras[i]);}



    char nombre_salida[100]; //guardar le nombre del archivo
    strcpy(nombre_salida, nombre_archivo); // Crear un archivo de salida .out con el mismo nombre que el archivo .ini
    strcat(nombre_salida, ".out");

    FILE *archivo_fin = fopen(nombre_salida, "w");  // Abrir el archivo de salida

    for (int i = 0; i < k; i++) 
        {buscador(matriz, filas, columnas, palabras[i], &coordenadas[i], archivo_fin);  // Buscar y marcar las palabras en el tablero y escribir los tableros en el archivo de salida
        if(coordenadas[i].fila != 0)
            {contador=contador+1;}
        }
   
    
    char nombre_salida2[100];  //guardar le nombre del archivo
    strcpy(nombre_salida2, nombre_archivo2); // crear un archivo de salida .out con el mismo nombre que el archivo .lst
    strcat(nombre_salida2, ".out");

    FILE *archivo2_fin = fopen(nombre_salida2, "w");     // Abrir el archivo de salida


    fprintf(archivo2_fin, "%d\n", k); // Escribir el número de palabras encontradas en el archivo de salida para lista1.lst.out

    
    for (int i = 0; i < k; i++)  // Escribir las palabras encontradas y sus coordenadas en el archivo de salida para lista1.lst.out
        {fprintf(archivo2_fin, "%d %d %s\n", coordenadas[i].fila, coordenadas[i].columna,palabras[i]);}


    fclose(archivo);
    fclose(archivo2);
    fclose(archivo_fin);
    fclose(archivo2_fin);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    
    printf("El tiempo de carga es = %f'' (seg)\n", tiempo);
    
    printf("Se crearon dos archivos -> lista().lst.out y tablero().ini.out\n");
    printf(" Se encontro %d palabras de %d (palabras) que se encuentran en lista",contador,k);

    return 0;
}
