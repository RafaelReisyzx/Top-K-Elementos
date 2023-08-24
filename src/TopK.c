#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Topk.h"

unsigned long hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}

Word* createWordNode(const char* word) {
    Word* new_word = (Word*)malloc(sizeof(Word));
    if (new_word != NULL) {
        strcpy(new_word->word, word);
        new_word->frequency = 1;
        new_word->next = NULL;
    }
    return new_word;
}

void initializeHashTable(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
    }
}

void loadStopWords(HashTable* hash_table, const char* stop_words_file) {
    FILE* file = fopen(stop_words_file, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de stopwords.\n");
        exit(1);
    }

    char word[MAX_WORD_LENGTH];
    while (fgets(word, MAX_WORD_LENGTH, file)) {
        word[strcspn(word, "\r\n")] = '\0'; 
        unsigned long hash = hashFunction(word);
        Word* new_word = createWordNode(word);
        new_word->frequency = -1; 
        new_word->next = hash_table->table[hash];
        hash_table->table[hash] = new_word;
    }

    fclose(file);
}

void processFile(HashTable* hash_table, const char* input_file) {
    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        exit(1);
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        word[strcspn(word, ".,!?")] = '\0'; 
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]); 
        }

        if (strlen(word) > 0) {
            unsigned long hash = hashFunction(word);
            Word* current = hash_table->table[hash];
            Word* prev = NULL;

            while (current != NULL) {
                if (strcmp(current->word, word) == 0) {
                    if (current->frequency > 0) {
                        current->frequency++;
                    }
                    break;
                }
                prev = current;
                current = current->next;
            }

            if (current == NULL) {
                Word* new_word = createWordNode(word);
                if (new_word != NULL) {
                    if (prev == NULL) {
                        hash_table->table[hash] = new_word;
                    } else {
                        prev->next = new_word;
                    }
                }
            }
        }
    }

    fclose(file);
}

void printHashTable(const HashTable* hash_table) {
    printf("Palavras adicionadas na tabela:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Word* current = hash_table->table[i];
        while (current != NULL) {
            if (current->frequency > 0) {
                printf("%s: %d\n", current->word, current->frequency);
            }
            current = current->next;
        }
    }
}

void freeHashTable(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Word* current = hash_table->table[i];
        while (current != NULL) {
            Word* temp = current;
            current = current->next;
            free(temp);
        }
    }
}
Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (heap != NULL) {
        heap->capacity = capacity;
        heap->size = 0;
        heap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    }
    return heap;
}

void insertIntoHeap(Heap* heap, Word* word_node) {
    if (heap->size < heap->capacity) {
        HeapNode newNode;
        newNode.word_node = word_node;
        heap->array[heap->size] = newNode;
        int index = heap->size;
        heap->size++;
        while (index != 0 && heap->array[(index - 1) / 2].word_node->frequency > word_node->frequency) {
            heap->array[index] = heap->array[(index - 1) / 2];
            index = (index - 1) / 2;
        }
        heap->array[index].word_node = word_node;
    }
}

void heapify(Heap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->array[left].word_node->frequency < heap->array[smallest].word_node->frequency) {
        smallest = left;
    }

    if (right < heap->size && heap->array[right].word_node->frequency < heap->array[smallest].word_node->frequency) {
        smallest = right;
    }

    if (smallest != index) {
        HeapNode temp = heap->array[index];
        heap->array[index] = heap->array[smallest];
        heap->array[smallest] = temp;
        heapify(heap, smallest);
    }
}

Word* extractMinFromHeap(Heap* heap) {
    if (heap->size == 0) {
        return NULL;
    }

    Word* min_word = heap->array[0].word_node;
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return min_word;
}

void freeHeap(Heap* heap) {
    free(heap->array);
    free(heap);
}
