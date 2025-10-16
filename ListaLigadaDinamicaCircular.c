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
    PONT cabeca;
} LISTA_DINAMICA_CIRCULAR;

// Protótipos das funções
void inicializarLista(LISTA_DINAMICA_CIRCULAR* lista);
int tamanhoLista(const LISTA_DINAMICA_CIRCULAR* lista);
void exibirLista(const LISTA_DINAMICA_CIRCULAR* lista);
PONT buscaSentinela(const LISTA_DINAMICA_CIRCULAR* lista, TIPOCHAVE chave);
PONT buscaSentinelaOrdenada(const LISTA_DINAMICA_CIRCULAR* lista, TIPOCHAVE chave);
PONT buscaSequencialComAnterior(const LISTA_DINAMICA_CIRCULAR* lista, TIPOCHAVE chave, PONT* anterior);
bool inserirElementoOrdenado(LISTA_DINAMICA_CIRCULAR* lista, REGISTRO registro);
bool excluirElemento(LISTA_DINAMICA_CIRCULAR* lista, TIPOCHAVE chave);
void reinicializarLista(LISTA_DINAMICA_CIRCULAR* lista);
void destruirLista(LISTA_DINAMICA_CIRCULAR* lista);

// Implementações
void inicializarLista(LISTA_DINAMICA_CIRCULAR* lista) {
    lista->cabeca = (PONT)malloc(sizeof(ELEMENTO));
    if (lista->cabeca == NULL) {
        printf("Erro: Falha na alocação do nó cabeça!\n");
        exit(1);
    }
    lista->cabeca->proximo = lista->cabeca;  // Lista circular
}

int tamanhoLista(const LISTA_DINAMICA_CIRCULAR* lista) {
    int contador = 0;
    PONT atual = lista->cabeca->proximo;
    
    while (atual != lista->cabeca) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

void exibirLista(const LISTA_DINAMICA_CIRCULAR* lista) {
    PONT atual = lista->cabeca->proximo;
    
    if (atual == lista->cabeca) {
        printf("Lista: \" \" (vazia)\n");
        return;
    }
    
    printf("Lista: \" ");
    while (atual != lista->cabeca) {
        printf("%d ", atual->registro.chave);
        atual = atual->proximo;
    }
    printf("\"\n");
}

PONT buscaSentinela(const LISTA_DINAMICA_CIRCULAR* lista, TIPOCHAVE chave) {
    PONT atual = lista->cabeca->proximo;
    lista->cabeca->registro.chave = chave;  // Configura sentinela
    
    while (atual->registro.chave != chave) {
        atual = atual->proximo;
    }
    
    if (atual != lista->cabeca) {
        return atual;
    }
    return NULL;
}

PONT buscaSentinelaOrdenada(const LISTA_DINAMICA_CIRCULAR* lista, TIPOCHAVE chave) {
    PONT atual = lista->cabeca->proximo;
    lista->cabeca->registro.chave = chave;  // Configura sentinela
    
    while (atual->registro.chave < chave) {
        atual = atual->proximo;
    }
    
    if (atual != lista->cabeca && atual->registro.chave == chave) {
        return atual;
    }
    return NULL;
}

PONT buscaSequencialComAnterior(const LISTA_DINAMICA_CIRCULAR* lista, TIPOCHAVE chave, PONT* anterior) {
    *anterior = lista->cabeca;
    PONT atual = lista->cabeca->proximo;
    lista->cabeca->registro.chave = chave;  // Configura sentinela
    
    while (atual->registro.chave < chave) {
        *anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual != lista->cabeca && atual->registro.chave == chave) {
        return atual;
    }
    
    return NULL;
}

bool inserirElementoOrdenado(LISTA_DINAMICA_CIRCULAR* lista, REGISTRO registro) {
    PONT anterior, atual;
    TIPOCHAVE chave = registro.chave;

    // Busca a posição correta para inserção
    atual = buscaSequencialComAnterior(lista, chave, &anterior);

    // Elemento já existe
    if (atual != NULL) {
        return false;
    }
    
    // Cria novo elemento
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    if (novo == NULL) {
        return false;  // Falha na alocação
    }
    
    novo->registro = registro;
    novo->proximo = anterior->proximo;
    anterior->proximo = novo;
    
    return true;
}

bool excluirElemento(LISTA_DINAMICA_CIRCULAR* lista, TIPOCHAVE chave) {
    PONT anterior;
    PONT atual = buscaSequencialComAnterior(lista, chave, &anterior);

    if (atual == NULL) {
        return false;  // Elemento não encontrado
    }
        
    // Remove o elemento
    anterior->proximo = atual->proximo;
    free(atual);
    return true;
}

void reinicializarLista(LISTA_DINAMICA_CIRCULAR* lista) {
    PONT atual = lista->cabeca->proximo;
    
    while (atual != lista->cabeca) {
        PONT proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    lista->cabeca->proximo = lista->cabeca;
}

void destruirLista(LISTA_DINAMICA_CIRCULAR* lista) {
    reinicializarLista(lista);
    free(lista->cabeca);
    lista->cabeca = NULL;
}

// Função main para teste completo
int main() {
    LISTA_DINAMICA_CIRCULAR lista;
    REGISTRO reg;
    
    printf("=== TESTE DA LISTA CIRCULAR COM SENTINELA ===\n\n");
    
    // Inicialização
    printf("1. Inicializando lista...\n");
    inicializarLista(&lista);
    exibirLista(&lista);
    printf("Tamanho: %d\n\n", tamanhoLista(&lista));
    
    // Teste 2: Inserção ordenada
    printf("2. Inserindo elementos ordenadamente...\n");
    int elementos[] = {30, 10, 50, 20, 40, 5, 60};
    for (int i = 0; i < 7; i++) {
        reg.chave = elementos[i];
        if (inserirElementoOrdenado(&lista, reg)) {
            printf("   Inserido: %d\n", elementos[i]);
        } else {
            printf("   Falha ao inserir (duplicata?): %d\n", elementos[i]);
        }
    }
    exibirLista(&lista);
    printf("Tamanho: %d\n\n", tamanhoLista(&lista));
    
    // Teste 3: Busca com sentinela
    printf("3. Buscando elementos com sentinela...\n");
    int busca[] = {20, 25, 5, 60, 100};
    for (int i = 0; i < 5; i++) {
        PONT resultado = buscaSentinelaOrdenada(&lista, busca[i]);
        if (resultado != NULL) {
            printf("   Elemento %d encontrado!\n", busca[i]);
        } else {
            printf("   Elemento %d não encontrado!\n", busca[i]);
        }
    }
    printf("\n");
    
    // Teste 4: Tentativa de inserir duplicata
    printf("4. Tentando inserir elemento duplicado...\n");
    reg.chave = 30;
    if (!inserirElementoOrdenado(&lista, reg)) {
        printf("   Elemento 30 já existe - não foi inserido novamente\n\n");
    }
    
    // Teste 5: Exclusão de elementos
    printf("5. Excluindo elementos...\n");
    int excluir[] = {5, 30, 100, 20};
    for (int i = 0; i < 4; i++) {
        if (excluirElemento(&lista, excluir[i])) {
            printf("   Elemento %d excluído com sucesso\n", excluir[i]);
        } else {
            printf("   Elemento %d não encontrado para exclusão\n", excluir[i]);
        }
    }
    exibirLista(&lista);
    printf("Tamanho: %d\n\n", tamanhoLista(&lista));
    
    // Teste 6: Teste de circularidade
    printf("6. Verificando circularidade...\n");
    printf("   Percorrendo a lista 2 vezes:\n   ");
    PONT atual = lista.cabeca->proximo;
    int count = 0;
    while (count < 2 * tamanhoLista(&lista)) {
        printf("%d ", atual->registro.chave);
        atual = atual->proximo;
        count++;
        if (atual == lista.cabeca) {
            printf("[SENTINELA] ");
        }
    }
    printf("\n\n");
    
    // Teste 7: Reinicialização
    printf("7. Reinicializando lista...\n");
    reinicializarLista(&lista);
    exibirLista(&lista);
    printf("Tamanho: %d\n\n", tamanhoLista(&lista));
    
    // Teste 8: Destruição
    printf("8. Destruindo lista...\n");
    destruirLista(&lista);
    printf("Lista destruída com sucesso!\n");
    
    return 0;
}