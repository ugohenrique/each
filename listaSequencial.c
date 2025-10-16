#include <stdio.h>

#define MAX 50
#define TRUE 1
#define FALSE 0
#define INVALIDO -1

typedef int TIPOCHAVE;
typedef int bool;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct {
    REGISTRO A[MAX];
    int numeroElementos;
} LISTA;

// Protótipos das funções
void inicializarLista(LISTA* lista);
void reinicializarLista(LISTA* lista);
int tamanhoLista(LISTA* lista);
bool listaCheia(LISTA* lista);
bool listaVazia(LISTA* lista);
void exibirLista(LISTA* lista);
int buscaSequencial(LISTA* lista, TIPOCHAVE chave);
int buscaSentinela(LISTA* lista, TIPOCHAVE chave);
int buscaBinaria(LISTA* lista, TIPOCHAVE chave);
bool inserirElemento(LISTA* lista, REGISTRO registro, int posicao);
bool inserirOrdenado(LISTA* lista, REGISTRO registro);
bool inserirInicio(LISTA* lista, REGISTRO registro);
bool inserirFim(LISTA* lista, REGISTRO registro);
bool excluirElemento(LISTA* lista, TIPOCHAVE chave);

// Implementações
void inicializarLista(LISTA* lista) {
    lista->numeroElementos = 0;
}

void reinicializarLista(LISTA* lista) {
    lista->numeroElementos = 0;
}

int tamanhoLista(LISTA* lista) {
    return lista->numeroElementos;
}

bool listaCheia(LISTA* lista) {
    return lista->numeroElementos >= MAX;
}

bool listaVazia(LISTA* lista) {
    return lista->numeroElementos == 0;
}

void exibirLista(LISTA* lista) {
    int i;
    printf("Lista: \" ");
    for (i = 0; i < lista->numeroElementos; i++) {
        printf("%i ", lista->A[i].chave);
    }
    printf("\" (Tamanho: %d)\n", lista->numeroElementos);
}

int buscaSequencial(LISTA* lista, TIPOCHAVE chave) {
    int i = 0;
    while (i < lista->numeroElementos) {
        if (chave == lista->A[i].chave)
            return i;
        i++;
    }
    return INVALIDO;
}

int buscaSentinela(LISTA* lista, TIPOCHAVE chave) {
    int i = 0;
    
    if (lista->numeroElementos == 0) return INVALIDO;
    
    // Configura sentinela
    lista->A[lista->numeroElementos].chave = chave;
    
    while (lista->A[i].chave != chave) 
        i++;
    
    if (i == lista->numeroElementos)
        return INVALIDO;
    else
        return i;
}

int buscaBinaria(LISTA* lista, TIPOCHAVE chave) {
    int esquerda, direita, meio;
    
    if (lista->numeroElementos == 0) return INVALIDO;
    
    esquerda = 0;
    direita = lista->numeroElementos - 1;
    
    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;
        
        if (lista->A[meio].chave == chave)
            return meio;
        else if (lista->A[meio].chave < chave)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }
    
    return INVALIDO;
}

bool inserirElemento(LISTA* lista, REGISTRO registro, int posicao) {
    int j;
    
    if (listaCheia(lista) || posicao < 0 || posicao > lista->numeroElementos)
        return FALSE;
    
    // Desloca elementos para a direita
    for (j = lista->numeroElementos; j > posicao; j--)
        lista->A[j] = lista->A[j - 1];
    
    lista->A[posicao] = registro;
    lista->numeroElementos++;
    return TRUE;
}

bool inserirOrdenado(LISTA* lista, REGISTRO registro) {
    if (listaCheia(lista)) return FALSE;
    
    int posicao = lista->numeroElementos;
    
    // Encontra a posição correta (lista deve estar ordenada)
    while (posicao > 0 && lista->A[posicao - 1].chave > registro.chave) {
        lista->A[posicao] = lista->A[posicao - 1];
        posicao--;
    }
    
    lista->A[posicao] = registro;
    lista->numeroElementos++;
    return TRUE;
}

bool inserirInicio(LISTA* lista, REGISTRO registro) {
    return inserirElemento(lista, registro, 0);
}

bool inserirFim(LISTA* lista, REGISTRO registro) {
    return inserirElemento(lista, registro, lista->numeroElementos);
}

bool excluirElemento(LISTA* lista, TIPOCHAVE chave) {
    int posicao, j;
    
    posicao = buscaSequencial(lista, chave);
    if (posicao == INVALIDO) 
        return FALSE;
    
    // Desloca elementos para a esquerda
    for (j = posicao; j < lista->numeroElementos - 1; j++) {
        lista->A[j] = lista->A[j + 1];
    }
    
    lista->numeroElementos--;
    return TRUE;
}

bool excluirElementoOrdenado(LISTA* lista, TIPOCHAVE chave) {
    int posicao, j;
    
    posicao = buscaBinaria(lista, chave);
    if (posicao == INVALIDO) 
        return FALSE;
    
    // Desloca elementos para a esquerda
    for (j = posicao; j < lista->numeroElementos - 1; j++) {
        lista->A[j] = lista->A[j + 1];
    }
    
    lista->numeroElementos--;
    return TRUE;
}

// FUNÇÃO MAIN PARA TESTAR TODAS AS FUNCIONALIDADES
int main() {
    LISTA lista;
    REGISTRO reg;
    int i;

    printf("=== TESTE COMPLETO - LISTA LINEAR SEQUENCIAL ===\n\n");

    // 1. Teste de inicialização
    printf("1. INICIALIZAÇÃO\n");
    inicializarLista(&lista);
    printf("Lista inicializada.\n");
    exibirLista(&lista);
    printf("Lista vazia: %s\n", listaVazia(&lista) ? "SIM" : "NÃO");
    printf("Lista cheia: %s\n\n", listaCheia(&lista) ? "SIM" : "NÃO");

    // 2. Teste de inserção no início
    printf("2. INSERÇÃO NO INÍCIO\n");
    for (i = 5; i >= 1; i--) {
        reg.chave = i * 10;
        if (inserirInicio(&lista, reg)) {
            printf("Inserido no início: %d\n", reg.chave);
        }
    }
    exibirLista(&lista);
    printf("\n");

    // 3. Teste de inserção no fim
    printf("3. INSERÇÃO NO FIM\n");
    for (i = 6; i <= 8; i++) {
        reg.chave = i * 10;
        if (inserirFim(&lista, reg)) {
            printf("Inserido no fim: %d\n", reg.chave);
        }
    }
    exibirLista(&lista);
    printf("\n");

    // 4. Teste de inserção em posição específica
    printf("4. INSERÇÃO EM POSIÇÃO ESPECÍFICA\n");
    reg.chave = 25;
    if (inserirElemento(&lista, reg, 2))
        printf("Inserido 25 na posição 2\n");
    
    reg.chave = 35;
    if (inserirElemento(&lista, reg, 4))
        printf("Inserido 35 na posição 4\n");
    
    exibirLista(&lista);
    printf("\n");

    // 5. Teste de buscas
    printf("5. TESTE DE BUSCAS\n");
    int chavesBusca[] = {25, 50, 99, 10, 80};
    for (i = 0; i < 5; i++) {
        int posSeq = buscaSequencial(&lista, chavesBusca[i]);
        int posSent = buscaSentinela(&lista, chavesBusca[i]);
        
        printf("Chave %d: ", chavesBusca[i]);
        if (posSeq != INVALIDO) {
            printf("Sequencial[%d] Sentinela[%d]\n", posSeq, posSent);
        } else {
            printf("Não encontrada\n");
        }
    }
    printf("\n");

    // 6. Teste de lista ordenada
    printf("6. TESTE COM LISTA ORDENADA\n");
    LISTA listaOrdenada;
    inicializarLista(&listaOrdenada);
    
    int elementos[] = {30, 10, 50, 20, 40, 5, 60};
    printf("Inserindo elementos em ordem: ");
    for (i = 0; i < 7; i++) {
        printf("%d ", elementos[i]);
        reg.chave = elementos[i];
        inserirOrdenado(&listaOrdenada, reg);
    }
    printf("\n");
    exibirLista(&listaOrdenada);
    
    // Busca binária na lista ordenada
    printf("Busca binária - Chave 20: ");
    int posBin = buscaBinaria(&listaOrdenada, 20);
    if (posBin != INVALIDO) 
        printf("Encontrada na posição %d\n", posBin);
    else
        printf("Não encontrada\n");
        
    printf("Busca binária - Chave 25: ");
    posBin = buscaBinaria(&listaOrdenada, 25);
    if (posBin != INVALIDO) 
        printf("Encontrada na posição %d\n", posBin);
    else
        printf("Não encontrada\n");
    printf("\n");

    // 7. Teste de exclusão
    printf("7. TESTE DE EXCLUSÃO\n");
    printf("Lista original: ");
    exibirLista(&lista);
    
    int chavesExcluir[] = {25, 10, 80, 99};
    for (i = 0; i < 4; i++) {
        if (excluirElemento(&lista, chavesExcluir[i])) {
            printf("Excluído %d: ", chavesExcluir[i]);
            exibirLista(&lista);
        } else {
            printf("Falha ao excluir %d (não encontrado)\n", chavesExcluir[i]);
        }
    }
    printf("\n");

    // 8. Teste de limites
    printf("8. TESTE DE LIMITES\n");
    reinicializarLista(&lista);
    printf("Lista reinicializada: ");
    exibirLista(&lista);
    
    // Tentar encher a lista
    printf("Preenchendo lista até o limite...\n");
    for (i = 0; i < MAX + 2; i++) {
        reg.chave = i + 1;
        if (!inserirFim(&lista, reg)) {
            printf("Não foi possível inserir %d - lista cheia (%d elementos)\n", 
                   reg.chave, tamanhoLista(&lista));
            break;
        }
    }
    exibirLista(&lista);
    
    // Tentar inserir em lista cheia
    reg.chave = 999;
    if (!inserirInicio(&lista, reg)) {
        printf("Falha ao inserir %d - lista cheia\n", reg.chave);
    }

    return 0;
}