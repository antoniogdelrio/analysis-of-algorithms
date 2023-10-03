#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

typedef void (*SortFunctionPtr)(int[], int);

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

bool isCorrectlySorted(int arr[], int n){
    int i;
    for (i=1; i<n; i++)
        if (arr[i-1] > arr[i]){
            printf("Found: [%d] > [%d]\n", arr[i-1], arr[i]);
            return false;
        }
    return true;
}

SortFunctionPtr getAlgorithmFunction(char* algorithm) {
    if (!strcmp(algorithm, "INSERTION_SORT")) {
        return insertionSort;
    }
}

float* sortAnalysis(
    int n,
    int strategy,
    char* algorithm
) {
    static float result[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i;
    clock_t start, end;
    int* vector;
    SortFunctionPtr fn = getAlgorithmFunction(algorithm);

    for (int i = 0, j = 1; i < 9; i++) {
        vector = generateVector(n, strategy, j);
        start = clock();
        fn(vector, n);
        end = clock();
        result[i] = ((double) end - start) / CLOCKS_PER_SEC;

        if (! isCorrectlySorted(vector, n))
            fprintf(stderr, "%d/%d, Vector not sorted!\n", i, j);

        free(vector);
 
        if ((i + 1) % 3 == 0) {
            j++;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    unsigned int n;
    int strategy;
    char* algorithm;

    if (argc != 4) {
        fprintf(stderr, "3 arguments expected/");
        return -1;
    }

    n = strtoul(argv[1], 0L, 10);
    strategy = atoi(argv[2]);
    algorithm = argv[3];

    float* results = sortAnalysis(n, strategy, algorithm);
    
    for (int k = 0; k < 9; k++) {
        fprintf(stdout, "%f ", results[k]);
        fprintf(stdout, "\n");
    }
}
