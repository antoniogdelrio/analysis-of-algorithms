void maxHeapify(int arr[], int n, int i) {
    int maior = i;       // Inicializa o maior como raiz
    int esquerdo = 2 * i + 1;  // índice do filho esquerdo
    int direito = 2 * i + 2; // índice do filho direito

    // Se o filho esquerdo é maior que o pai
    if (esquerdo < n && arr[esquerdo] > arr[maior])
        maior = esquerdo;

    // Se o filho direito é maior que o maior até agora
    if (direito < n && arr[direito] > arr[maior])
        maior = direito;

    // Se o maior não é a raiz
    if (maior != i) {
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;

        // Chama recursivamente a função em relação ao filho afetado
        maxHeapify(arr, n, maior);
    }
}

void buildMaxHeap(int arr[], int n) {
    // Começa a partir do último nó não folha e vai até a raiz
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

void heapSort(int arr[], int n) {
    // Construir um heap máximo
    buildMaxHeap(arr, n);

    // Extrair elementos um por um do heap
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz atual para o final do array
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Chama maxHeapify no heap reduzido
        maxHeapify(arr, i, 0);
    }
}