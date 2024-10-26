#include <stdio.h>

// Función para intercambiar dos elementos del array
void intercambio(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Función para ordenar un array usando Selection Sort
void selectionSort(int arr[], int n) {
    int i, j, min_idx;

    // Recorre el array
    for (i = 0; i < n - 1; i++) {
        // Encuentra el índice del elemento mínimo en el subarray no ordenado
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Intercambia el elemento mínimo encontrado con el primer elemento del subarray no ordenado
        intercambio(&arr[i], &arr[min_idx]);
    }
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    selectionSort(arr, n);

    printf("\nArray ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
