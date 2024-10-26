#include <stdio.h>

// Función para intercambiar dos elementos del array
void intercambio(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Función para ordenar un array usando Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        // Últimos i elementos ya están en su lugar correcto
        for (j = 0; j < n - i - 1; j++) {
            // Si el elemento actual es mayor que el siguiente elemento, intercámbialos
            if (arr[j] > arr[j + 1]) {
                intercambio(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    bubbleSort(arr, n);

    printf("\nArray ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
