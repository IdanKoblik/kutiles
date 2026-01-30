#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

unsigned long int_hash(const void* key) {
    return *(const int*)key;
}

void test_insert_and_get() {
    struct HashTable* map = map_init(16, int_hash, NULL, NULL);

    int key = 42;
    int value = 1337;

    map_insert(map, &key, &value);

    const int* result = map_get(map, &key);
    assert(result != NULL);
    assert(*result == 1337);

    map_free(map);
}

void test_missing_key() {
    struct HashTable* map = map_init(8, int_hash, NULL, NULL);

    int key = 7;
    assert(map_get(map, &key) == NULL);

    map_free(map);
}

int main() {
    test_insert_and_get();
    test_missing_key();

    printf("All hash table tests passed ✅\n");
    return 0;
}
