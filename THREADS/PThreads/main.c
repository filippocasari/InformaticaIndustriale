#include <stdio.h>
#include <pthread.h>


// void * ritorno un oggetto tipo Java
void *my_pthread_fn(void *arg) {

    //Thread body
    printf("\t\t\t\t\t\tfaccio altre robeeee\n");
    return NULL;

}

int main() {

    printf("main thread\n");
    //my_pthread_fn(NULL); NULL==> ritorna 0

    pthread_attr_t myattr;

    pthread_attr_init(&myattr);

    pthread_t mythread;


    int err = pthread_create(&mythread, &myattr, my_pthread_fn, NULL);


    printf("..more stuff...\n");
    printf("..more stuff...\n");
    void *returnvalue;
    pthread_join(mythread, &returnvalue);
    printf("..more stuff...\n");

    printf("..more stuff...\n");
    printf("..more stuff...\n");


    return 0;
}


