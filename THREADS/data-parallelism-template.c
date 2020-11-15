#include <stdio.h>
#include <pthread.h>


#define NUM_THREADS 4
#define N_ELEMENT 20

int arr[N_ELEMENT];
const int rapporto = N_ELEMENT / NUM_THREADS;

void *pthread_fn(void *args) {

    int index = (int) args;
    int min = index * rapporto;
    int max = rapporto + min;
    for (;index < max; index++) {
        arr[index] = index * 2;
    }

}

void stampa_tutto() {
    for (int i = 0; i < N_ELEMENT; i++) {
        printf("arr[%d] is\t %d\n", i, arr[i]);
    }
}


int main() {

    pthread_t my_threads[NUM_THREADS];
    pthread_attr_t myattr;
    void *returnvalue;

    for (int i = 0; i < NUM_THREADS; i++) {

        pthread_attr_init(&myattr);
        int err = pthread_create(&my_threads[i], &myattr, pthread_fn, (void *) i);
        pthread_attr_destroy(&myattr);
    }
    for (int j = 0; j < NUM_THREADS; j++) {
        pthread_join(my_threads[j], &returnvalue);
    }

    stampa_tutto();
    return 0;
}
