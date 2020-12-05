#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int varA;

void* threadFunc(void* arg)
{
    int n = (int)arg;
    int varB;

    varB = 4*n;
    printf("threadFunc-%d-1: varA=%d, varB=%d\n", n, varA, varB);
    varA = 5*n;
    printf("threadFunc-%d-2: varA=%d, varB=%d\n", n, varA, varB);
    sleep(2);
    printf("threadFunc-%d-3: varA=%d, varB=%d\n", n, varA, varB);
    varB = 6*n;
    printf("threadFunc-%d-4: varA=%d, varB=%d\n", n, varA, varB);

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;
    int varB;

    varA = 1;
    varB = 1;
    printf("main-1: varA=%d, varB=%d\n", varA, varB);

    if (pthread_create(&thread1, NULL, threadFunc, (void*)1) != 0) {
        printf("Error: Failed to create new thread.\n");
        exit(1);
    }
    sleep(1);

    varB = 3;
    printf("main2: varA=%d, varB=%d\n", varA, varB);
    if (pthread_create(&thread2, NULL, threadFunc, (void*)2) != 0) {
        printf("Error: Failed to create new thread.\n");
        exit(1);
    }

    if (pthread_join(thread1, NULL) != 0) {
        printf("Error: Failed to wait for the thread termination.\n");
        exit(1);
    }
    if (pthread_join(thread2, NULL) != 0) {
        printf("Error: Failed to wait for the thread termination.\n");
        exit(1);
    }

    printf("main-3: varA=%d, varB=%d\n", varA, varB);

    return 0;
}
