#include <stdio.h>

// Función para intercambiar dos elementos del array
void intercambio(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Función para seleccionar el pivote y particionar el array
int particiona(int arr[], int low, int high) {
    int pivot = arr[high]; // Tomamos el último elemento como pivote
    int i = (low - 1);     // Índice del menor elemento

    for (int j = low; j <= high - 1; j++) {
        // Si el elemento actual es menor o igual al pivote
        if (arr[j] <= pivot) {
            i++; // Incrementa el índice del menor elemento
            intercambio(&arr[i], &arr[j]);
        }
    }
    intercambio(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Función principal de QuickSort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Encuentra el índice de partición
        int pi = particiona(arr, low, high);

        // Ordena los elementos antes y después de la partición
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    quickSort(arr, 0, n - 1);

    printf("\nArray ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
