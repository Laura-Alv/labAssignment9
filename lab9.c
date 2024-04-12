#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order;
    struct RecordType* next; // Pointer to the next record in the chain (for chaining)
};

// HashType structure: an array of pointers to linked lists of RecordType
struct HashType {
    struct RecordType** buckets; // Array of pointers to linked lists
    int size; // Size of the hash table
};

// Compute the hash function
int hash(int x, int hashSize) {
    // Compute the hash using modulo operation
    return x % hashSize;
}

// Function to initialize the hash table
struct HashType* initializeHashTable(int size) {
    struct HashType* hashTable = (struct HashType*)malloc(sizeof(struct HashType));
    hashTable->size = size;
    hashTable->buckets = (struct RecordType**)malloc(sizeof(struct RecordType*) * size);

    // Initialize each bucket as NULL (empty linked list)
    for (int i = 0; i < size; i++) {
        hashTable->buckets[i] = NULL;
    }
    return hashTable;
}

// Function to insert a record into the hash table
void insertRecord(struct HashType* hashTable, struct RecordType* record) {
    int index = hash(record->id, hashTable->size);
    
    // Insert record at the head of the linked list at index
    record->next = hashTable->buckets[index];
    hashTable->buckets[index] = record;
}

// Function to display records in the hash table
void displayRecordsInHash(struct HashType* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        // Check if the bucket at index i is not empty
        if (hashTable->buckets[i] != NULL) {
            printf("Index %d -> ", i);
            
            // Traverse the linked list at this bucket
            struct RecordType* current = hashTable->buckets[i];
            while (current != NULL) {
                printf("id: %d, name: %c, order: %d -> ", current->id, current->name, current->order);
                current = current->next;
            }
            
            printf("NULL\n"); // Mark end of the linked list
        }
    }
}

// Cleanup function to release memory allocated for the hash table and its contents
void freeHashTable(struct HashType* hashTable) {
    // Free each linked list in the hash table
    for (int i = 0; i < hashTable->size; i++) {
        struct RecordType* current = hashTable->buckets[i];
        while (current != NULL) {
            struct RecordType* temp = current;
            current = current->next;
            free(temp);
        }
    }
    // Free the array of buckets and the hash table struct
    free(hashTable->buckets);
    free(hashTable);
}

// Main function
int main(void) {
    struct RecordType* pRecords;
    int recordSz = 0;

    // Parse data from the file
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table with size of your choice
    int hashSize = 10;
    struct HashType* hashTable = initializeHashTable(hashSize);

    // Insert records into the hash table
    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashTable, &pRecords[i]);
    }

    // Display the records in the hash table
    displayRecordsInHash(hashTable);

    // Clean up the hash table and the records
    freeHashTable(hashTable);
    free(pRecords);

    return 0;
}
