//variante con thread main che lavora (fa da quatro thread)

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
    for (index=min;index < max; index++) {
        arr[index] = index * 2;
        
        printf("arr[%d] is %d\t", index, arr[index]);
    }
    
    printf("\n");

}

void stampa_tutto() {
    for (int i = 0; i < N_ELEMENT; i++) {
        printf("arr[%d] is\t %d\n", i, arr[i]);
    }
}


int main() {

    pthread_t my_threads[NUM_THREADS-1];
    pthread_attr_t myattr;
    void *returnvalue;

    for (int i = 0; i < NUM_THREADS-1; i++) {

        pthread_attr_init(&myattr);
        int err = pthread_create(&my_threads[i], &myattr, pthread_fn, (void *) i);
        pthread_attr_destroy(&myattr);
    }
    pthread_fn((int) NUM_THREADS-1);
    for (int j = 0; j < NUM_THREADS-1; j++) {
        pthread_join(my_threads[j], &returnvalue);
    }

    
    return 0;
}
