// String hash
// Open addressing.

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdint.h>

typedef struct HashTable_ HashTable;

/* ../src/hash_table.c */
extern HashTable *hasht_init(void);
extern void *hasht_insert(HashTable *t, char *key, void *data);
extern void *hasht_get(HashTable *t, char *key);
extern void *hasht_get_or_insert(HashTable *t, char *key, void *data);

#endif /* ifndef __HASH_TABLE_H__ */
