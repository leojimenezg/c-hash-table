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
 * @brief Creates a new Hash Table with specified initial capacity.
 * 
 * Allocates and initializes a new Hash Table with the given initial size.
 * If init_size is 0, defaults to 256 buckets. Uses separate chaining 
 * for collision resolution.
 * 
 * @param init_size Initial number of buckets. Use 0 for default (256).
 * @return Pointer to the newly created Hash Table, or NULL if allocation fails.
 * 
 * @note The returned Hash Table must be freed with destroy_hash_table().
 * @see destroy_hash_table()
 */
HashTable* new_hash_table(size_t init_size);

/**
 * @brief Destroys a Hash Table and frees all associated memory.
 * 
 * Frees all items (including their keys and values), the bucket array,
 * and the Hash Table structure itself. After calling this function,
 * the Hash Table pointer becomes invalid.
 * 
 * @param ht Pointer to the Hash Table to destroy. Must not be NULL.
 * 
 * @warning Accessing the Hash Table after destruction results in undefined behavior.
 * @see new_hash_table()
 */
void destroy_hash_table(HashTable* ht);

/**
 * @brief Inserts a new key-value pair or updates an existing key.
 * 
 * If the key already exists, replaces its value with the new one.
 * If the key doesn't exist, creates a new entry. Both key and value
 * are copied internally, so the caller retains ownership of the originals.
 * 
 * @param ht Pointer to the Hash Table. Must not be NULL.
 * @param key String key to insert or update. Must not be NULL.
 * @param value String value to associate with the key. Must not be NULL.
 * @return 0 if a new item was added,
 *         1 if an existing item was updated,
 *        -1 if memory allocation failed.
 */
int add_item(HashTable* ht, const char* key, const char* value);

/**
 * @brief Retrieves the value associated with a key.
 * 
 * Searches for the given key in the Hash Table and returns its associated value.
 * The returned pointer points to the internal storage and should not be freed
 * or modified by the caller.
 * 
 * @param ht Pointer to the Hash Table. Must not be NULL.
 * @param key String key to search for. Must not be NULL.
 * @return Pointer to the value string if found, or NULL if the key doesn't exist.
 * 
 * @warning Do not free or modify the returned string. It's owned by the Hash Table.
 */
char* get_item(HashTable* ht, const char* key);

/**
 * @brief Removes a key-value pair from the Hash Table.
 * 
 * Searches for the given key and removes it along with its associated value
 * if found. Frees all memory associated with the removed item.
 * 
 * @param ht Pointer to the Hash Table. Must not be NULL.
 * @param key String key to delete. Must not be NULL.
 * @return 0 if the item was successfully deleted,
 *        -1 if the key was not found.
 */
int delete_item(HashTable* ht, const char* key);

#endif
