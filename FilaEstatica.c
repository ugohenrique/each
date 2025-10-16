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
    REGISTRO dados[MAX];
    int inicio;
    int tamanho;
} FILA;

// Protótipos das funções - OPERAÇÕES DE FILA
void inicializarFila(FILA* fila);
void reinicializarFila(FILA* fila);
int tamanhoFila(const FILA* fila);
bool filaCheia(const FILA* fila);
bool filaVazia(const FILA* fila);
void exibirFila(const FILA* fila);
bool enfileirar(FILA* fila, REGISTRO registro);
bool desenfileirar(FILA* fila, REGISTRO* registro);
bool inicioFila(const FILA* fila, REGISTRO* registro);

// Implementações
void inicializarFila(FILA* fila) {
    fila->inicio = 0;
    fila->tamanho = 0;
}

void reinicializarFila(FILA* fila) {
    fila->inicio = 0;
    fila->tamanho = 0;
}

int tamanhoFila(const FILA* fila) {
    return fila->tamanho;
}

bool filaCheia(const FILA* fila) {
    return fila->tamanho >= MAX;
}

bool filaVazia(const FILA* fila) {
    return fila->tamanho == 0;
}

void exibirFila(const FILA* fila) {
    if (filaVazia(fila)) {
        printf("Fila: [ VAZIA ]\n");
        return;
    }
    
    printf("Fila (início → fim): [ ");
    int pos = fila->inicio;
    for (int i = 0; i < fila->tamanho; i++) {
        printf("%d ", fila->dados[pos].chave);
        pos = (pos + 1) % MAX;
    }
    printf("] (Tamanho: %d)\n", fila->tamanho);
}

bool enfileirar(FILA* fila, REGISTRO registro) {
    if (filaCheia(fila)) {
        printf("ERRO: Fila cheia! Não foi possível enfileirar %d\n", registro.chave);
        return FALSE;
    }
    
    int fim = (fila->inicio + fila->tamanho) % MAX;
    fila->dados[fim] = registro;
    fila->tamanho++;
    
    return TRUE;
}

bool desenfileirar(FILA* fila, REGISTRO* registro) {
    if (filaVazia(fila)) {
        printf("ERRO: Fila vazia! Não há elementos para desenfileirar\n");
        return FALSE;
    }
    
    *registro = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;
    fila->tamanho--;
    
    return TRUE;
}

bool inicioFila(const FILA* fila, REGISTRO* registro) {
    if (filaVazia(fila)) {
        return FALSE;
    }
    
    *registro = fila->dados[fila->inicio];
    return TRUE;
}

// FUNÇÃO MAIN PARA TESTAR TODAS AS FUNCIONALIDADES
int main() {
    FILA fila;
    REGISTRO reg, temp;
    int i;
    
    printf("=== TESTE COMPLETO - FILA CIRCULAR (FIFO) ===\n\n");
    
    // 1. Teste de inicialização
    printf("1. INICIALIZAÇÃO DA FILA\n");
    inicializarFila(&fila);
    printf("Fila circular inicializada.\n");
    exibirFila(&fila);
    printf("Fila vazia: %s\n", filaVazia(&fila) ? "SIM" : "NÃO");
    printf("Fila cheia: %s\n\n", filaCheia(&fila) ? "SIM" : "NÃO");
    
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
    
    // 6. Teste de circularidade
    printf("6. TESTE DE CIRCULARIDADE\n");
    printf("Enfileirando elementos até preencher parcialmente...\n");
    for (i = 1; i <= 5; i++) {
        reg.chave = i;
        enfileirar(&fila, reg);
    }
    exibirFila(&fila);
    
    printf("Desenfileirando 3 elementos...\n");
    for (i = 0; i < 3; i++) {
        desenfileirar(&fila, &temp);
        printf("Removido: %d\n", temp.chave);
    }
    exibirFila(&fila);
    
    printf("Enfileirando mais 8 elementos (testando wrap-around)...\n");
    for (i = 10; i <= 18; i++) {
        reg.chave = i;
        enfileirar(&fila, reg);
    }
    exibirFila(&fila);
    printf("Início: %d, Tamanho: %d\n", fila.inicio, fila.tamanho);
    printf("\n");
    
    // 7. Teste de fila vazia
    printf("7. TESTE DE FILA VAZIA\n");
    printf("Esvaziando a fila completamente...\n");
    while (!filaVazia(&fila)) {
        desenfileirar(&fila, &temp);
        printf("Desenfileirado: %d | Elementos restantes: %d\n", 
               temp.chave, tamanhoFila(&fila));
    }
    
    printf("Tentando desenfileirar fila vazia:\n");
    if (!desenfileirar(&fila, &temp)) {
        printf("ERRO capturado: Fila está vazia\n");
    }
    
    printf("Tentando ver início de fila vazia:\n");
    if (!inicioFila(&fila, &temp)) {
        printf("ERRO capturado: Não há início (fila vazia)\n");
    }
    printf("\n");
    
    // 8. Teste de fila cheia
    printf("8. TESTE DE FILA CHEIA\n");
    printf("Preenchendo fila até o limite (%d elementos)...\n", MAX);
    for (i = 1; i <= MAX + 3; i++) {
        reg.chave = i * 100;
        if (!enfileirar(&fila, reg)) {
            printf("Fila cheia! Não foi possível enfileirar %d\n", i * 100);
            break;
        }
    }
    printf("Estado final: ");
    exibirFila(&fila);
    printf("Fila cheia: %s\n", filaCheia(&fila) ? "SIM" : "NÃO");
    printf("\n");
    
    // 9. Teste de estresse - operações mistas
    printf("9. TESTE DE ESTRESSE - OPERAÇÕES MISTAS\n");
    reinicializarFila(&fila);
    
    printf("Realizando 50 operações mistas...\n");
    int enfileirados = 0, desenfileirados = 0;
    
    for (i = 0; i < 50; i++) {
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
    
    // 10. Teste de reinicialização
    printf("10. TESTE DE REINICIALIZAÇÃO\n");
    printf("Fila antes: ");
    exibirFila(&fila);
    
    reinicializarFila(&fila);
    printf("Fila após reinicialização: ");
    exibirFila(&fila);
    
    // Teste final
    printf("\nEnfileirando alguns elementos finais para verificar funcionamento:\n");
    reg.chave = 999; enfileirar(&fila, reg);
    reg.chave = 888; enfileirar(&fila, reg);
    reg.chave = 777; enfileirar(&fila, reg);
    exibirFila(&fila);
    
    return 0;
}