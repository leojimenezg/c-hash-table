#include "hash_table.h"

#define DEFAULT_SIZE 256

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
