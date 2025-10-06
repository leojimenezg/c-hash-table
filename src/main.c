#include <stdio.h>
#include "hash_table.h"

int main() {
	HashTable* ht = new_hash_table(10);
	printf("Hash Table buckets: %zu\n", ht->size);
	add_item(ht, "foo", "bar");
	add_item(ht, "bar", "foo");
	printf("Hash Table elements: %zu\n", ht->count);
	char* foo_value = get_item(ht, "foo");
	printf("Hash Table key %s: %s\n", "foo", foo_value);
	destroy_hash_table(ht);
	printf("Hash Table destroyed\n");
	return 0;
}
