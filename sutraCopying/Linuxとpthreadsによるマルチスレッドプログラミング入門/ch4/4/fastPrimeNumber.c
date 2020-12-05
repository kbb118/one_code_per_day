#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_PRIME_NUMBERS 100000
#define THREADS 6

// 素数表
int primeNumber[MAX_PRIME_NUMBERS];
int nPrimeNumber;

// 素数かどうか確認済みの最大の数
int primeNumberChecked;

pthread_mutex_t usingPrimeNumber;

int isPrimeNumber(int m)
{
    for (int i = 0; i < nPrimeNumber; ++i) {
        if (primeNumber[i] > m/2) {
            return 1;
        }
        if (m%primeNumber[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void generatePrimeNumbers(int n)
{
    if (n <= primeNumberChecked) {
        return;
    }

    pthread_mutex_lock(&usingPrimeNumber);

    /* 足りない分の素数表を作成する */
    for (int i = primeNumberChecked+1; i <= n; ++i) {
        if (isPrimeNumber(i)) {
            if (nPrimeNumber >= MAX_PRIME_NUMBERS) {
                printf("Oops, too many prime numbers.\n");
                exit(1);
            }
            primeNumber[nPrimeNumber++] = i;
        }
    }
    primeNumberChecked = n;

    pthread_mutex_unlock(&usingPrimeNumber);
}

int countPrimeNumbers(int n)
{
    int count = 0;

    generatePrimeNumbers(n);

    for (int i = 0; i < nPrimeNumber; ++i) {
        if (primeNumber[i] > n) {
            break;
        }
        count++;
    }

    return count;
}

void* threadFunc(void* arg)
{
    int n = (int)arg;
    int x = countPrimeNumbers(n);
    printf("Number of prime numbers under %d is %d\n", n, x);

    return NULL;
}

int main(int argc, char *argv[])
{
    int numberList[THREADS] = {1, 10, 100, 1000, 10000, 100000};
    pthread_t threads[THREADS];

    nPrimeNumber = 0;
    primeNumberChecked = 1;

    pthread_mutex_init(&usingPrimeNumber, NULL);

    for (int i = 0; i < THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, threadFunc, (void*)numberList[i]) != 0) {
            printf("Error: Failed to create new thread.\n");
            exit(1);
        }
    }
    for (int i = 0; i < THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error: Failed to wait for the thread termination.\n");
            exit(1);
        }
    }

    pthread_mutex_destroy(&usingPrimeNumber);

    return 0;
}
