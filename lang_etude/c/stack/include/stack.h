#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>
#include <stdint.h>

#define DECL_SSTACK(T, N)                                 \
typedef struct {                                          \
    uint64_t top;                                         \
    T        data_[N];                                    \
} SStack_##N;                                             \
static inline T                                           \
SSTACK_##N##_PUSH(SStack_##N *s, T data) {                \
    if ( s->top == sizeof(s->data_)/sizeof(T) )           \
    {                                                     \
        T ret = { 0 };                                    \
        return ret;                                       \
    }                                                     \
    else                                                  \
        return s->data_[++(s->top)] = data;               \
}                                                         \
static inline T                                           \
SSTACK_##N##_POP(SStack_##N *s) {                         \
    if ( s->top == 0 )                                    \
    {                                                     \
        T ret = { 0 };                                    \
        return ret;                                       \
    }                                                     \
    else                                                  \
        return s->data_[(s->top)--];                      \
}

typedef struct Stack_ {
    uint64_t size;
    uint64_t top;
    void **data_;
} Stack;

static inline void
stack_delete(Stack *s) {
    if ( s )
        free(s->data_);
    free(s);
}
static inline Stack*
stack_new(uint64_t size) {
    Stack *s = malloc(sizeof(Stack));
    if ( !s )
        goto ERR;
    s->size = size;
    s->top = 0;
    s->data_ = malloc(sizeof(void*) * size);
    if ( !s->data_ )
        goto ERR;
    return s;
ERR:
    stack_delete(s);
    return NULL;
}

#define STACK_PUSH(S, D, TYPE) (TYPE)stack_push((S), (void*)(D));
#define STACK_POP(S, TYPE)     (TYPE)stack_pop((S));

static inline void*
stack_push(Stack *s, void *data) {
    if ( s->top == s->size )
        return NULL;
    else
        return s->data_[++(s->top)] = data;
}
static inline void*
stack_pop(Stack *s) {
    if ( s->top == 0 )
        return NULL;
    else
        return s->data_[(s->top)--];
}

#endif /* ifndef __STACK_H__ */
