#include "hash_table.h"
#include <stdlib.h>

struct MapPair {
    void* key;
    void* value;
    struct MapPair* next;
};

struct HashTable {
    size_t size;
    struct MapPair** table;
    HashFunction hashFunction;
    FreeFunction keyFreeFunction;
    FreeFunction valueFreeFunction;
};

static struct MapPair* createPair(const void* key, const void* value) {
    struct MapPair* pair = malloc(sizeof(struct MapPair));
    if (!pair) return NULL;

    pair->key = (void*)key;
    pair->value = (void*)value;
    pair->next = NULL;
    return pair;
}

struct HashTable* map_init(
    size_t size,
    HashFunction hashFunction,
    FreeFunction keyFreeFunction,
    FreeFunction valueFreeFunction
) {
    if (!hashFunction || size == 0) return NULL;

    struct HashTable* hashTable = malloc(sizeof(struct HashTable));
    if (!hashTable) return NULL;

    hashTable->size = size;
    hashTable->table = calloc(size, sizeof(struct MapPair*));
    hashTable->hashFunction = hashFunction;
    hashTable->keyFreeFunction = keyFreeFunction;
    hashTable->valueFreeFunction = valueFreeFunction;

    return hashTable;
}

void map_insert(struct HashTable* hashTable, const void* key, const void* value) {
    if (!hashTable || !key) return;

    unsigned long index = hashTable->hashFunction(key) % hashTable->size;
    struct MapPair* pair = createPair(key, value);
    if (!pair) return;

    pair->next = hashTable->table[index];
    hashTable->table[index] = pair;
}

const void* map_get(struct HashTable* hashTable, const void* key) {
    if (!hashTable || !key) return NULL;

    unsigned long index = hashTable->hashFunction(key) % hashTable->size;
    struct MapPair* current = hashTable->table[index];

    while (current) {
        if (current->key == key)
            return current->value;
        current = current->next;
    }

    return NULL;
}

void map_free(struct HashTable* hashTable) {
    if (!hashTable) return;

    for (size_t i = 0; i < hashTable->size; i++) {
        struct MapPair* current = hashTable->table[i];
        while (current) {
            struct MapPair* temp = current;
            current = current->next;

            if (hashTable->keyFreeFunction)
                hashTable->keyFreeFunction(temp->key);
            if (hashTable->valueFreeFunction)
                hashTable->valueFreeFunction(temp->value);

            free(temp);
        }
    }

    free(hashTable->table);
    free(hashTable);
}
