#include <stdio.h>

#define MAX 50
#define INVALIDO -1
#define false 0
#define true 1

typedef int TIPOCHAVE;
typedef int bool;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct {
    REGISTRO registro;
    int proximo;
} ELEMENTO;

typedef struct {
    ELEMENTO data[MAX];
    int inicioLista;
    int posicaoDisponivel;
} LISTA_ESTATICA;

// Protótipos das funções
void inicializarLista(LISTA_ESTATICA* lista);
int tamanhoLista(const LISTA_ESTATICA* lista);
void exibirLista(const LISTA_ESTATICA* lista);
int buscaSequencialOrdenada(const LISTA_ESTATICA* lista, TIPOCHAVE chave);
int obterNo(LISTA_ESTATICA* lista);
void devolverNo(LISTA_ESTATICA* lista, int posicao);
bool inserirElementoOrdenado(LISTA_ESTATICA* lista, REGISTRO registro);
bool excluirElemento(LISTA_ESTATICA* lista, TIPOCHAVE chave);
void reinicializarLista(LISTA_ESTATICA* lista);

void inicializarLista(LISTA_ESTATICA* lista) {
    for (int i = 0; i < MAX - 1; i++) {
        lista->data[i].proximo = i + 1;
    }
    lista->data[MAX - 1].proximo = INVALIDO;
    lista->inicioLista = INVALIDO;
    lista->posicaoDisponivel = 0;
}

int tamanhoLista(const LISTA_ESTATICA* lista) {
    int contador = 0;
    int posicaoAtual = lista->inicioLista;
    
    while (posicaoAtual != INVALIDO) {
        contador++;
        posicaoAtual = lista->data[posicaoAtual].proximo;
    }
    return contador;
}

void exibirLista(const LISTA_ESTATICA* lista) {
    int posicaoAtual = lista->inicioLista;
    printf("Lista: \" ");
    
    while (posicaoAtual != INVALIDO) {
        printf("%d ", lista->data[posicaoAtual].registro.chave);
        posicaoAtual = lista->data[posicaoAtual].proximo;
    }
    printf("\"\n");
}

int buscaSequencialOrdenada(const LISTA_ESTATICA* lista, TIPOCHAVE chave) {
    int posicaoAtual = lista->inicioLista;
    
    while (posicaoAtual != INVALIDO && lista->data[posicaoAtual].registro.chave < chave) {
        posicaoAtual = lista->data[posicaoAtual].proximo;
    }
    
    if (posicaoAtual != INVALIDO && lista->data[posicaoAtual].registro.chave == chave) {
        return posicaoAtual;
    }
    
    return INVALIDO;
}

int obterNo(LISTA_ESTATICA* lista) {
    int posicao = lista->posicaoDisponivel;
    
    if (posicao != INVALIDO) {
        lista->posicaoDisponivel = lista->data[posicao].proximo;
    }
    
    return posicao;
}

void devolverNo(LISTA_ESTATICA* lista, int posicao) {
    lista->data[posicao].proximo = lista->posicaoDisponivel;
    lista->posicaoDisponivel = posicao;
}

bool inserirElementoOrdenado(LISTA_ESTATICA* lista, REGISTRO registro) {
    if (lista->posicaoDisponivel == INVALIDO) {
        return false;
    }

    int anterior = INVALIDO;
    int atual = lista->inicioLista;
    TIPOCHAVE chave = registro.chave;

    // Encontrar posição de inserção
    while (atual != INVALIDO && lista->data[atual].registro.chave < chave) {
        anterior = atual;
        atual = lista->data[atual].proximo;
    }

    // Verificar se elemento já existe
    if (atual != INVALIDO && lista->data[atual].registro.chave == chave) {
        return false;
    }

    // Inserir elemento
    int novaPosicao = obterNo(lista);
    lista->data[novaPosicao].registro = registro;

    if (anterior == INVALIDO) {
        // Inserir no início
        lista->data[novaPosicao].proximo = lista->inicioLista;
        lista->inicioLista = novaPosicao;
    } else {
        // Inserir no meio ou final
        lista->data[novaPosicao].proximo = lista->data[anterior].proximo;
        lista->data[anterior].proximo = novaPosicao;
    }

    return true;
}

bool excluirElemento(LISTA_ESTATICA* lista, TIPOCHAVE chave) {
    int anterior = INVALIDO;
    int atual = lista->inicioLista;

    while (atual != INVALIDO && lista->data[atual].registro.chave < chave) {
        anterior = atual;
        atual = lista->data[atual].proximo;
    }

    if (atual == INVALIDO || lista->data[atual].registro.chave != chave) {
        return false;
    }

    if (anterior == INVALIDO) {
        lista->inicioLista = lista->data[atual].proximo;
    } else {
        lista->data[anterior].proximo = lista->data[atual].proximo;
    }

    devolverNo(lista, atual);
    return true;
}

void reinicializarLista(LISTA_ESTATICA* lista) {
    inicializarLista(lista);
}

// Função main para teste
int main() {
    LISTA_ESTATICA lista;
    REGISTRO reg;
    
    printf("=== TESTE DA LISTA LIGADA ESTÁTICA ===\n\n");
    
    // Inicializar lista
    inicializarLista(&lista);
    printf("Lista inicializada.\n");
    printf("Tamanho da lista: %d\n", tamanhoLista(&lista));
    exibirLista(&lista);
    
    // Inserir elementos
    printf("\n--- Inserindo elementos ---\n");
    
    reg.chave = 30;
    if (inserirElementoOrdenado(&lista, reg)) {
        printf("Elemento %d inserido com sucesso.\n", reg.chave);
    } else {
        printf("Falha ao inserir elemento %d.\n", reg.chave);
    }
    
    reg.chave = 10;
    if (inserirElementoOrdenado(&lista, reg)) {
        printf("Elemento %d inserido com sucesso.\n", reg.chave);
    } else {
        printf("Falha ao inserir elemento %d.\n", reg.chave);
    }
    
    reg.chave = 20;
    if (inserirElementoOrdenado(&lista, reg)) {
        printf("Elemento %d inserido com sucesso.\n", reg.chave);
    } else {
        printf("Falha ao inserir elemento %d.\n", reg.chave);
    }
    
    reg.chave = 5;
    if (inserirElementoOrdenado(&lista, reg)) {
        printf("Elemento %d inserido com sucesso.\n", reg.chave);
    } else {
        printf("Falha ao inserir elemento %d.\n", reg.chave);
    }
    
    // Tentar inserir elemento duplicado
    reg.chave = 20;
    if (inserirElementoOrdenado(&lista, reg)) {
        printf("Elemento %d inserido com sucesso.\n", reg.chave);
    } else {
        printf("Falha ao inserir elemento %d (provavelmente duplicado).\n", reg.chave);
    }
    
    printf("\nEstado atual da lista:\n");
    printf("Tamanho: %d\n", tamanhoLista(&lista));
    exibirLista(&lista);
    
    // Buscar elementos
    printf("\n--- Buscando elementos ---\n");
    
    int chaveBusca = 20;
    int posicao = buscaSequencialOrdenada(&lista, chaveBusca);
    if (posicao != INVALIDO) {
        printf("Elemento %d encontrado na posição %d.\n", chaveBusca, posicao);
    } else {
        printf("Elemento %d não encontrado.\n", chaveBusca);
    }
    
    chaveBusca = 99;
    posicao = buscaSequencialOrdenada(&lista, chaveBusca);
    if (posicao != INVALIDO) {
        printf("Elemento %d encontrado na posição %d.\n", chaveBusca, posicao);
    } else {
        printf("Elemento %d não encontrado.\n", chaveBusca);
    }
    
    // Excluir elementos
    printf("\n--- Excluindo elementos ---\n");
    
    chaveBusca = 10;
    if (excluirElemento(&lista, chaveBusca)) {
        printf("Elemento %d excluído com sucesso.\n", chaveBusca);
    } else {
        printf("Falha ao excluir elemento %d.\n", chaveBusca);
    }
    
    chaveBusca = 99;
    if (excluirElemento(&lista, chaveBusca)) {
        printf("Elemento %d excluído com sucesso.\n", chaveBusca);
    } else {
        printf("Falha ao excluir elemento %d (não encontrado).\n", chaveBusca);
    }
    
    printf("\nEstado final da lista:\n");
    printf("Tamanho: %d\n", tamanhoLista(&lista));
    exibirLista(&lista);
    
    // Reinicializar lista
    printf("\n--- Reinicializando lista ---\n");
    reinicializarLista(&lista);
    printf("Tamanho após reinicialização: %d\n", tamanhoLista(&lista));
    exibirLista(&lista);
    
    return 0;
}