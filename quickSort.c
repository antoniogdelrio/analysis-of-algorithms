int particione(int arr[], int indiceInicio, int indiceFim)
{

    int x = arr[indiceFim];
 
    int i = (indiceInicio - 1);
 
    for (int j = indiceInicio; j <= indiceFim - 1; j++) {
 
        if (arr[j] < x) {
 
            i++;
            troca(&arr[i], &arr[j]);
        }
    }

    troca(&arr[i + 1], &arr[indiceFim]);
    return (i + 1);
}
 
void quickSort(int arr[], int indiceInicio, int indiceFim)
{
    if (indiceInicio < indiceFim) {

        int q = particione(arr, indiceInicio, indiceFim);

        quickSort(arr, indiceInicio, q - 1);
        quickSort(arr, q + 1, indiceFim);
    }
}

void quickStarter(int arr[], int n)
{
    quickSort(arr, 0, n-1);
}
