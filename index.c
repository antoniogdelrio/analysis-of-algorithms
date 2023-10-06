#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "util.c"
#include "insertionSort.c"
#include "selectionSort.c"
#include "quickSort.c"

enum SORT_ALGORITHM {
    INSERTION_SORT,
    SELECTION_SORT,
    QUICK_SORT,
    MERGE_SORT,
    HEAP_SORT,
};

typedef void (*SortFunctionPtr)(int[], int);

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

SortFunctionPtr getAlgorithmFunction(int algorithm) {
    if (algorithm == INSERTION_SORT) {
        return insertionSort;
    }
    if (algorithm == SELECTION_SORT) {
        return selectionSort;
    }
    if (algorithm == QUICK_SORT) {
        return quickStarter;
    }
    if (algorithm == MERGE_SORT) {
        return insertionSort;
    }
    if (algorithm == HEAP_SORT) {
        return insertionSort;
    }
}

char* getAlgorithmName(int algorithm) {
    if (algorithm == INSERTION_SORT) {
        return "insertionSort";
    }
    if (algorithm == SELECTION_SORT) {
        return "selectionSort";
    }
    if (algorithm == QUICK_SORT) {
        return "quickSort";
    }
    if (algorithm == MERGE_SORT) {
        return "mergeSort";
    }
    if (algorithm == HEAP_SORT) {
        return "heapSort";
    }
}

float* sortAnalysis(
    int n,
    int strategy
) {
    static float result[45];

    int i;
    clock_t start, end;
    int* vector = allocateVector(n);

    for (int v = 0; v < 5; v++) {
        SortFunctionPtr fn = getAlgorithmFunction(v);

        for (int i = 0, j = 1; i < 9; i++) {
            int* filledVector = fillVector(n, strategy, vector, j);
            start = clock();
            fn(filledVector, n);
            end = clock();
            result[v * 9 + i] = ((double) end - start) / CLOCKS_PER_SEC;

            if (! isCorrectlySorted(filledVector, n))
                fprintf(stderr, "%d/%d, Vector not sorted!\n", i, j);
    
            if ((i + 1) % 3 == 0) {
                j++;
            }

        }
    }

    free(vector);

    return result;
}

int main(int argc, char *argv[]) {
    unsigned int n;
    int strategy;

    if (argc != 3) {
        fprintf(stderr, "2 arguments expected/");
        return -1;
    }

    n = strtoul(argv[1], 0L, 10);
    strategy = atoi(argv[2]);

    float* results = sortAnalysis(n, strategy);

    for (int v = 0; v < 5; v++) {
        fprintf(stdout, "%s: ", getAlgorithmName(v));
        for (int i = 0, j = 1; i < 9; i++) {
            fprintf(stdout, "%f, ", results[v * 9 + i]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}
