#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

typedef void (*FreeFunction)(void*);
typedef unsigned long (*HashFunction)(const void* key);

struct HashTable;

struct HashTable* map_init(
    size_t size,
    HashFunction hashFunction,
    FreeFunction keyFreeFunction,
    FreeFunction valueFreeFunction
);

void map_insert(struct HashTable* hashTable, const void* key, const void* value);
const void* map_get(struct HashTable* hashTable, const void* key);
void map_free(struct HashTable* hashTable);

#endif // HASH_TABLE_H
