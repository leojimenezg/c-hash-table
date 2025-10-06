#include <stdio.h>
#include <string.h>
#include "hash_table.h"

int main() {
    printf("=== Creating Hash Table ===\n");
    HashTable* ht = new_hash_table(4);  // Start small to trigger resize quickly
    printf("Hash Table created with %zu buckets\n", ht->size);
    
    printf("=== Testing Dynamic Resizing ===\n");
    const char* keys[] = {"name", "age", "city", "country", "email", "phone", 
                          "address", "zip", "state", "occupation"};
    const char* values[] = {"Andrea", "21", "Mexico", "Mexico", 
                            "andrea@example.com", "442-555-1234", 
                            "Av. 5 de Febrero 123", "76000", "Querétaro", "Nurse"};
    
    for (int i = 0; i < 10; i++) {
        size_t prev_size = ht->size;
        printf("Inserting item %d: %s = %s\n", i + 1, keys[i], values[i]);
        add_item(ht, keys[i], values[i]);
        printf("  Elements: %zu | Buckets: %zu\n", ht->count, ht->size);
        if (ht->size > prev_size) {
            printf("  >>> RESIZE TRIGGERED! New size: %zu <<<\n", ht->size);
        }
        printf("\n");
    }
    
    printf("=== Verifying all items after resize ===\n");
    for (int i = 0; i < 10; i++) {
        char* value = get_item(ht, keys[i]);
        printf("%s = %s %s\n", keys[i], value ? value : "NOT FOUND",
               value && strcmp(value, values[i]) == 0 ? "✓" : "✗");
    }
    printf("\n");
    
    printf("=== Searching items ===\n");
    char* value = get_item(ht, "name");
    printf("name = %s\n", value ? value : "NOT FOUND");
    
    value = get_item(ht, "city");
    printf("city = %s\n", value ? value : "NOT FOUND");
    
    value = get_item(ht, "nonexistent");
    printf("nonexistent = %s\n\n", value ? value : "NOT FOUND");
    
    printf("=== Updating item ===\n");
    int result = add_item(ht, "age", "29");
    printf("age updated (return code %d)\n", result);
    value = get_item(ht, "age");
    printf("age = %s\n\n", value);
    
    printf("=== Deleting items ===\n");
    result = delete_item(ht, "zip");
    printf("zip deleted (return code %d)\n", result);
    printf("Remaining elements: %zu\n", ht->count);
    
    printf("=== Final Stats ===\n");
    printf("Total elements: %zu\n", ht->count);
    printf("Total buckets: %zu\n", ht->size);
    
    printf("=== Destroying Hash Table ===\n");
    destroy_hash_table(ht);
    printf("Hash Table destroyed successfully\n");
    
    return 0;
}
