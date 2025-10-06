# C Hash Table

A simple and efficient hash table implementation in C from scratch, featuring dynamic resizing, separate chaining for collision resolution, and the djb2 hash function.

## Features
* **Dynamic Resizing**: Automatically doubles capacity when load factor exceeds 0.75
* **Collision Resolution**: Uses separate chaining with linked lists
* **djb2 Hash Function**: Fast and well-distributed hash algorithm by Daniel J. Bernstein
* **Simple API**: Easy-to-use functions for insert, search, update, and delete operations
* **Configurable**: Customizable initial size

## Installation
### Prerequisites
Before anything else, make sure you have installed **C99** (or newer) and a compatible compiler like **GCC** or **Clang** in your system. 

### Steps
1. **Clone the repository:**
Open your prefered terminal and clone the project to your local machine.
    ```bash
    git clone https://github.com/leojimenezg/c-hash-table.git
    ```
2. **Navigate into the project directory:**
    ```bash
    cd c-hash-table
    ```
3. **Build the project**
Choose the compilation method that applies to your setup.
    * If you compile using GCC:
        ```bash
        gcc -o main src/main.c src/hash_table.c
        ```
    * If you compile using Clang:
        ```bash
        clang -o src/main src/main.c src/hash_table.c
        ```
4. **Run the application**
Finally, execute the generated object file to test the C Hash Table Program.
    ```bash
    ./src/main
    ```

## Get Started
### Basic Usage
```C
#include "hash_table.h"

int main() {
    // Create a hash table with default size (256 buckets)
    HashTable* ht = new_hash_table(0);
    
    // Insert key-value pairs
    add_item(ht, "name", "Andrea");
    add_item(ht, "country", "Mexico");
    
    // Retrieve values
    char* name = get_item(ht, "name");
    printf("Name: %s\n", name);  // Output: Name: Andrea
    
    // Update existing value
    add_item(ht, "name", "Andrea Amaro");
    
    // Delete an item
    delete_item(ht, "city");
    
    // Clean up
    destroy_hash_table(ht);
    
    return 0;
}
```

## Functions
### `HashTable* new_hash_table(size_t init_size)`
Creates a new hash table with the specified initial capacity.

**Parameters:**
* `init_size`: Initial number of buckets. Use `0` for default size (256).

**Returns:** Pointer to the newly created hash table, or `NULL` if allocation fails.

**Example:**
```c
HashTable* ht = new_hash_table(128);  // Custom size
HashTable* ht2 = new_hash_table(0);   // Default size (256)
```

### `void destroy_hash_table(HashTable* ht)`

Destroys the hash table and frees all associated memory.

**Parameters:**
* `ht`: Pointer to the hash table to destroy.

**Example:**
```c
destroy_hash_table(ht);
```

### `int add_item(HashTable* ht, const char* key, const char* value)`

Inserts a new key*value pair or updates an existing key.

**Parameters:**
* `ht`: Pointer to the hash table.
* `key`: String key to insert or update.
* `value`: String value to associate with the key.

**Returns:**
* `0` if a new item was added
* `1` if an existing item was updated
* `-1` if memory allocation failed

**Example:**
```c
add_item(ht, "email", "andrea@example.com");  // Insert
add_item(ht, "email", "andrea.new@example.com");  // Update
```

### `char* get_item(HashTable* ht, const char* key)`

Retrieves the value associated with a key.

**Parameters:**
* `ht`: Pointer to the hash table.
* `key`: String key to search for.

**Returns:** Pointer to the value string if found, or `NULL` if the key doesn't exist.

**Warning:** Do not free or modify the returned string. It's owned by the hash table.

**Example:**
```c
char* value = get_item(ht, "name");
if (value != NULL) {
    printf("Name: %s\n", value);
} else {
    printf("Key not found\n");
}
```

### `int delete_item(HashTable* ht, const char* key)`

Removes a key*value pair from the hash table.

**Parameters:**
* `ht`: Pointer to the hash table.
* `key`: String key to delete.

**Returns:**
* `0` if the item was successfully deleted
* `-1` if the key was not found

**Example:**
```c
int result = delete_item(ht, "age");
if (result == 0) {
    printf("Successfully deleted\n");
} else {
    printf("Key not found\n");
}
```

## Implementation Details
### Hash Function
Uses the **djb2** algorithm by Daniel J. Bernstein:
```c
hash = 5381
for each character c in string:
    hash = ((hash << 5) + hash) + c
index = hash % table_size
```

### Collision Resolution
Implements **separate chaining**: each bucket contains a linked list of items that hash to the same index.

### Load Factor & Resizing
* **Load Factor** = `count / size`
* **Threshold**: 0.75
* When threshold is exceeded, the table automatically doubles in size and rehashes all items

### Time Complexity
| Operation | Average Case | Worst Case |
|-----------|--------------|------------|
| Insert    | O(1)         | O(n)*      |
| Search    | O(1)         | O(n)       |
| Delete    | O(1)         | O(n)       |

*: Amortized O(1) due to dynamic resizing.

### Space Complexity
O(n + m), where n is the number of items and m is the number of buckets.

## Memory Management
The hash table properly manages memory:
* Keys and values are **copied** internally (using `malloc` and `strcpy`)
* All memory is freed when calling `destroy_hash_table()`
* No memory leaks when used correctly

**Important:** Always call `destroy_hash_table()` when done to prevent memory leaks.

## Notes
* My main goal in making this project was to practice and solidify my C skills by exploring the implementation of something new and fun for me, specifically a Hash Table.
* While it isn't the most optimized implementation out there, I consider it functional enough and an honest representation of my learning process.
* This project was a valuable experience, I had my moments of frustration dealing with bugs, but I had a lot of fun and gained significant practical knowledge.
* Important Notice: This code was created exclusively for educational purposes and has not been subjected to deep, rigorous testing. Therefore, it is not intended for production environments.

## Useful Resources
* [Hash Table, Wikipedia](https://en.wikipedia.org/wiki/Hash_table)
* [Hash Table, Interview Cake](https://www.interviewcake.com/concept/java/hash-map)
* [djb2 Hash Function](http://www.cse.yorku.ca/~oz/hash.html)
