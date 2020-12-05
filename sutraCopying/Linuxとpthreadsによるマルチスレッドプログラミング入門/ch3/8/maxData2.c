#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define DATASIZE 100000000
#define THREADS 10
// DATASIZEはTHREADSの整数倍

int data[DATASIZE];

// pthread_getspecificなどで使うキー番号
pthread_key_t startIndexKey;
pthread_key_t endIndexKey;

void setRandomData(void)
{
    int ans = INT_MIN;
    for (int i = 0; i < DATASIZE; ++i) {
        data[i] = rand();
        if (ans < data[i]) {
            ans = data[i];
        }
    }
    printf("ANSWER: %d\n", ans);
}

int getMax()
{
    size_t startIndex = (size_t)pthread_getspecific(startIndexKey);
    size_t endIndex = (size_t)pthread_getspecific(endIndexKey);
    int max = data[startIndex];
    for (int i = startIndex; i < endIndex; ++i) {
        if (max < data[i]) {
            max = data[i];
        }
    }
    return max;
}

void* threadFunc(void* arg)
{
    int n = (int)arg;
    // スレッドローカル変数をセット
    size_t startIndex = (DATASIZE/THREADS)*n;
    size_t endIndex = startIndex + (DATASIZE/THREADS);
    pthread_setspecific(startIndexKey, (void*)startIndex);
    pthread_setspecific(endIndexKey, (void*)endIndex);

    int max = getMax();
    return (void*)max;
}

int main(int argc, char *argv[])
{
    pthread_t threads[THREADS];
    int res[THREADS];
    int max;

    srand(time(NULL));
    setRandomData();

    // スレッドローカル変数を作成
    pthread_key_create(&startIndexKey, NULL);
    pthread_key_create(&endIndexKey, NULL);

    // 並列処理
    for (int i = 0; i < THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, threadFunc, (void*)i) != 0) {
            printf("Error: Failed to create new thread.\n");
            exit(1);
        }
    }

    for (int i = 0; i < THREADS; ++i) {
        if (pthread_join(threads[i], (void**)&(res[i])) != 0) {
            printf("Error: Failed to wait for the thread termination.\n");
            exit(1);
        }
    }

    max = res[0];
    for (int i = 0; i < THREADS; ++i) {
        if (max < res[i]) {
            max = res[i];
        }
    }

    printf("Max value is %d\n", max);

    return 0;
}
