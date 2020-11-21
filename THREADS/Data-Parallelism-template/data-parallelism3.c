//variante con thread main che lavora (fa da quatro thread)
//in piu' il num di elementi non è esattamente un numero multiplo dei threads

#include <stdio.h>
#include <pthread.h>


#define NUM_THREADS 4
#define N_ELEMENT 5

int arr[N_ELEMENT];

const int rapporto = N_ELEMENT / NUM_THREADS;

void *pthread_fn(void *args) {
    int index = (int) args;
    int j = 0;
    if ((N_ELEMENT % NUM_THREADS) != 0) {
        j = 1;
    }

    printf("thread numero: %d\n", index);


    int min = index * (rapporto + j);
    int max = (rapporto + j) + min;
    if(N_ELEMENT-min < rapporto+j){
        max=N_ELEMENT;
    }
    for (index = min; index < max; index++) {
        arr[index] = index * 2;

        printf("arr[%d] is %d\t\n", index, arr[index]);
    }

    printf("\n\n");

}

void stampa_tutto() {
    for (int i = 0; i < N_ELEMENT; i++) {
        printf("arr[%d] is\t %d\n", i, arr[i]);
    }
}


int main() {

    pthread_t my_threads[NUM_THREADS - 1];
    pthread_attr_t myattr;
    void *returnvalue;

    for (int i = 0; i < NUM_THREADS - 1; i++) {

        pthread_attr_init(&myattr);
        int err = pthread_create(&my_threads[i], &myattr, pthread_fn, (void *) i);
        pthread_attr_destroy(&myattr);
    }
    pthread_fn((int) NUM_THREADS - 1);
    for (int j = 0; j < NUM_THREADS - 1; j++) {
        pthread_join(my_threads[j], &returnvalue);
    }


    return 0;
}

