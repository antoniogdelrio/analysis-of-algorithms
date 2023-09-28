#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int* fillVector(int size, int strategy, int* vector, int seed) {
    int i;
    switch(strategy) {
        case(1):
            for (i = 0; i < size; i++) {
                vector[i] = i;
            }
            break;
        case(2):
            srand((unsigned int) seed);
            for (i = 0; i < size; i++) {
                vector[i] = (int)(((float) rand() / (float)(RAND_MAX)) * (float) size);
                printf("%d\n", vector[i]);
            }
            break;
        case(3):
            for (i = 0; i < size; i++) {
                vector[i] = size - i;
            }
            break;
        default:
            break;
    }
    return vector;
}

int* generateVector(int size, int strategy, int seed) {
    int* ptr = (int*)malloc(size * sizeof(int));
    ptr = fillVector(size, strategy, ptr, seed);

    return ptr;
}

float* insertionSortAnalysys(
    int n,
    int strategy
) {
    static float result[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i;
    clock_t start, end;
    int* vector;

    for (int i = 0, j = 1; i < 9; i++) {
        vector = generateVector(n, strategy, j);
        start = clock();
        insertionSort(vector, n);
        end = clock();
        free(vector);
        result[i] = ((double) end - start) / CLOCKS_PER_SEC;
 
        if ((i + 1) % 3 == 0) {
            j++;
        }
    }
    return result;
}

void main() {
    int n = 100000;
    int strategy = 3;

    float* results = insertionSortAnalysys(n, strategy);
    
    for (int k = 0; k < 3; k++) {
        printf("%f, \n", results[k]);
    }
}