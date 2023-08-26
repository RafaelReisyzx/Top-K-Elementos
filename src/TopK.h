#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#ifndef TOPK_H
#define TOPK_H
#define TABLE_SIZE 300000
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

void initializeHashTable(HashTable* hash_table);
void loadStopWords(HashTable* hash_table, const char* stop_words_file);
unsigned long hashFunction(const char* str);
Word* createWordNode(const char* word);
void processFile(HashTable* hash_table, const char* input_file);
Heap* createHeap(int capacity);
Word* extractMinFromHeap(Heap* heap);
void insertIntoHeap(Heap* heap, Word* word_node);


#endif
