#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

typedef struct Item {
    char* key;
    char* value;
    struct Item* next;
} Item;

typedef struct HashTable {
    size_t size;
    size_t count;
    Item** buckets;
} HashTable;

HashTable* new_hash_table(size_t init_size);

void destroy_hash_table(HashTable* ht);

#endif
