#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 256
#define MAX_LOAD_FACTOR 0.75

HashTable* new_hash_table(size_t init_size) {
	HashTable* new_ht = (HashTable*)malloc(sizeof(HashTable));
	if (new_ht == NULL) return NULL;
	if (init_size == 0) {
		init_size = DEFAULT_SIZE;
	}
	new_ht->buckets = calloc(init_size, sizeof(Item*)); 
	if (new_ht->buckets == NULL ) {
		free(new_ht);
		return NULL;
	}
	new_ht->size = init_size;
	new_ht->count = 0;
	return new_ht;
}

void destroy_hash_table(HashTable* ht) {
	if (ht == NULL) return;
	for (size_t i = 0; i < ht->size; i++) {
		Item* current = ht->buckets[i];
		while (current != NULL) {
			Item* next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = next;
		}
	}
	free(ht->buckets);
	free(ht);
}

static unsigned long hash_function(const char* str, size_t size) {
	unsigned long hash = 5381;
	int c;
	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c;
	}
	return hash % size;
}

static double get_load_factor(HashTable* ht) {
	return (double)ht->count / (double)ht->size;
}

/**
 * @brief Searches for a specific key within a bucket's linked list.
 * 
 * Traverses the linked list starting from the given item, comparing each
 * item's key with the target key using string comparison.
 * 
 * @param first_item Pointer to the first item in the bucket's linked list.
 *                   Can be NULL if the bucket is empty.
 * @param key String key to search for. Must not be NULL.
 * @return Pointer to the Item containing the matching key, or NULL if not found.
 * 
 * @note This is an internal helper function for Hash Table operations.
 */
static Item* search_bucket_items(Item* first_item, const char* key) {
	while (first_item != NULL) {
		if (strcmp(first_item->key, key) == 0) {
			return first_item;
		}
		first_item = first_item->next;
	}
	return NULL;
}

/**
 * @brief Doubles the Hash Table capacity and rehashes all items.
 * 
 * Creates a new bucket array with double the capacity, recalculates the hash
 * for each item with the new size, and relinks existing items into the new
 * array. The old bucket array is freed, but items are reused (not copied).
 * 
 * @param ht Pointer to the Hash Table to resize. Must not be NULL.
 * @return 0 on success, -1 if memory allocation fails.
 * 
 * @note This is an internal helper function called when load factor exceeds threshold.
 * @note Item count remains unchanged; only the bucket array is resized.
 */
static int resize_hash_table(HashTable* ht) {
	size_t new_size = ht->size * 2;
	Item** new_buckets = calloc(new_size, sizeof(Item*));
	if (new_buckets == NULL) return -1;
	for (size_t i = 0; i < ht->size; i++) {
		Item *current = ht->buckets[i];
		while (current != NULL) {
			unsigned long new_index = hash_function(current->key, new_size);
			Item* next = current->next;
			current->next = new_buckets[new_index];
			new_buckets[new_index] = current;
			current = next;
		}
	}
	free(ht->buckets);
	ht->buckets = new_buckets;
	ht->size = new_size;
	return 0;
}

int add_item(HashTable* ht, const char* key, const char* value) {
	unsigned long index = hash_function(key, ht->size);
	Item* item = search_bucket_items(ht->buckets[index], key);
	if (item != NULL) {
		free(item->value);
		item->value = malloc(strlen(value) + 1);
		strcpy(item->value, value);
		return 1;
	}
	item = malloc(sizeof(Item));
	if (item == NULL) return -1;
	item->key = malloc(strlen(key) + 1);
	if (item->key == NULL) {
		free(item);
		return -1;
	}
	strcpy(item->key, key);
	item->value = malloc(strlen(value) + 1);
	if (item->value == NULL) {
		free(item);
		free(item->key);
		return -1;
	}
	strcpy(item->value, value);
	item->next = ht->buckets[index];
	ht->buckets[index] = item;
	ht->count++;
	if (get_load_factor(ht) >= MAX_LOAD_FACTOR) resize_hash_table(ht);
	return 0;
}

char* get_item(HashTable* ht, const char* key) {
	unsigned long index = hash_function(key, ht->size);
	Item* item = search_bucket_items(ht->buckets[index], key);
	if (item == NULL) return NULL;
	return item->value;
}

int delete_item(HashTable* ht, const char* key) {
	unsigned long index = hash_function(key, ht->size);
	Item* prev = ht->buckets[index];
	if (prev == NULL) return -1;
	if (strcmp(prev->key, key) == 0) {
		ht->buckets[index] = prev->next;
		free(prev->key);
		free(prev->value);
		free(prev);
		ht->count--;
		return 0;
	}
	Item* current = prev->next;
	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			ht->count--;
			return 0;
		}
		prev = current;
		current = current->next;
	}
	return -1;
}
