#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/time.h>

#include "logger.h"
#include "stack.h"

#define STACK_LEN (100)
DECL_SSTACK(struct timeval, 100);
typedef struct Logger {
    SStack_100 s;
} Logger;

Logger*
logger_create(void) {
    Logger *l = malloc(sizeof(Logger));
    if (  !l )
        return NULL;
    return l;
}
bool
logger_start(Logger *l) {
    struct timeval tv;
    if ( gettimeofday(&tv, NULL) < 0 )
    {
        perror("gettimeofday");
        return false;
    }
    struct timeval ret = SSTACK_100_PUSH(&l->s, tv);
    if ( ret.tv_sec == 0 && ret.tv_usec == 0 )
    {
        assert(0 && "Logger stack full!!!");
        return false;
    }
    return true;
}
bool
logger_end(Logger *l) {
    struct timeval end;
    if ( gettimeofday(&end, NULL) < 0 )
    {
        perror("gettimeofday");
        return false;
    }
    struct timeval start = SSTACK_100_POP(&l->s);
    if ( start.tv_sec == 0 && start.tv_usec == 0 )
    {
        assert(0 && "Logger stack empty!!!");
        return false;
    }

    struct timeval res;
    timersub(&end, &start, &res);
    double elapsed =((double)res.tv_sec * 1000000 + res.tv_usec) / 1000000;
    fprintf(stderr, "Elapsed %f sec\n", elapsed);

    return true;
}

#ifdef TEST
int main(int argc, char *argv[])
{
    (void)argc, (void)argv;

    Logger *l = logger_create();

    logger_start(l);
    sleep(1);
    logger_start(l);
    sleep(2);
    logger_end(l);
    logger_end(l);

    return 0;
}
#endif
