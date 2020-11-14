#include <stdio.h>
#include <pthread.h>

int x ;

// void * ritorno un oggetto tipo Java
void *my_pthread_fn(void *arg) {

    x++;
    return NULL;

}

int main() {
    const int NUMTHREADS = 30000;
    printf("main thread\n");
    pthread_attr_t myattr;
    pthread_t mythread[NUMTHREADS];


    for (int i = 0; i < NUMTHREADS; i++) {
        pthread_attr_init(&myattr);

        int err = pthread_create(&mythread[i], &myattr, my_pthread_fn, NULL);

    }

    void *returnvalue;

    for (int i = 0; i < NUMTHREADS; i++) {
        pthread_join(mythread[i], &returnvalue);

    }

    printf("x is \t%d\n", x);
    printf("NUMERO ASPETATTATO:\t %d\n", NUMTHREADS);
    if (NUMTHREADS != x) {
        printf("data rasing! ");
    } else {
        printf("caso senza data racing\n");
    }

    return 0;
}



