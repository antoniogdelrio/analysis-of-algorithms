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

int getRandomNumber(int lower, int upper) {
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int particioneAleatorio(int arr[], int indiceInicio, int indiceFim) {
    srand(time(NULL));

    int i = getRandomNumber(indiceInicio, indiceFim);

    troca(&arr[i], &arr[indiceFim]);

    return particione(arr, indiceInicio, indiceFim);
}

int particioneOtimo(int arr[], int indiceInicio, int indiceFim) {
    int middle = ((indiceFim - indiceInicio) / 2) + indiceInicio;

    troca(&arr[middle], &arr[indiceFim]);

    return particione(arr, indiceInicio, indiceFim);
}

void quickSort(int arr[], int indiceInicio, int indiceFim)
{
    if (indiceInicio < indiceFim) {

        int q = particione(arr, indiceInicio, indiceFim);

        quickSort(arr, indiceInicio, q - 1);
        quickSort(arr, q + 1, indiceFim);
    }
}

void quickSortAleatorio(int arr[], int indiceInicio, int indiceFim)
{
    if (indiceInicio < indiceFim) {

        int q = particioneAleatorio(arr, indiceInicio, indiceFim);

        quickSortAleatorio(arr, indiceInicio, q - 1);
        quickSortAleatorio(arr, q + 1, indiceFim);
    }
}

void quickSortOtimo(int arr[], int indiceInicio, int indiceFim)
{
    if (indiceInicio < indiceFim) {

        int q = particioneOtimo(arr, indiceInicio, indiceFim);

        quickSortOtimo(arr, indiceInicio, q - 1);
        quickSortOtimo(arr, q + 1, indiceFim);
    }
}

void quickStarter(int arr[], unsigned int n)
{
    quickSort(arr, 0, n-1);
}

void quickStarterAleatorio(int arr[], unsigned int n)
{
    quickSortAleatorio(arr, 0, n-1);
}

void quickStarterOtimo(int arr[], unsigned int n)
{
    quickSortOtimo(arr, 0, n-1);
}