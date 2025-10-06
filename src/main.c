#include <stdio.h>
#include "hash_table.h"

int main() {
	HashTable* ht = new_hash_table(10);
	printf("Hash Table buckets: %zu\n", ht->size);
	add_item(ht, "balls", "hot");
	add_item(ht, "hot", "balls");
	printf("Hash Table elements: %zu\n", ht->count);
	destroy_hash_table(ht);
	printf("Hash Table destroyed\n");
	return 0;
}
