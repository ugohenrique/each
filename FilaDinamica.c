#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INVALIDO -1

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
    PONT fim;
} FILA;

// Protótipos das funções
void inicializarFila(FILA* fila);
void reinicializarFila(FILA* fila);
void destruirFila(FILA* fila);
int tamanhoFila(const FILA* fila);
bool filaCheia();
bool filaVazia(const FILA* fila);
void exibirFila(const FILA* fila);
bool enfileirar(FILA* fila, REGISTRO registro);
bool desenfileirar(FILA* fila, REGISTRO* registro);
bool inicioFila(const FILA* fila, REGISTRO* registro);

// Implementações
void inicializarFila(FILA* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void reinicializarFila(FILA* fila) {
    PONT atual = fila->inicio;
    while (atual != NULL) {
        PONT proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    fila->inicio = NULL;
    fila->fim = NULL;
}

void destruirFila(FILA* fila) {
    reinicializarFila(fila);
}

int tamanhoFila(const FILA* fila) {
    PONT atual = fila->inicio;
    int contador = 0;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

bool filaCheia() {
    // Em lista encadeada, a fila só fica "cheia" se a memória acabar
    PONT teste = (PONT)malloc(sizeof(ELEMENTO));
    if (teste == NULL) {
        return TRUE;
    }
    free(teste);
    return FALSE;
}

bool filaVazia(const FILA* fila) {
    return fila->inicio == NULL;
}

void exibirFila(const FILA* fila) {
    PONT atual = fila->inicio;
    
    if (filaVazia(fila)) {
        printf("Fila: [ VAZIA ]\n");
        return;
    }
    
    printf("Fila (início → fim): [ ");
    while (atual != NULL) {
        printf("%d ", atual->registro.chave);
        atual = atual->proximo;
    }
    printf("] (Tamanho: %d)\n", tamanhoFila(fila));
}

bool enfileirar(FILA* fila, REGISTRO registro) {
    if (filaCheia()) {
        printf("ERRO: Memória insuficiente! Não foi possível enfileirar %d\n", registro.chave);
        return FALSE;
    }
    
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    if (novo == NULL) {
        return FALSE;
    }
    
    novo->registro = registro;
    novo->proximo = NULL;
    
    // Se a fila está vazia, novo elemento é tanto início quanto fim
    if (filaVazia(fila)) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        // Adiciona no fim e atualiza o ponteiro fim
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
    
    return TRUE;
}

bool desenfileirar(FILA* fila, REGISTRO* registro) {
    if (filaVazia(fila)) {
        printf("ERRO: Fila vazia! Não há elementos para desenfileirar\n");
        return FALSE;
    }
    
    *registro = fila->inicio->registro;
    PONT remover = fila->inicio;
    
    // Avança o início
    fila->inicio = fila->inicio->proximo;
    
    // Se a fila ficou vazia, atualiza o fim também
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    free(remover);
    return TRUE;
}

bool inicioFila(const FILA* fila, REGISTRO* registro) {
    if (filaVazia(fila)) {
        return FALSE;
    }
    
    *registro = fila->inicio->registro;
    return TRUE;
}

// FUNÇÃO MAIN PARA TESTAR TODAS AS FUNCIONALIDADES
int main() {
    FILA fila;
    REGISTRO reg, temp;
    int i;
    
    printf("=== TESTE COMPLETO - FILA DINÂMICA (LISTA ENCADEADA) ===\n\n");
    
    // 1. Teste de inicialização
    printf("1. INICIALIZAÇÃO DA FILA\n");
    inicializarFila(&fila);
    printf("Fila dinâmica inicializada.\n");
    exibirFila(&fila);
    printf("Fila vazia: %s\n", filaVazia(&fila) ? "SIM" : "NÃO");
    printf("Memória disponível: %s\n\n", filaCheia() ? "INSUFICIENTE" : "SUFICIENTE");
    
    // 2. Teste de enfileiramento
    printf("2. TESTE DE ENFILEIRAMENTO (ENQUEUE)\n");
    printf("Enfileirando elementos de 1 a 8:\n");
    for (i = 1; i <= 8; i++) {
        reg.chave = i * 10;
        if (enfileirar(&fila, reg)) {
            printf("Enfileirado: %d | ", reg.chave);
            exibirFila(&fila);
        }
    }
    printf("\n");
    
    // 3. Teste de visualização do início
    printf("3. VISUALIZAÇÃO DO INÍCIO\n");
    if (inicioFila(&fila, &temp)) {
        printf("Primeiro elemento da fila: %d\n", temp.chave);
    }
    printf("Tamanho atual: %d\n\n", tamanhoFila(&fila));
    
    // 4. Teste de desenfileiramento
    printf("4. TESTE DE DESENFILEIRAMENTO (DEQUEUE)\n");
    printf("Desenfileirando 5 elementos:\n");
    for (i = 0; i < 5; i++) {
        if (desenfileirar(&fila, &temp)) {
            printf("Desenfileirado: %d | ", temp.chave);
            exibirFila(&fila);
        }
    }
    printf("\n");
    
    // 5. Demonstração do comportamento FIFO
    printf("5. DEMONSTRAÇÃO DO COMPORTAMENTO FIFO\n");
    printf("Estado atual: ");
    exibirFila(&fila);
    
    printf("Enfileirando mais elementos: 90, 100, 110\n");
    reg.chave = 90; enfileirar(&fila, reg);
    reg.chave = 100; enfileirar(&fila, reg);
    reg.chave = 110; enfileirar(&fila, reg);
    exibirFila(&fila);
    
    printf("Ordem de saída (FIFO): ");
    while (!filaVazia(&fila)) {
        desenfileirar(&fila, &temp);
        printf("%d ", temp.chave);
    }
    printf("← Primeiro a entrar é o primeiro a sair\n");
    exibirFila(&fila);
    printf("\n");
    
    // 6. Teste de operações mistas
    printf("6. OPERAÇÕES MISTAS\n");
    printf("Enfileirando elementos: 5, 15, 25\n");
    reg.chave = 5; enfileirar(&fila, reg);
    reg.chave = 15; enfileirar(&fila, reg);
    reg.chave = 25; enfileirar(&fila, reg);
    exibirFila(&fila);
    
    printf("Desenfileirando 1 elemento: ");
    desenfileirar(&fila, &temp);
    printf("%d removido\n", temp.chave);
    
    printf("Enfileirando 35: ");
    reg.chave = 35; enfileirar(&fila, reg);
    exibirFila(&fila);
    
    printf("Desenfileirando todos: ");
    while (!filaVazia(&fila)) {
        desenfileirar(&fila, &temp);
        printf("%d ", temp.chave);
    }
    printf("\n");
    exibirFila(&fila);
    printf("\n");
    
    // 7. Teste de fila vazia
    printf("7. TESTE DE FILA VAZIA\n");
    printf("Tentando desenfileirar fila vazia:\n");
    if (!desenfileirar(&fila, &temp)) {
        printf("ERRO capturado: Fila está vazia\n");
    }
    
    printf("Tentando ver início de fila vazia:\n");
    if (!inicioFila(&fila, &temp)) {
        printf("ERRO capturado: Não há início (fila vazia)\n");
    }
    printf("\n");
    
    // 8. Teste de estresse
    printf("8. TESTE DE ESTRESSE\n");
    printf("Realizando 100 operações de enfileirar/desenfileirar...\n");
    
    int enfileirados = 0, desenfileirados = 0;
    for (i = 0; i < 100; i++) {
        if (i % 3 != 0 || filaVazia(&fila)) {
            // Prioriza enfileirar
            reg.chave = i + 1000;
            if (enfileirar(&fila, reg)) {
                enfileirados++;
            }
        } else {
            // Às vezes desenfileira
            if (desenfileirar(&fila, &temp)) {
                desenfileirados++;
            }
        }
    }
    
    printf("Operações: %d enfileirados, %d desenfileirados\n", enfileirados, desenfileirados);
    printf("Estado final: ");
    exibirFila(&fila);
    printf("\n");
    
    // 9. Teste de ponteiros início e fim
    printf("9. VERIFICAÇÃO DOS PONTEIROS INÍCIO E FIM\n");
    printf("Esvaziando parcialmente a fila...\n");
    for (i = 0; i < 3; i++) {
        desenfileirar(&fila, &temp);
    }
    exibirFila(&fila);
    
    if (fila.inicio != NULL) {
        printf("Início aponta para: %d\n", fila.inicio->registro.chave);
    }
    if (fila.fim != NULL) {
        printf("Fim aponta para: %d\n", fila.fim->registro.chave);
    }
    printf("\n");
    
    // 10. Teste de destruição
    printf("10. DESTRUIÇÃO DA FILA\n");
    printf("Fila antes da destruição: ");
    exibirFila(&fila);
    
    destruirFila(&fila);
    printf("Fila após destruição: ");
    exibirFila(&fila);
    printf("Fila vazia: %s\n", filaVazia(&fila) ? "SIM" : "NÃO");
    
    // Teste final
    printf("\nTeste final - enfileirando após destruição:\n");
    reg.chave = 999; enfileirar(&fila, reg);
    reg.chave = 888; enfileirar(&fila, reg);
    exibirFila(&fila);
    
    return 0;
}