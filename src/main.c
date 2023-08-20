#include <stdio.h>
#include "Topk.h"

int main() {
    HashTable hash_table;
    initializeHashTable(&hash_table);

    // Carregar as palavras proibidas do arquivo stopwords.txt
    loadStopWords(&hash_table, "dataset/stopwords.txt");

    // Processar o arquivo1.txt e atualizar a tabela hash
    processFile(&hash_table, "dataset/arquivo1.txt");

    // Imprimir as palavras e suas frequências da tabela hash
    printHashTable(&hash_table);

    // Liberar memória da tabela hash
    freeHashTable(&hash_table);

    return 0;
}