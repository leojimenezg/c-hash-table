#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 256
#define MAX_LOAD_FACTOR 0.65

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
* @brief Searches the items of a bucket of a key.
* "search_bucket_items" searches all of the items from a bucket looking for an
* specific key. It expects to start at the first item of the bucket.
* @param first_item First item of the bucket.
* @param key Key to look up for.
* @return The Item where the key matches, o NULL if not found.
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

int add_item(HashTable* ht, const char* key, const char* value) {
	// if (get_load_factor(ht) >= MAX_LOAD_FACTOR) { /* Resize HashTable */ }
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

void resize_hash_table();
