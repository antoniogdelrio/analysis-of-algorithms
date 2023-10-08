#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "util.c"
#include "insertionSort.c"
#include "selectionSort.c"
#include "quickSort.c"
#include "mergeSort.c"
#include "heapSort.c"

typedef void (*SortFunctionPtr)(int[], unsigned int);

int* fillVector(unsigned int size, char* strategy, int* vector, int seed) {
    int i;

    if (!strcmp(strategy, "best")) {
        for (i = 0; i < size; i++) {
            vector[i] = i;
        }
    }

    if (!strcmp(strategy, "worst")) {
        for (i = 0; i < size; i++) {
            vector[i] = size - i;
        }
    }

    if (!strcmp(strategy, "random")) {
        srand((unsigned int) seed);
        for (i = 0; i < size; i++) {
            vector[i] = (int)(((float) rand() / (float)(RAND_MAX)) * (float) size);
        }
    }

    return vector;
}

int* allocateVector(int size) {
    int* ptr = (int*)malloc(size * sizeof(int));
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

SortFunctionPtr getAlgorithmFunction(char* algorithm, char* strategy) {
    if (!strcmp(algorithm, "insertionSort")) {
        return insertionSort;
    }
    if (!strcmp(algorithm, "selectionSort")) {
        return selectionSort;
    }
    if (!strcmp(algorithm, "quickSort") && !strcmp(strategy, "worst")) {
        return quickStarter;
    }
    if (!strcmp(algorithm, "quickSort") && !strcmp(strategy, "best")) {
        return quickStarterOtimo;
    }
    if (!strcmp(algorithm, "quickSort")) {
        return quickStarterAleatorio;
    }
    if (!strcmp(algorithm, "mergeSort")) {
        return mergeStarter;
    }
    if (!strcmp(algorithm, "heapSort")) {
        return heapSort;
    }
}

float* sortAnalysis(
    unsigned int n,
    char* strategy,
    char* algorithm
) {
    static float result[9];

    int i;
    clock_t start, end;
    int* vector = allocateVector(n);

    SortFunctionPtr fn = getAlgorithmFunction(algorithm, strategy);

    for (int i = 0, j = 1; i < 9; i++) {
        int* filledVector = fillVector(n, strategy, vector, j);
        start = clock();
        fn(filledVector, n);
        end = clock();

        result[i] = ((double) end - start) / CLOCKS_PER_SEC;

        if (! isCorrectlySorted(filledVector, n)) {
            fprintf(stderr, "%d/%d, Vector not sorted!\n", i, j);
            exit(-1);
        }
    
        if ((i + 1) % 3 == 0) {
            j++;
        }
    }

    free(vector);

    return result;
}

int main(int argc, char *argv[]) {
    unsigned int n;
    char* strategy;
    char* algorithm;

    if (argc != 4) {
        fprintf(stderr, "3 arguments expected/");
        return -1;
    }

    n = strtoul(argv[1], 0L, 10);
    strategy = argv[2];
    algorithm = argv[3];

    float* results = sortAnalysis(n, strategy, algorithm);

    fprintf(stdout, "%s: ", algorithm);
    for (int i = 0; i < 9; i++) {
        fprintf(stdout, "%f, ", results[i]);
    }
    fprintf(stdout, "\n");
}
