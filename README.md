
# Descrição do algoritmo
 A análise de texto é uma tarefa fundamental em muitos campos, como processamento de linguagem natural, mineração de dados e aprendizado de máquina. Um dos desafios frequentes é identificar as palavras mais relevantes e significativas em um documento, o que pode ser vital para extrair insights e compreender seu conteúdo. O algoritmo projetado aborda esse desafio de forma eficiente, permitindo a identificação das K palavras mais frequentes em um texto de maneira rápida e escalável.
O problema central que o algoritmo aborda é como extrair informações úteis de grandes volumes de texto, destacando as palavras que mais contribuem para o significado do documento. O algoritmo resolve esse problema utilizando uma tabela de hash para armazenar as palavras e suas frequências e um heap min garantindo que as K palavras mais frequentes sejam mantidas em ordem, permitindo a fácil identificação das palavras de maior relevância. Ao combinar essas estruturas de dados, o algoritmo aproveita a velocidade da tabela de hash e a funcionalidade de classificação do heap, resultando em um método eficiente para encontrar as palavras mais frequentes.

# Regras Propostas
Um exemplo clássico de problema que pode ser solucionado utilizando-se hash e heap é o
chamado top k itens. Neste problema, é preciso encontrar os k itens mais valiosos de uma
coleção de dados. Logo, utiliza-se o hash para contar a frequência de todos os itens, enquanto
o heap se aplica na manutenção de uma lista dos k itens de maior valor. Sabendo-se disso,
elabore uma solução em C/C++ que dado uma entrada:
• Crie uma tabela de dispersão (hash) para contar a frequência de cada elemento tokenizado
da coleção de dados de entrada.
• Crie uma árvore de prioridades (heap) de tamanho k e insira os primeiros k elementos do
hash nela.
1. Para cada elemento restante na hash, compare a contagem com o menor valor do
heap.
2. Se a contagem for maior do que o menor valor da heap, remova o menor valor, insira
o novo elemento e refaça a estrutura.
3. Caso contrário, ignore o elemento e vá para o próximo.
• No final, a heap conterá os k elementos com maiores valores (frequências) da coleção
de dados. Então, imprima-os em ordem crescente.
Esse algoritmo é uma combinação eficiente do uso de hash para contar a frequência dos
elementos e heap para manter a lista dos k elementos com maiores valores. Sua complexidade,
caso implementado adequadamente, é de O(nlogk), onde n é o tamanho da coleção de dados
e k o número de itens mais relevantes.

# Funções 

1. initializeHashTable(HashTable* hash_table)
Essa função é responsável por inicializar a tabela de hash. Ela percorre a matriz table dentro da estrutura hash_table e define todos os ponteiros de cada posição da tabela como NULL. Isso prepara a tabela de hash para armazenar as palavras e suas frequências.
```
void initializeHashTable(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
    }
}
```

2. loadStopWords(HashTable* hash_table, const char* stop_words_file)
A função loadStopWords lida com as palavras que geralmente não carregam significado relevante em análises de texto, chamadas de "stop words". Ela lê um arquivo de stop words e, para cada palavra no arquivo, calcula seu valor de hash e cria um novo nó de palavra associado a essa palavra. A frequência do nó de palavra é definida como -1 para diferenciar as stop words das palavras regulares. O novo nó de palavra é adicionado ao início da lista ligada na posição de hash correspondente na tabela de hash.

```
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

unsigned long hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}
```

3. hashFunction(const char* str)
Essa função calcula um valor de hash para uma dada string str. Ela percorre os caracteres da string, multiplicando o valor atual do hash por um número primo (5381) e somando o valor ASCII do caractere atual. O valor final é reduzido usando a operação de módulo para que ele caiba dentro do intervalo da tabela de hash.
Exemplo de Funcionamento da Função hashFunction com a Palavra "aba":

- Inicialização: hash = 5381 (número arbitrário que foi escolhido como semente inicial.).

- Percorrendo os caracteres:
Primeiro caractere 'a':
Valor ASCII de 'a': 97
Cálculo: hash = (hash * 33) + 97 = 177670
Segundo caractere 'b':
Valor ASCII de 'b': 98
Cálculo: hash = (177670 * 33) + 98 = 5863208
Caractere 'a' novamente:
Valor ASCII de 'a': 97
Cálculo: hash = (5841642 * 33) + 97 = 193485961
- Redução de Hash:
Aplicamos a operação de módulo para limitar o valor dentro do intervalo da tabela de hash (suponhamos TABLE_SIZE = 300000):
hash = 193485961 % 300000 = 6449
O valor de hash final para a palavra "aba" é 6449. Esse valor será usado para indexar na tabela de hash e determinar onde armazenar a palavra. Note que diferentes palavras terão diferentes valores de hash, mas a mesma palavra sempre terá o mesmo valor de hash, o que é fundamental para o funcionamento adequado da estrutura de dados.

```
unsigned long hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}
```

4. createWordNode(const char* word)
Essa função cria um novo nó de palavra, associando a ele a palavra fornecida e definindo sua frequência inicial como 1. O nó de palavra é a estrutura que armazena a palavra e sua frequência na tabela de hash.

```
Word* createWordNode(const char* word) {
    Word* new_word = (Word*)malloc(sizeof(Word));
    if (new_word != NULL) {
        strcpy(new_word->word, word);
        new_word->frequency = 1;
        new_word->next = NULL;
    }
    return new_word;
}
```
5. processFile(HashTable* hash_table, const char* input_file)
A função processFile é responsável por ler um arquivo de entrada, tokenizar o conteúdo em palavras, converter essas palavras para letras minúsculas e atualizar suas frequências na tabela de hash. Para cada palavra no arquivo, ela calcula seu valor de hash, busca ou cria um nó de palavra correspondente na tabela de hash e atualiza sua frequência.

```
void processFile(HashTable* hash_table, const char* input_file) {
    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        exit(1);
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        word[strcspn(word, ".,!?;-—/\()")] = '\0'; 
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]); 
        }

        if (strlen(word) > 0) {
            unsigned long hash = hashFunction(word);
            Word* palavra_atual = hash_table->table[hash];
            Word* palavra_anterior = NULL;

            while (palavra_atual != NULL) {
                if (strcmp(palavra_atual->word, word) == 0) {
                    if (palavra_atual->frequency > 0) {
                        palavra_atual->frequency++;
                    }
                    break;
                }
                palavra_anterior = palavra_atual;
                palavra_atual = palavra_atual->next;
            }

            if (palavra_atual == NULL) {
                Word* new_word = createWordNode(word);
                if (new_word != NULL) {
                    if (palavra_anterior == NULL) {
                        hash_table->table[hash] = new_word;
                    } else {
                        palavra_anterior->next = new_word;
                    }
                }
            }
        }
    }

    fclose(file);
}
```
6. createHeap(int capacity)
Essa função cria e inicializa um heap min, que é usado para manter as palavras com as K maiores frequências. O heap é representado como uma estrutura Heap contendo um array de HeapNode e mantém as propriedades de um heap min.

```
Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (heap != NULL) {
        heap->capacity = capacity;
        heap->size = 0;
        heap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    }
    return heap;
}
```
7. heapify(Heap* heap, int index)
A função heapify é um procedimento de manutenção do heap. Dado um índice index no heap, ela verifica se o elemento nesse índice obedece à propriedade de heap min. Se não obedecer, ela ajusta o heap trocando elementos para que a propriedade seja restaurada.

```
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

```
8. extractMinFromHeap(Heap* heap)
Essa função remove e retorna o nó de palavra com a menor frequência do heap. Para fazer isso, ela troca o nó raiz (com a menor frequência) com o último nó no heap, diminui o tamanho do heap e, em seguida, chama heapify para manter a propriedade de heap min.

```
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
```
9. insertIntoHeap(Heap* heap, Word* word_node)
A função insertIntoHeap insere um nó de palavra no heap. Ela verifica se há espaço no heap para a inserção, adiciona o nó de palavra ao final do heap e, em seguida, ajusta a posição do nó inserido para manter a propriedade de heap min.

```
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

```

# Funcionamento
A seguir, serão examinadas em detalhes as etapas que compõem o funcionamento do algoritmo, as quais se baseiam nas funções mencionadas previamente:
Inicialização da Tabela de Hash:
O processo tem início com a inicialização da tabela de hash, que serve como a estrutura central para armazenar as palavras e suas frequências. A função "initializeHashTable" percorre cada posição da matriz "table" dentro da estrutura "hash_table" e define os ponteiros como NULL. Esse procedimento cria espaços vazios que serão utilizados para armazenar as palavras e seus respectivos dados.

Carregamento de Stop Words:
Em muitas análises de texto, palavras comuns como "o", "a", "e", são irrelevantes. A função "loadStopWords" lida com essa situação carregando uma lista de palavras irrelevantes de um arquivo. Para cada stop word no arquivo, a função calcula seu valor de hash usando a função "hashFunction". Em seguida, ela cria um novo nó de palavra associado à stop word, definindo sua frequência como -1 para diferenciá-la das palavras regulares. O novo nó de palavra é adicionado ao início da lista ligada na posição de hash correspondente na tabela de hash.

Processamento do Arquivo de Entrada:
O algoritmo agora está pronto para processar o arquivo de entrada propriamente dito. A função "processFile" lê o arquivo palavra por palavra. Para cada palavra, ela a limpa de pontuações e a converte para letras minúsculas. A função então calcula o valor de hash da palavra usando a "hashFunction" e busca ou cria um nó de palavra correspondente na tabela de hash. Se a palavra já estiver na tabela, sua frequência é atualizada; caso contrário, um novo nó de palavra é criado e adicionado à lista ligada.

Criação e Utilização do Heap:
A estrutura de dados-chave que possibilita encontrar as K palavras mais frequentes é o heap mínimo. Ele é criado pela função "createHeap", que inicializa uma estrutura de Heap contendo um array de "HeapNode". Esse heap mantém as palavras com as menores frequências no topo. Isso é crucial para identificar rapidamente as palavras menos frequentes entre as mais frequentes.

Identificação das Palavras Mais Frequentes:
Após processar o arquivo e preencher a tabela de hash com palavras e suas frequências, o algoritmo entra na fase de identificar as K palavras mais frequentes. Isso é feito de forma eficiente usando o heap mínimo. A cada iteração, as palavras da tabela de hash são comparadas com a palavra de menor frequência atualmente no heap. Se uma palavra da tabela tiver uma frequência maior que a menor frequência do heap, ela substitui essa palavra no heap.

Extração das Palavras Principais:
Com o heap atualizado para conter as K palavras mais frequentes, é possível extrair essas palavras uma a uma por meio da função "extractMinFromHeap". Essa função remove a palavra com a menor frequência (no topo do heap), reorganiza o heap e retorna a palavra extraída.

Apresentação dos Resultados:
Por fim, as palavras principais extraídas são apresentadas na saída padrão. A frequência e a palavra são impressas, revelando quais palavras são as mais frequentes no documento de entrada.

# Conclusão:
Em última análise, o algoritmo oferece uma solução robusta para um problema central na análise de texto. Sua combinação inteligente de estruturas de dados e algoritmos permite a rápida identificação das palavras mais ocorrentes.
No entanto, é importante reconhecer algumas limitações do algoritmo. Ele pode não ser ideal para tratar palavras com caracteres especiais e além disso, a definição de K (o número de palavras principais a serem identificadas) deve ser feita com cuidado, uma vez que valores muito altos podem afetar o desempenho.

# Compilação e Execução

A estrutura disponibilizada possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

Em resumo, para executar o programa, você precisa navegar até o diretório raiz do projeto e executar o comando make para compilar o programa e, em seguida, 
executar o comando make run para executá-lo.Se você precisar limpar a compilação anterior, pode usar o comando make clean antes de executar a compilação.
