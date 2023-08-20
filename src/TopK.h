#ifndef TOPK_H
#define TOPK_H

#define TABLE_SIZE 1000
#define MAX_WORD_LENGTH 50

typedef struct Word {
    char word[MAX_WORD_LENGTH];
    int frequency;
    struct Word* next;
} Word;

typedef struct HashTable {
    Word* table[TABLE_SIZE];
} HashTable;
typedef struct HeapNode {
    Word* word_node;
} HeapNode;

typedef struct Heap {
    HeapNode* array;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity);
void insertIntoHeap(Heap* heap, Word* word_node);
void heapify(Heap* heap, int index);
Word* extractMinFromHeap(Heap* heap);
void freeHeap(Heap* heap);
void initializeHashTable(HashTable* hash_table);
void loadStopWords(HashTable* hash_table, const char* stop_words_file);
void processFile(HashTable* hash_table, const char* input_file);
void freeHashTable(HashTable* hash_table);

#endif
