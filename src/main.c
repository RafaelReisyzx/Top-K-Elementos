#include <stdio.h>
#include "Topk.h"

int main() {
  HashTable hash_table;
  int k = 20;  
   initializeHashTable(&hash_table);
   loadStopWords(&hash_table, "dataset/stopwords.txt");
  // processFile(&hash_table, "dataset/Semana_Machado_Assis.txt");
   processFile(&hash_table, "dataset/DomCasmurro.txt");
   Heap* heap = createHeap(k);
   for (int i = 0; i < TABLE_SIZE; i++) {
        Word* palavra_atual = hash_table.table[i];
        while (palavra_atual != NULL) {
            if (palavra_atual->frequency > 0) {
                insertIntoHeap(heap, palavra_atual);
                if (heap->size > k) {
                    extractMinFromHeap(heap);
                }
            }
            palavra_atual = palavra_atual->next;
        }
    }

     for (int i = 0; i < TABLE_SIZE; i++) {
        Word* palavra_atual = hash_table.table[i];
        while (palavra_atual != NULL) {
            if (palavra_atual->frequency > 0 && palavra_atual->frequency > heap->array[0].word_node->frequency) {
                extractMinFromHeap(heap);
                insertIntoHeap(heap, palavra_atual);
            }
            palavra_atual = palavra_atual->next;
        }
    }
    printf("Top %d palavras mais frequentes:\n", k);
   printf("Palavras Frequência\n", k);
    while (heap->size > 0) {
        Word* max_word = extractMinFromHeap(heap);
        printf("%s %d\n", max_word->word, max_word->frequency);
    }


    return 0;


}
