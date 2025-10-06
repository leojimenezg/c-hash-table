#include <stdio.h>
#include "hash_table.h"

int main() {
    printf("=== Creating Hash Table ===\n");
    HashTable* ht = new_hash_table(10);
    printf("Hash Table created with %zu buckets\n\n", ht->size);
    
    printf("=== Inserting items ===\n");
    add_item(ht, "foo", "bar");
    add_item(ht, "name", "Alice");
    add_item(ht, "age", "25");
    add_item(ht, "city", "Paris");
    printf("Elements inserted: %zu\n", ht->count);
    
    printf("=== Searching items ===\n");
    char* value = get_item(ht, "foo");
    printf("foo = %s\n", value ? value : "NOT FOUND");
    
    value = get_item(ht, "name");
    printf("name = %s\n", value ? value : "NOT FOUND");
    
    value = get_item(ht, "age");
    printf("age = %s\n", value ? value : "NOT FOUND");
    
    value = get_item(ht, "nonexistent");
    printf("nonexistent = %s\n\n", value ? value : "NOT FOUND");
    
    printf("=== Updating item ===\n");
    int result = add_item(ht, "foo", "updated_bar");
    printf("foo updated (return code %d)\n", result);
    value = get_item(ht, "foo");
    printf("foo = %s\n\n", value);
    
    printf("=== Deleting items ===\n");
    result = delete_item(ht, "age");
    printf("age deleted (return code %d)\n", result);
    printf("Remaining elements: %zu\n", ht->count);
    
    value = get_item(ht, "age");
    printf("age = %s\n\n", value ? value : "NOT FOUND");
    
    result = delete_item(ht, "nonexistent");
    printf("Trying to delete 'nonexistent' (return code %d)\n\n", result);
    
    printf("=== Destroying Hash Table ===\n");
    destroy_hash_table(ht);
    printf("Hash Table destroyed successfully\n");
    
    return 0;
}
