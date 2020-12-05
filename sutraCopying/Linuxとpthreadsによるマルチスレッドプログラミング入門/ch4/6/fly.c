#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define WIDTH 78
#define HEIGHT 23
#define MAX_FLY 6
const char *flyMarkList = "o@*+.#";
#define DRAW_CYCLE 50
#define MIN_SPEED 1.0
#define MAX_SPEED 20.0

int stopRequest;

/* ミリ秒単位のスリーブ */
void mSleep(int msec)
{
    struct timespec ts;
    ts.tv_sec = msec/1000;
    ts.tv_nsec = (msec%1000)*1000*1000;
    nanosleep(&ts, NULL);
}

double randDouble(double min, double max)
{
    return min + (double)rand()/((double)RAND_MAX+1)*(max-min);
}

/* 画面再描画 */
void clearScreen(void) { fputs("\033[2J", stdout); }
void moveCursor(int x, int y) { printf("\033[%d;%dH", y, x); }


/* ハエ構造体 */
typedef struct {
    char mark;
    double x,y;
    double angle;
    double speed;
    pthread_mutex_t mutex;
} Fly;
Fly flyList[MAX_FLY];

void flyInitRandom(Fly *fly, char mark_)
{
    pthread_mutex_init(&fly->mutex, NULL);
    fly->mark = mark_;
    fly->x = randDouble(0, WIDTH-1);
    fly->y = randDouble(0, HEIGHT-1);
    fly->angle = randDouble(0, M_2_PI);
    fly->speed = randDouble(MIN_SPEED, MAX_SPEED);
}
void flyDestroy(Fly *fly)
{
    pthread_mutex_destroy(&fly->mutex);
}
void flyMove(Fly *fly)
{
    pthread_mutex_lock(&fly->mutex);
    fly->x += cos(fly->angle);
    fly->y += sin(fly->angle);
    /* 縁にぶつかったら折り返す */
    if (fly->x < 0) {
        fly->x = 0;
        fly->angle = M_PI - fly->angle;
    } else if (fly->x > WIDTH-1) {
        fly->x = WIDTH-1;
        fly->angle = M_PI - fly->angle;
    }
    if (fly->y < 0) {
        fly->y = 0;
        fly->angle = -fly->angle;
    } else if (fly->y > HEIGHT-1) {
        fly->y = HEIGHT-1;
        fly->angle = -fly->angle;
    }
    pthread_mutex_unlock(&fly->mutex);
}
int flyIsAt(Fly *fly, int x, int y) {
    int res;
    pthread_mutex_lock(&fly->mutex);
    res = ((int)(fly->x) == x) && ((int)(fly->y) == y);
    pthread_mutex_unlock(&fly->mutex);
    return res;
}

/* ハエを動かし続けるスレッド */
void* doMove(void *arg)
{
    Fly *fly = (Fly*)arg;
    while (!stopRequest) {
        flyMove(fly);
        mSleep((int)(1000.0/fly->speed));
    }
    return NULL;
}

/* スクリーンを描画する */
void drawScreen(void)
{
    moveCursor(0, 0);
    for (int y = 0;  y < HEIGHT; y++) {
        for (int x = 0;  x < WIDTH; x++) {
            char ch = 0;
            for (int i = 0; i < MAX_FLY; ++i) {
                if (flyIsAt(&flyList[i], x, y)) {
                    ch = flyList[i].mark;
                    break;
                }
            }
            if (ch != 0)
                putchar(ch);
            else if ((y == 0) || (y == HEIGHT-1))
                putchar('-');
            else if ((x == 0) || (x == WIDTH-1))
                putchar('|');
            else
                putchar(' ');
        }
        putchar('\n');
    }
}
/* スクリーンを描画し続けるスレッド */
void* doDraw(void *arg)
{
    while (!stopRequest) {
        drawScreen();
        mSleep(DRAW_CYCLE);
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t drawThread;
    pthread_t moveThread[MAX_FLY];
    char buf[40];

    /* init */
    srand((unsigned int)time(NULL));
    clearScreen();
    for (int i = 0; i < MAX_FLY; ++i) {
        flyInitRandom(&flyList[i], flyMarkList[i]);
    }

    for (int i = 0; i < MAX_FLY; ++i) {
        if (pthread_create(&moveThread[i], NULL, doMove, (void*)&flyList[i]) != 0) {
            printf("Error: Failed to create new thead.\n");
            exit(1);
        }
    }
    if (pthread_create(&drawThread, NULL, doDraw, NULL) != 0) {
        printf("Error: Failed to create new thead.\n");
        exit(1);
    }

    /* press any key to stop */
    fgets(buf, sizeof(buf), stdin);
    stopRequest = 1;

    if (pthread_join(drawThread, NULL) != 0) {
        printf("Error: Failed to wait for the thread termination.\n");
        exit(1);
    }
    for (int i = 0; i < MAX_FLY; ++i) {
        if (pthread_join(moveThread[i], NULL) != 0) {
            printf("Error: Failed to wait for the thread termination.\n");
            exit(1);
        }
        flyDestroy(&flyList[i]);
    }

    return 0;
}
