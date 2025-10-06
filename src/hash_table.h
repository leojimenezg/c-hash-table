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

/**
* @brief Creates a Hash Table
* "new_hash_table" creates and allocates all the initial necessary memory to work with
* a new empty Hast Table.
* @param init_size Initial size of the underlying array. It's default value is 256.
* @return A pointer to the created Hash Table.
*/
HashTable* new_hash_table(size_t init_size);

/**
* @brief Destroys a Hash Table
* "destroy_hash_table" frees all the allocated memory to work with a Hash Table.
* @param ht Hash Table to be destroyed (freed).
*/
void destroy_hash_table(HashTable* ht);

/**
* @brief Adds a new item or updates an existing one.
* "add_item" adds a new item (key-value) to the Hash Table, or updated the value of the
* key if it already exists.
* @param ht Created Hash Table.
* @param key Key to map.
* @param value Value to assign to the key.
* @return 0 if added successfully, 1 if updated, and -1 if fails.
*/
int add_item(HashTable* ht, const char* key, const char* value);

/**
* @brief Gets the value of a key in the Hash Table.
* "get_item" gets the value of a key if it exists, otherwise returns a NULL value.
* @param ht Hash Table to search.
* @param key Key to look up for.
* @return The value of a key if found, or NULL if not found.
*/
char* get_item(HashTable* ht, const char* key);

#endif
