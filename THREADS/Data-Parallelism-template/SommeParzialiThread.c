//variante con thread main che lavora (fa da quatro thread)
//in piu' il num di elementi non è esattamente un numero multiplo dei threads

#include <stdio.h>
#include <pthread.h>


#define NUM_THREADS 4
#define N_ELEMENT 10

int arr[N_ELEMENT];

const int rapporto = N_ELEMENT / NUM_THREADS;

int *pthread_fn(void *args) {
    int j = 0;
    int index = (int) args;
    if ((N_ELEMENT % NUM_THREADS) != 0) {
        j = 1;
    }

    int min = index * (rapporto + j);
    int max = (rapporto + j) + min;

    int somma = 0;
    if (N_ELEMENT - min < rapporto + j) {
        max = N_ELEMENT;
    }
    for (index = min; index < max; index++) {
        somma += arr[index];
    }
    return somma;
}

void riempiArray() {
    for (int i = 0; i < N_ELEMENT; i++) {
        arr[i] = i;
    }
}


int main() {
    riempiArray();
    pthread_t my_threads[NUM_THREADS - 1];
    pthread_attr_t myattr;
    int *returnvalue;
    int somma_Tot = 0;
    for (int i = 0; i < NUM_THREADS - 1; i++) {

        pthread_attr_init(&myattr);
        pthread_create(&my_threads[i], &myattr, pthread_fn, (void *) i);
        pthread_attr_destroy(&myattr);

    }
    somma_Tot=pthread_fn((int) NUM_THREADS - 1);
    printf("Somma paziale del Thread %d : %d\n", NUM_THREADS-1, somma_Tot);
    for (int j = 0; j < NUM_THREADS - 1; j++) {

        pthread_join(my_threads[j], &returnvalue);

        printf("Somma parziale del thread %d: %d\n", j, (int) returnvalue);

        somma_Tot+= (int) returnvalue;
    }
    printf("Somma totale: %d", somma_Tot);

    return 0;
}



