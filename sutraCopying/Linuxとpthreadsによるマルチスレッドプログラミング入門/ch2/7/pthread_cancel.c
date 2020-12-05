#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* threadFunc(void* arg)
{
    int *buf = malloc(sizeof(int)*100);
    if ( !buf ) {
        printf("Memory allocation error.\n");
        exit(1);
    }

    while (1) {
        printf("threadFunc working...\n");
        sleep(1);
        for (int i = 0; i < 100; ++i) {
            buf[i] += 1;
        }
    }

    // main から pthread_cancel されて while 内で
    // pthread_exit されるので leak する...
    free(buf);

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread;

    if (pthread_create(&thread, NULL, threadFunc, NULL) != 0) {
        printf("Error: Failed to create new thread.\n");
        exit(1);
    }

    sleep(5);
    pthread_cancel(thread);
    if (pthread_join(thread, NULL) != 0) {
        printf("Error: Failed to wait for the thread termination.\n");
        exit(1);
    }

    return 0;
}
