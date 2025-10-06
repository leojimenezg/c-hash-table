#include <stdio.h>
#include "hash_table.h"

int main() {
	HashTable* ht = new_hash_table(10);
	printf("Hash Table buckets: %zu\n", ht->size);
	destroy_hash_table(ht);
	printf("Hash Table destroyed\n");
	return 0;
}
