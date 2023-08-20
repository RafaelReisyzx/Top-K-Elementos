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

void initializeHashTable(HashTable* hash_table);
void loadStopWords(HashTable* hash_table, const char* stop_words_file);
void processFile(HashTable* hash_table, const char* input_file);
void printHashTable(const HashTable* hash_table);
void freeHashTable(HashTable* hash_table);

#endif