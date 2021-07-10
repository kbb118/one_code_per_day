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
slist_new_(SListFreeFunc *free_func) {
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
ssize_t slist_append_(SList *s, void *data) {
    assert( s != NULL );
    Node *n = my_calloc(1, sizeof(Node));
    if ( !n )
        return false;
    n->data = data;

    if ( s->len == 0 )
        s->head = s->tail = n;
    else
        s->tail = s->tail->next = n;
    return ++s->len;
}
ssize_t slist_prepend_(SList *s, void *data) {
    assert( s != NULL );
    Node *n = my_calloc(1, sizeof(Node));
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
bool
slist_remove_(SList *s, void *data, SListCmpFunc *cmp_func) {
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
void*
slist_find_(SList *s, void *data, SListCmpFunc *cmp_func) {
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
        if ( cmp_func(a_cur->data, b_cur->data) <= 0 ) {
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

    return _merge(_sort(a, f, tpp), _sort(b, f, tpp), f, tpp);
}
void slist_sort_(SList *s, SListCmpFunc *cmp_func) {
    Node *new_tail = NULL;
    Node *new_head = _sort(s->head, cmp_func, &new_tail);
    s->head = new_head;
    s->tail = new_tail;
}

//
// 出力
//
void
slist_print_(SList *s, SListPrintFunc *print_func) {
    assert( s != NULL );
    for ( Node *i = s->head; i != NULL; i = i->next ) {
        print_func(i->data);
    }
}

#ifdef TEST
#include <string.h>
static void
_print_int(void *data) {
    printf("%ld\n", (int64_t)data);
}
static int
_cmp_int(void *a, void *b) {
    return (long)a - (long)b;
}
static void
_print_str(void *data) {
    printf("%s\n", (char*)data);
}

typedef struct {
    char *name;
    int num;
} Fruit;

Fruit *
harvest_fruit(char *name, int num)
{
    Fruit *f = malloc(sizeof(Fruit));
    f->name = strdup(name);
    f->num = num;
    return f;
}
void
eat_fruit(Fruit *f)
{
    free(f->name);
    free(f);
}
void
show_fruit(Fruit *f)
{
    printf("name:%s, num:%d\n", f->name, f->num);
}

int main(void) {
    SList *s = slist_new(NULL);
    slist_append(s, 1);
    slist_append(s, 5);
    slist_append(s, 7);
    slist_append(s, 9);
    slist_append(s, 19);
    slist_append(s, 1);

    printf("List len is %lu\n", slist_len(s));

    slist_print(s, _print_int);
    slist_sort(s, _cmp_int);
    printf("sorted.\n");
    slist_print(s, _print_int);

    slist_delete(s);

    SList *s1 = slist_new(NULL);
    slist_append(s1, "John");
    slist_append(s1, "Meraki");
    slist_append(s1, "Hervey");
    slist_append(s1, "Dave");

    printf("List len is %lu\n", slist_len(s1));

    slist_print(s1, _print_str);
    slist_sort(s1, (SListCmpFunc*)strcmp);
    printf("sorted.\n");
    slist_print(s1, _print_str);

    slist_delete(s1);


    SList *basket = slist_new(eat_fruit);
    slist_append(basket, harvest_fruit("orange", 100));
    slist_prepend(basket, harvest_fruit("kiwi", 10));
    slist_prepend(basket, harvest_fruit("banana", 2));
    slist_append(basket, harvest_fruit("mango", 1));
    slist_prepend(basket, harvest_fruit("meron", 30));
    slist_prepend(basket, harvest_fruit("grape", 140));
    slist_append(basket, harvest_fruit("peach", 180));
    slist_append(basket, harvest_fruit("orange", 800));
    slist_print(basket, show_fruit);

    slist_delete(basket);

    return 0;
}
#endif
