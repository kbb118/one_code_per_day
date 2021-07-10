#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "hasht.h"

#define INIT_SIZE (4096)

typedef struct HashEntry_ {
    uint64_t h; // raw hash value
    char *key;  // do not free
    void *data;
} HashEntry;

typedef struct HashTable_ {
    pthread_mutex_t mtx;

    int size;
    HashEntry **entries;
} HashTable;

/*
 *  FVN hash
 *  http://www.isthe.com/chongo/src/fnv/hash_64.c
 *  By:
 *      chongo <Landon Curt Noll> /\oo/\
 *      http://www.isthe.com/chongo/
 */
static inline uint64_t
hash(char *str)
{
    unsigned char *s = (unsigned char *)str;
    uint64_t hval = 0xcbf29ce484222325ULL;
    while ( *s )
    {
        hval += (hval << 1) + (hval << 4) + (hval << 5) +
            (hval << 7) + (hval << 8) + (hval << 40);
        hval ^= (uint64_t)*s++;
    }
    return hval;
}

HashTable*
hasht_init(void)
{
    HashTable *ret = malloc(sizeof(HashTable));
    ret->size = INIT_SIZE;
    ret->entries = calloc(INIT_SIZE, 1);
    return ret;
}

void*
hasht_insert(HashTable *t, char *key, void *data)
{
    // DON'T insert already exist key!!!

    // TODO rehash

    // TODO mutex lock/unlock

    HashEntry *new_ent = malloc(sizeof(HashEntry));
    new_ent->key = key;
    new_ent->h = hash(key);
    new_ent->data = data;

    int idx = new_ent->h % t->size;
    HashEntry *ent = t->entries[idx];

    // Open addressing.
    while ( ent )
    {
        // This must not occur.
        // assert( !(strcmp(ent->key, key) == 0) );

        idx = (idx+1)%t->size;
        ent = t->entries[idx];
    }
    t->entries[idx] = new_ent;
    return data;
}

void*
hasht_get(HashTable *t, char *key)
{
    // TODO mutex lock/unlock

    uint64_t h = hash(key);
    int idx = h % t->size;
    HashEntry *ent = t->entries[idx];

    // search Open addressing.
    while ( ent )
    {
        if ( strcmp(ent->key, key) == 0 )
            return ent->data;

        idx = (idx+1)%t->size;
        ent = t->entries[idx];
    }
    return NULL;
}
void*
hasht_get_or_insert(HashTable *t, char *key, void *data)
{
    void *ret = hasht_get(t, key);
    return ret ? ret : hasht_insert(t, key, data);
}

#ifdef TEST
#include <assert.h>

typedef struct {
    char *name;
    int num;
} Fruit;

Fruit *
harvest_fruit(char *name, int num)
{
    Fruit *f = malloc(sizeof(Fruit));
    f->name = name;
    f->num = num;
    return f;
}

int main(int argc, char *argv[])
{
    (void)argc, (void)argv;
    HashTable *t = hasht_init();

    char *k = "orange";
    Fruit *f = harvest_fruit(k, 100);
    hasht_insert(t, k, f);
    Fruit *g = hasht_get(t, k);
    assert(f == g);

    char *x = "grape";
    Fruit *y = harvest_fruit(k, 110);
    hasht_get_or_insert(t, x, y);
    Fruit *z = hasht_get(t, x);
    assert(y == z);

    // TODO more testing.

    return 0;
}
#endif

