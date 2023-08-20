#include <stdio.h>
#include "Topk.h"

int main() {
    HashTable hash_table;
    initializeHashTable(&hash_table);

    // Carregar as palavras proibidas do arquivo stopwords.txt
    loadStopWords(&hash_table, "dataset/stopwords.txt");

    // Processar o arquivo1.txt e atualizar a tabela hash
    processFile(&hash_table, "dataset/arquivo1.txt");

    // Criar e configurar a heap de tamanho k
    int k = 10; // O valor de k que você deseja
    Heap* heap = createHeap(k);

    // Preencher a heap com os primeiros k elementos da tabela hash
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

    // Continuar a análise da tabela hash e atualizar a heap conforme necessário
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

    // Imprimir os k elementos com maiores valores (frequências) em ordem crescente (heapsort)
    printf("Top %d palavras mais frequentes:\n", k);
    while (heap->size > 0) {
        Word* max_word = extractMinFromHeap(heap);
        printf("%s: %d\n", max_word->word, max_word->frequency);
    }

    // Liberar memória da heap e da tabela hash
    freeHeap(heap);
    freeHashTable(&hash_table);

    return 0;
}
