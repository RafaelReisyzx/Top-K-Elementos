#include <stdio.h>
#include "Topk.h"

int main() {
    HashTable hash_table;
    initializeHashTable(&hash_table);
    loadStopWords(&hash_table, "dataset/stopwords.txt");
    processFile(&hash_table, "dataset/arquivo1.txt");
    int k = 10; 
    Heap* heap = createHeap(k);
    for (int i = 0; i < TABLE_SIZE; i++) {
        Word* current = hash_table.table[i];
        while (current != NULL) {
            if (current->frequency > 0) {
                insertIntoHeap(heap, current);
                if (heap->size > k) {
                    extractMinFromHeap(heap);
                }
            }
            current = current->next;
        }
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Word* current = hash_table.table[i];
        while (current != NULL) {
            if (current->frequency > 0 && current->frequency > heap->array[0].word_node->frequency) {
                extractMinFromHeap(heap);
                insertIntoHeap(heap, current);
            }
            current = current->next;
        }
    }
    printf("Top %d palavras mais frequentes:\n", k);
    while (heap->size > 0) {
        Word* max_word = extractMinFromHeap(heap);
        printf("%s: %d\n", max_word->word, max_word->frequency);
    }

    freeHeap(heap);
    freeHashTable(&hash_table);

    return 0;
}
