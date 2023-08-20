#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* fillVector(int size, int strategy, int* vector) {
    int i;
    switch(strategy) {
        case(1):
            for (i = 0; i < size; i++) {
                vector[i] = i;
            }
            break;
        case(2):
            srand((unsigned int) time(NULL));
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

int* generateVector(int size, int strategy) {
    int* ptr = (int*)malloc(size * sizeof(int));
    ptr = fillVector(size, strategy, ptr);

    return ptr;
}

void printVector(int* vector, int size) {
    printf("Printing vector:\n");
    for (int k = 0; k < size; k++) {
        printf("%d, \n", vector[k]);
    }
}

void main() {
    int size = 100000;
    int* vector = generateVector(size, 2);
    printVector(vector, size);
}