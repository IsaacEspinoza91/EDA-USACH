#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct producto{
    int fila;
    int columna;
}datosPalab;



/*Funcion que escribe el tablero en un archivo de texto
Entradas: tablero (char**), cantidad filas tablero (int), cantidad columnas tablero (int), archivo a escribir (FILE*)
Salida: sin salida*/
void escribirTablero(char** tablero, int filas, int columnas, FILE* archivo){
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            fprintf(archivo," %c",tablero[i][j]);
        }
        fprintf(archivo,"\n");
    }
    fprintf(archivo,"\n");      //escribimos la linea de separacion entre los tableros
    return;
}



/*Funcion que lee el archivo de palabras y crea un array con palabras
Entrada: nombre archivo Lista de palabras (array char), direccion de memoria de variable int que guarda 
la cantidad de palabras (puntero)
Salida: array de array de char (nombres leidos, array de palabras)*/
char** lecturaPalabras(char* nombreArchivo, int* cantidadPalabrasPuntero){

    char caracterLeido;

    FILE* archivoLeido = fopen(nombreArchivo, "r");
    if(archivoLeido == NULL){
        printf("Error al leer las palabras\n");
        exit(1);
    }else{
        printf("\nEl archivo %s se abrio correctamente",nombreArchivo);
    }

    int cantPalabras;       //lectura de la primera linea del texto, cantidad de palabras
    fscanf(archivoLeido, "%d", &cantPalabras);

    char** arrayPalabras = (char**)malloc(sizeof(char*)*cantPalabras);         //array dinamico de las palabras leidas
    for(int i=0; i<cantPalabras; i++){    //iteracion que recorre las n palabras   
        arrayPalabras[i] = (char*)malloc(sizeof(char)*18);      //limite de 18 letras cada palabra
        fscanf(archivoLeido,"%s",arrayPalabras[i]);
    }

    fclose(archivoLeido);
    *cantidadPalabrasPuntero = cantPalabras;
    return arrayPalabras;
}



/*Funcion que lee el archivo del tablero y crea una matriz con caracteres leidos
Entrada: nombre archivo Tablero (array char), direccion de memoria variable int filas del tablero,
direccion de memoria variable int columnas del tablero
Salida: array de array de char, matriz de caracteres del tablero*/
char** lecturaTablero(char* nombreArchivo, int* filasTableroPuntero, int* columTableroPuntero){

    FILE* tableroLeido = fopen(nombreArchivo, "r");
    if(nombreArchivo == NULL){
        printf("Error al leer el tablero\n");
        exit(1);
    }else{
        printf("\nEl archivo %s se abrio correctamente\n",nombreArchivo);
    }

    int filasTablero, columTablero;     //lectura de la primera linea de texto, tamanio tablero filasxcolumnas
    fscanf(tableroLeido,"%d %d", &filasTablero, &columTablero);
    *filasTableroPuntero = filasTablero;        //guardamos los datos de fila y columna en las variables ingresadas como parametro
    *columTableroPuntero = columTablero;

    char** tablero = (char**)malloc(sizeof(char*)*filasTablero);        //creamos matriz del tablero
    for (int i=0; i<filasTablero; i++) {
        tablero[i] = (char*)malloc(sizeof(char)*columTablero);
        for (int j=0; j<columTablero; j++) {
            fscanf(tableroLeido, " %c", &tablero[i][j]);        //leemos los caracteres de cada linea sin el espacio entremedio
        }
    }

    fclose(tableroLeido);
    return tablero;
}



/*Funcion que busca las palabras dentro del tablero y entrega bool de su resultado
Entrada: palabra a buscar (array de char), tablero (array de array de char, char**),
filas tablero (int), columnas tablero (int), direccion de memoria datos de la palabra struct(datosPalab*),
booleano sobre si la palabre ingresada esta invertida (true) o esta derecha (false),
flujo del archivo a escribir la salida tablero.out (FILE*).
Salida: booleano true si encuentra palabra, falso si no encuentra palabra*/
bool buscarPalabras(char* palabra, char** tablero, int filas, int columnas, datosPalab* palabraActual, bool palabraInversa, FILE* archivoTab){

    bool pEncontrada;
    int largoPalabra = strlen(palabra);     //la funcion srtlen obtiene el largo de la palabra ingresada, cant de char
    
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){         //con estos dos bucles anidados se recorren todos los char del tablero
            if(tablero[i][j]==palabra[0]){  //caso en que encuentra la primera letra de la palabra en el tablero


                //BUSQUEDA DERECHA A IZQ ->
                if((j+largoPalabra-1)<columnas){
                    pEncontrada = true;
                    for(int u=1; u<largoPalabra; u++){      //partimos de 1 porque ya sabemos que la primera letra si coincide
                        if(tablero[i][j+u] != palabra[u]){      //solo en el caso en que todas las demas palabras no coincidan
                            pEncontrada = false;            //se podria para la iteracion del u aqui
                            break;
                        }
                    }
                    if(pEncontrada==true){

                        //proceso de escribir * en el tablero
                        for(int q=0; q<largoPalabra; q++){
                            tablero[i][j+q] = '*';
                        }
                        escribirTablero(tablero,filas,columnas,archivoTab);
                        for(int q=0; q<largoPalabra; q++){  //volvemos a escribir la palabra en vez de *
                            tablero[i][j+q] = palabra[q];
                        }

                        if(palabraInversa==false){
                            palabraActual->fila = i+1;
                            palabraActual->columna = j+1;
                            return true;
                        }else{
                            palabraActual->fila = i+1;
                            palabraActual->columna = j+largoPalabra;
                            return true;
                        }
                    }
                }



                //BUSQUEDA ARRIBA HACIA ABAJO ↓
                if((i+largoPalabra-1)<filas){
                    pEncontrada = true;
                    for(int u=1; u<largoPalabra; u++){
                        if(tablero[i+u][j] != palabra[u]){      //vamos buscando en la fila siguiente, entonces i+u
                            pEncontrada = false;
                            break;
                        }
                    }
                    if(pEncontrada==true){

                        //proceso de escribir * en el tablero
                        for(int q=0; q<largoPalabra; q++){
                            tablero[i+q][j] = '*';
                        }
                        escribirTablero(tablero,filas,columnas,archivoTab);
                        for(int q=0; q<largoPalabra; q++){  //volvemos a escribir la palabra en vez de *
                            tablero[i+q][j] = palabra[q];
                        }


                        if(palabraInversa==false){
                            palabraActual->fila = i+1;
                            palabraActual->columna = j+1;
                            return true;
                        }else{
                            palabraActual->fila = i+largoPalabra;
                            palabraActual->columna = j+1;
                            return true;
                        }
                    }
                }



                //BUSQUEDA DIAGONAL ABAJO/IZQ ↙
                if(((i+largoPalabra-1) < filas) && ((j-largoPalabra+1) >= 0)){
                    pEncontrada = true;
                    for(int u=1; u<largoPalabra; u++){
                        if(tablero[i+u][j-u] != palabra[u]){      //vamos buscando en la fila siguiente, entonces i+u
                            pEncontrada = false;
                            break;
                        }
                    }
                    if(pEncontrada==true){

                        //proceso de escribir * en el tablero
                        for(int q=0; q<largoPalabra; q++){
                            tablero[i+q][j-q] = '*';
                        }
                        escribirTablero(tablero,filas,columnas,archivoTab);
                        for(int q=0; q<largoPalabra; q++){  //volvemos a escribir la palabra en vez de *
                            tablero[i+q][j-q] = palabra[q];
                        }


                        if(palabraInversa==false){
                            palabraActual->fila = i+1;
                            palabraActual->columna = j+1;
                            return true;
                        }else{
                            palabraActual->fila = i+largoPalabra;
                            palabraActual->columna = j-largoPalabra+2;
                            return true;
                        }
                    }
                }



                //BUSQUEDA DIAGONAL ABAJO/DERE ↘
                if(((i+largoPalabra-1) < filas) && ((j+largoPalabra-1)<columnas)){
                    pEncontrada = true;
                    for(int u=1; u<largoPalabra; u++){
                        if(tablero[i+u][j+u] != palabra[u]){      //vamos buscando en la fila siguiente, entonces i+u
                            pEncontrada = false;
                            break;
                        }
                    }
                    if(pEncontrada==true){

                        //proceso de escribir * en el tablero
                        for(int q=0; q<largoPalabra; q++){
                            tablero[i+q][j+q] = '*';
                        }
                        escribirTablero(tablero,filas,columnas,archivoTab);
                        for(int q=0; q<largoPalabra; q++){  //volvemos a escribir la palabra en vez de *
                            tablero[i+q][j+q] = palabra[q];
                        }


                        if(palabraInversa==false){
                            palabraActual->fila = i+1;
                            palabraActual->columna = j+1;
                            return true;
                        }else{
                            palabraActual->fila = i+largoPalabra;
                            palabraActual->columna = j+largoPalabra;
                            return true;
                        }
                    }
                }
            }
        }
    }
    palabraActual->fila = -1;
    palabraActual->columna = -1;
    return false;
}



/*Funcion que reemplaza la extension de formato del nombre de un archivo, 
ejemplo podria reeplazar hola.jpg por hola.png
Entrada: nombre archivo con extension de 3 letras (array de char, char*),
extension a cambiar (array de char, char*)
Salida: array de char con la extension nueva (char*)*/
char* cambiarExtension3char(char* nombreArchivo, char* extension){
    int largoNombre = strlen(nombreArchivo);
    for(int n=1; n<=3; n++){
        nombreArchivo[largoNombre-n] = extension[3-n];
    }
    return nombreArchivo;
}




void main(){

    char* nombreLista = (char*)malloc(sizeof(char)*12);//limite de 12 letras en el nombre a buscar
    char* nombreTablero = (char*)malloc(sizeof(char)*12);
    int cantPalabrasArray, numBuscar, resultBusqueda, filasM, columnasN, contPalabras=0;
    bool palabraEncontrada, palabraInvertidaEncontrada;


    printf("\nIngresar el nombre del archivo lista (con su extension .lst): ");
    scanf("%s",nombreLista);
    printf("Ingresar el nombre del archivo tablero (con su extension .ini): ");
    scanf("%s",nombreTablero);

    char** palabrasTablero = lecturaPalabras(nombreLista, &cantPalabrasArray);
    char** tablero = lecturaTablero(nombreTablero, &filasM, &columnasN);


    cambiarExtension3char(nombreLista, "out");
    cambiarExtension3char(nombreTablero, "out");
    FILE* salidaListaPalabra = fopen(nombreLista, "w");
    if(salidaListaPalabra == NULL){
        printf("\nNo se pudo crear el archivo");
        return;
    }else{
        printf("\nSe creo correctamente el archivo %s",nombreLista);
    }

    FILE* salidaTablero = fopen(nombreTablero, "w");
    if(salidaTablero == NULL){
        printf("\nNo se pudo crear el archivo");
        return;
    }else{
        printf("\nSe cre correctamente el archivo %s\n",nombreTablero);
    }
    
    datosPalab* datosPalabras = (datosPalab*)malloc(sizeof(datosPalab)*cantPalabrasArray);


    //buscamos las palabras y sus posciones y las agregamos al array de datos
    for(int t=0; t<cantPalabrasArray; t++){
        palabraEncontrada = buscarPalabras(palabrasTablero[t], tablero, filasM, columnasN, &datosPalabras[t], false, salidaTablero);
        if(palabraEncontrada==false){//en el caso que en un inicio no encontro la palabra, ahora se busca las misma palabra pero al reves
            strrev(palabrasTablero[t]);     //funcion que invierte el array de char
            palabraEncontrada = buscarPalabras(palabrasTablero[t], tablero, filasM, columnasN, &datosPalabras[t], true, salidaTablero);   //con palabra invertida
            strrev(palabrasTablero[t]);      //volvemos a invertirlo para que vuelva a estar normal
        }
    }



    //ESCRIBIMOS LA CANTIDAD DE PALABRAS EN EL ARCHIVO LISTA.OUT
    fprintf(salidaListaPalabra, "%d\n",cantPalabrasArray);
    //PROCESO IMPRIMIR LAS PALABRAS Y SUS DATOS EN LISTA.OUT
    for(int r=0; r<cantPalabrasArray; r++){
        if(datosPalabras[r].fila != -1){        //condicion para contar palabras encontrada, si fila es -1 NO encontro la palabra
            contPalabras ++;
            //imprimir datos palabras en el texto de salida lista.out
            fprintf(salidaListaPalabra, "%d %d (%s)\n", datosPalabras[r].fila, datosPalabras[r].columna, palabrasTablero[r]);
        }
    }



    
    printf("\nPalabras buscadas: %d\nPalabras encontradas: %d\n",cantPalabrasArray, contPalabras);
    fclose(salidaListaPalabra);
    fclose(salidaTablero);


    //RECORDAR LIBERAR MEMORIA

}