#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "slist.h"

#define my_malloc(SIZE) \
            dbg_malloc(SIZE, __FILE__, __LINE__, __func__)
#define my_calloc(NMEMB, SIZE) \
            dbg_calloc(NMEMB, SIZE, __FILE__, __LINE__, __func__)
static inline void*
dbg_malloc(size_t size, const char *file, int line, const char *func) {
    void *ret = malloc(size);
    if ( ret == NULL ) {
        fprintf(stderr,
            "%s:%d %s Memory allocation error (%lu bytes)\n",
            file, line, func, size);
    }
    return ret;
}
static inline void*
dbg_calloc(size_t nmemb, size_t size, const char *file, int line, const char *func) {
    void *ret = calloc(nmemb, size);
    if ( ret == NULL ) {
        fprintf(stderr,
            "%s:%d %s Memory allocation error (%lu bytes)\n",
            file, line, func, size);
    }
    return ret;
}

typedef struct Node_ {
    struct Node_ *next;
    void *data;
} Node;

struct SList_ {
    size_t len;
    Node *head;
    Node *tail;
    SListFreeFunc *free_func;
};

//
// アクセサ
//
#define DECL_SLIST_GETTER(T, memb)  \
T                                   \
slist_##memb(SList *s) {            \
    assert( s != NULL );            \
    return s->memb;                 \
}
DECL_SLIST_GETTER(size_t, len);
DECL_SLIST_GETTER(void*, head);
DECL_SLIST_GETTER(void*, tail);

//
// 生成/破棄
//
void
slist_delete(SList *s) {
    assert( s != NULL );
    if ( s->len != 0 ) {
        Node *saved_next = s->head->next;
        for ( Node *i = s->head; i != NULL; i = saved_next ) {
            saved_next = i->next;
            if ( s->free_func )
                s->free_func(i->data);
            free(i);
        }
    }
    free(s);
}
SList*
slist_new(SListFreeFunc *free_func) {
    SList *s = my_calloc(1, sizeof(SList));
    if ( !s )
        return NULL;
    else {
        s->free_func = free_func;
        return s;
    }
}

//
// 追加/削除/検索/整列
//
ssize_t slist_append(SList *s, void *data) {
    assert( s != NULL );
    Node *n = my_calloc(1, sizeof(void*));
    if ( !n )
        return false;
    n->data = data;

    if ( s->len == 0 )
        s->head = s->tail = n;
    else
        s->tail = s->tail->next = n;
    return ++s->len;
}
ssize_t slist_prepend(SList *s, void *data) {
    assert( s != NULL );
    Node *n = my_calloc(1, sizeof(void*));
    if ( !n )
        return false;
    n->data = data;

    if ( s->len == 0 )
        s->head = s->tail = n;
    else {
        n->next = s->head;
        s->head = n;
    }
    return ++s->len;
}
// リストから data に最初にマッチするの Node を検索。 O(n)
//   削除のしやすさのために見つかった Node の一つ前を返す。
//   つまり head を検索することができない。
//   見つからない場合は NULL を返す
static inline Node*
_find_node(SList *s, void *data, SListCmpFunc *cmp_func) {
    for ( Node *i = s->head; i->next != NULL; i = i->next ) {
        if ( cmp_func(data, i->next) == 0 )
            return i;
    }
    return NULL;
}
bool slist_remove(SList *s, void *data, SListCmpFunc *cmp_func) {
    assert( cmp_func );

    Node *found = NULL;
    // _find_node では先頭を検索できないのであらかじめ。
    if ( cmp_func(data, s->head->data) == 0 ) {
        found = s->head;
        s->head = found->next;
    }
    else {
        // NOTE: _find_node はマッチした奴の一つ前を返す！！！
        Node *n = _find_node(s, data, cmp_func);
        if ( !n )
            return false;
        assert( n->next != NULL );
        found = n->next;
        n->next = found->next;
    }

    if ( s->free_func )
        s->free_func(found->data);
    free(found);
    s->len--;
    return true;
}
void* slist_find(SList *s, void *data, SListCmpFunc *cmp_func) {
    assert( cmp_func );

    Node *found = NULL;
    // _find_node では先頭を検索できないのであらかじめ。
    if ( cmp_func(data, s->head->data) == 0 )
        found = s->head;
    else {
        // NOTE: _find_node はマッチした奴の一つ前を返す！！！
        Node *n = _find_node(s, data, cmp_func);
        if ( !n )
            return NULL;
        assert( n->next != NULL );
        found = n->next;
    }
    return found->data;
}
static Node*
_merge(Node* a, Node *b, SListCmpFunc *cmp_func, Node** p_new_tail) {
    Node dummy;
    Node *tail = &dummy;
    Node *a_cur = a;
    Node *b_cur = b;
    while ( a_cur != NULL && b_cur != NULL ) {
        if ( cmp_func(a->data, b->data) <= 0 ) {
            tail = tail->next = a_cur;
            a_cur = a_cur->next;
        }
        else {
            tail = tail->next = b_cur;
            b_cur = b_cur->next;
        }
    }
    tail->next = a_cur ? a_cur : b_cur;
    while ( tail->next != NULL )
        tail = tail->next;
    *p_new_tail = tail;

    return dummy.next;
}
static Node*
_sort(Node* head, SListCmpFunc *f, Node** tpp) {
    if ( head->next == NULL )
        return head;

    Node *a, *a_tail, *b, *tmp;
    a = a_tail = b = tmp = head;

    while ( tmp != NULL ) {
        a_tail = b;
        b = b->next;
        tmp = tmp->next;
        if ( tmp )
            tmp = tmp->next;
    }
    a_tail->next = NULL;

    return _merge(_sort(a, f, tpp), _sort(a,f, tpp), f, tpp);
}
void slist_sort(SList *s, SListCmpFunc *cmp_func) {
    Node *new_tail = NULL;
    Node *new_head = _sort(s->head, cmp_func, &new_tail);
    s->head = new_head;
    s->tail = new_tail;
}


#ifdef TEST
int main(int argc, char *argv[]) {
    SList *s = slist_new();

    slist_append(s, 1);
    slist_append(s, 5);
    slist_append(s, 7);
    slist_append(s, 9);
    slist_append(s, 19);
    slist_append(s, 1);

    slist_len(s);

    slist_sort(s, slist_cmp_int);


    slist_delete(s);



    return 0;
}
#endif
