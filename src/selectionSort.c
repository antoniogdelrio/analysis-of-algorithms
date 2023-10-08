void selectionSort(int arr[], unsigned int n)
{
    int i, menorIndice, j, trocaValor;

    for(i=0; i < n-1; i++) {
        menorIndice = i;

        for (j=i+1; j < n; j++) {
            if (arr[j] < arr[menorIndice]) {
                menorIndice = j; 
            }
        }

        if (menorIndice != i) {
            troca(&arr[i], &arr[menorIndice]);
        }
    }
}