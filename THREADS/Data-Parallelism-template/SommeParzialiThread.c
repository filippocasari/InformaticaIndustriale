//variante con thread main che lavora (fa da quarto thread)
//in piu', se il num di elementi non è esattamente
// un numero multiplo dei threads, ho j che viene sommato al chunk

#include <stdio.h>
#include <pthread.h>


#define NUM_THREADS 4
#define N_ELEMENT 5

int arr[N_ELEMENT];

const int rapporto = N_ELEMENT / NUM_THREADS;

int *pthread_fn(void *args) {
    int j = 0;
    int index = (int) args;
    j = ((N_ELEMENT % NUM_THREADS) != 0) ? 1 : 0;

    int contatore_el_processati = 0;
    int min = index * (rapporto + j);
    int max = (rapporto + j) + min;

    int somma = 0;
    if (N_ELEMENT - min < rapporto + j) {
        max = N_ELEMENT;
    }
    for (index = min; index < max; index++) {
        somma += arr[index];
        contatore_el_processati++;
    }

    return somma;
}

void riempiArray() {
    for (int i = 0; i < N_ELEMENT; i++) {
        arr[i] = i;
    }
}

void Average_fn(const int *Somma_Tot, float *Media) {

    *Media = (float) *Somma_Tot / N_ELEMENT;
}


int main() {
    float Media;
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
    somma_Tot = pthread_fn((int) NUM_THREADS - 1);
    printf("Somma paziale del Thread %d : %d\n", NUM_THREADS - 1, somma_Tot);
    for (int j = 0; j < NUM_THREADS - 1; j++) {

        pthread_join(my_threads[j], &returnvalue);

        printf("Somma parziale del thread %d: %d\n", j, (int) returnvalue);

        somma_Tot += (int) returnvalue;
    }
    printf("Somma totale: %d\n", somma_Tot);
    Average_fn(&somma_Tot, &Media);
    printf("La media e' : %f", Media);
    return 0;
}



