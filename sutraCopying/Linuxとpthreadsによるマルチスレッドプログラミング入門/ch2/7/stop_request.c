#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int stopRequest = 0;

void* threadFunc(void* arg)
{
    int *buf = malloc(sizeof(int)*100);
    if ( !buf ) {
        printf("Memory allocation error.\n");
        exit(1);
    }

    while (stopRequest == 0) {
        printf("threadFunc working...\n");
        sleep(1);
        for (int i = 0; i < 100; ++i) {
            buf[i] += 1;
        }
    }

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
    stopRequest = 1;

    if (pthread_join(thread, NULL) != 0) {
        printf("Error: Failed to wait for the thread termination.\n");
        exit(1);
    }

    return 0;
}
