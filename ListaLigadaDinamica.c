#include <stdio.h>
#include <stdlib.h>

#define MAX 50
#define INVALIDO -1
#define false 0
#define true 1

typedef int TIPOCHAVE;
typedef int bool;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux {
    REGISTRO registro;
    struct aux *proximo;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct {
    PONT inicio;
} LISTA_DINAMICA;

// Protótipos das funções
void inicializarLista(LISTA_DINAMICA* lista);
int tamanhoLista(const LISTA_DINAMICA* lista);
void exibirLista(const LISTA_DINAMICA* lista);
PONT buscaSequencial(const LISTA_DINAMICA* lista, TIPOCHAVE chave);
PONT buscaSequencialOrdenada(const LISTA_DINAMICA* lista, TIPOCHAVE chave);
PONT buscaSequencialComAnterior(const LISTA_DINAMICA* lista, TIPOCHAVE chave, PONT* anterior);
bool inserirElementoOrdenado(LISTA_DINAMICA* lista, REGISTRO registro);
bool excluirElemento(LISTA_DINAMICA* lista, TIPOCHAVE chave);
void reinicializarLista(LISTA_DINAMICA* lista);

// Implementações
void inicializarLista(LISTA_DINAMICA* lista) {
    lista->inicio = NULL;
}

int tamanhoLista(const LISTA_DINAMICA* lista) {
    int contador = 0;
    PONT atual = lista->inicio;
    
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

void exibirLista(const LISTA_DINAMICA* lista) {
    PONT atual = lista->inicio;
    printf("Lista: \" ");
    
    while (atual != NULL) {
        printf("%d ", atual->registro.chave);
        atual = atual->proximo;
    }
    printf("\"\n");
}

PONT buscaSequencial(const LISTA_DINAMICA* lista, TIPOCHAVE chave) {
    PONT atual = lista->inicio;
    
    while (atual != NULL) {
        if (atual->registro.chave == chave)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

PONT buscaSequencialOrdenada(const LISTA_DINAMICA* lista, TIPOCHAVE chave) {
    PONT atual = lista->inicio;
    
    while (atual != NULL && atual->registro.chave < chave) {
        atual = atual->proximo;
    }
    
    if (atual != NULL && atual->registro.chave == chave) {
        return atual;
    }
    
    return NULL;
}

PONT buscaSequencialComAnterior(const LISTA_DINAMICA* lista, TIPOCHAVE chave, PONT* anterior) {
    *anterior = NULL;
    PONT atual = lista->inicio;
    
    while (atual != NULL && atual->registro.chave < chave) {
        *anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual != NULL && atual->registro.chave == chave) {
        return atual;
    }
    
    return NULL;
}

bool inserirElementoOrdenado(LISTA_DINAMICA* lista, REGISTRO registro) {
    PONT anterior, atual;
    TIPOCHAVE chave = registro.chave;

    // Busca a posição correta para inserção
    atual = buscaSequencialComAnterior(lista, chave, &anterior);

    // Elemento já existe
    if (atual != NULL)
        return false;
    
    // Cria novo elemento
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    if (novo == NULL) return false; // Falha na alocação
    
    novo->registro = registro;
    
    // Insere no início (lista vazia ou chave menor que primeiro elemento)
    if (anterior == NULL) {
        novo->proximo = lista->inicio;
        lista->inicio = novo;
    } else {
        // Insere no meio ou final
        novo->proximo = anterior->proximo;
        anterior->proximo = novo;
    }
    
    return true;
}

bool excluirElemento(LISTA_DINAMICA* lista, TIPOCHAVE chave) {
    PONT anterior;
    PONT atual = buscaSequencialComAnterior(lista, chave, &anterior);

    if (atual == NULL)
        return false; // Elemento não encontrado
        
    // Remove o elemento
    if (anterior == NULL)
        lista->inicio = atual->proximo; // Remove do início
    else
        anterior->proximo = atual->proximo; // Remove do meio/final

    free(atual);
    return true;
}

void reinicializarLista(LISTA_DINAMICA* lista) {
    PONT atual = lista->inicio;
    
    while (atual != NULL) {
        PONT proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    lista->inicio = NULL;
}

// Função main para teste completo
int main() {
    LISTA_DINAMICA lista;
    REGISTRO reg;
    int opcao, chave;
    
    inicializarLista(&lista);
    
    printf("=== TESTE DA LISTA DINÂMICA ORDENADA ===\n\n");
    
    // Teste 1: Inserção de elementos
    printf("1. Inserindo elementos...\n");
    int elementos[] = {30, 10, 50, 20, 40};
    for (int i = 0; i < 5; i++) {
        reg.chave = elementos[i];
        if (inserirElementoOrdenado(&lista, reg)) {
            printf("   Inserido: %d\n", elementos[i]);
        } else {
            printf("   Falha ao inserir: %d\n", elementos[i]);
        }
    }
    exibirLista(&lista);
    printf("Tamanho da lista: %d\n\n", tamanhoLista(&lista));
    
    // Teste 2: Busca de elementos
    printf("2. Buscando elementos...\n");
    int busca[] = {20, 60, 10, 25};
    for (int i = 0; i < 4; i++) {
        PONT resultado = buscaSequencialOrdenada(&lista, busca[i]);
        if (resultado != NULL) {
            printf("   Elemento %d encontrado!\n", busca[i]);
        } else {
            printf("   Elemento %d não encontrado!\n", busca[i]);
        }
    }
    printf("\n");
    
    // Teste 3: Tentativa de inserir duplicata
    printf("3. Tentando inserir elemento duplicado...\n");
    reg.chave = 30;
    if (!inserirElementoOrdenado(&lista, reg)) {
        printf("   Elemento 30 já existe - não foi inserido novamente\n\n");
    }
    
    // Teste 4: Exclusão de elementos
    printf("4. Excluindo elementos...\n");
    int excluir[] = {10, 40, 60};
    for (int i = 0; i < 3; i++) {
        if (excluirElemento(&lista, excluir[i])) {
            printf("   Elemento %d excluído com sucesso\n", excluir[i]);
        } else {
            printf("   Elemento %d não encontrado para exclusão\n", excluir[i]);
        }
    }
    exibirLista(&lista);
    printf("Tamanho da lista: %d\n\n", tamanhoLista(&lista));
    
    // Teste 5: Reinicialização da lista
    printf("5. Reinicializando lista...\n");
    reinicializarLista(&lista);
    exibirLista(&lista);
    printf("Tamanho da lista: %d\n", tamanhoLista(&lista));
    
    return 0;
}