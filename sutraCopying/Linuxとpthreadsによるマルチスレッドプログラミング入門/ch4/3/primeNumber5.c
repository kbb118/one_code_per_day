#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_PRIME_NUMBERS 100000

int primeNumber[MAX_PRIME_NUMBERS];
int nPrimeNumber;
pthread_mutex_t usingPrimeNumber;

int isPrimeNumber(int m)
{
    for (int i = 0; i < nPrimeNumber; ++i) {
        if (m%primeNumber[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int countPrimeNumbers(int n)
{
    pthread_mutex_lock(&usingPrimeNumber);

    nPrimeNumber = 0;
    for (int i = 2; i < n+1; ++i) {
        if (isPrimeNumber(i)) {
            if (nPrimeNumber >= MAX_PRIME_NUMBERS) {
                printf("Oops, too many prime numbers\n");
                exit(1);
            }
            primeNumber[nPrimeNumber++] = i;
        }
    }
    pthread_mutex_unlock(&usingPrimeNumber);

    return nPrimeNumber;
}

void* threadFunc(void* arg)
{
    int n = (int)arg;
    int x = countPrimeNumbers(n);
    printf("Number of prime numbers under %d is %d\n", n, x);

    return NULL;
}

// 共有資源書き込み時はmutex lock してるので大丈夫
int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;

    pthread_mutex_init(&usingPrimeNumber, NULL);

    if (pthread_create(&thread1, NULL, threadFunc, (void*)100000) != 0) {
        printf("Error: Failed to create new thread.\n");
        exit(1);
    }
    if (pthread_create(&thread2, NULL, threadFunc, (void*)200000) != 0) {
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

    pthread_mutex_destroy(&usingPrimeNumber);
    printf("Done.\n");

    return 0;
}
