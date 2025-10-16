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
    PONT topo;
} PILHA;

// Protótipos das funções
void inicializarPilha(PILHA* pilha);
void reinicializarPilha(PILHA* pilha);
int tamanhoPilha(PILHA* pilha);
bool pilhaCheia();  // Em lista encadeada, geralmente não fica cheia
bool pilhaVazia(PILHA* pilha);
void exibirPilha(PILHA* pilha);
bool empilhar(PILHA* pilha, REGISTRO registro);
bool desempilhar(PILHA* pilha, REGISTRO* registro);
bool topoPilha(PILHA* pilha, REGISTRO* registro);
void destruirPilha(PILHA* pilha);

// Implementações
void inicializarPilha(PILHA* pilha) {
    pilha->topo = NULL;
}

void reinicializarPilha(PILHA* pilha) {
    PONT atual = pilha->topo;
    while (atual != NULL) {
        PONT proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    pilha->topo = NULL;
}

int tamanhoPilha(PILHA* pilha) {
    PONT atual = pilha->topo;
    int contador = 0;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

bool pilhaCheia() {
    // Em lista encadeada, a pilha só fica "cheia" se a memória acabar
    PONT teste = (PONT)malloc(sizeof(ELEMENTO));
    if (teste == NULL) {
        return TRUE;
    }
    free(teste);
    return FALSE;
}

bool pilhaVazia(PILHA* pilha) {
    return pilha->topo == NULL;
}

void exibirPilha(PILHA* pilha) {
    PONT atual = pilha->topo;
    printf("Pilha (topo → base): \" ");
    while (atual != NULL) {
        printf("%d ", atual->registro.chave);
        atual = atual->proximo;
    }
    printf("\" (Tamanho: %d)\n", tamanhoPilha(pilha));
}

bool empilhar(PILHA* pilha, REGISTRO registro) {
    if (pilhaCheia()) {
        printf("ERRO: Memória insuficiente! Não foi possível empilhar %d\n", registro.chave);
        return FALSE;
    }
    
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    if (novo == NULL) {
        return FALSE;
    }
    
    novo->registro = registro;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    return TRUE;
}

bool desempilhar(PILHA* pilha, REGISTRO* registro) {
    if (pilhaVazia(pilha)) {
        printf("ERRO: Pilha vazia! Não há elementos para desempilhar\n");
        return FALSE;
    }
    
    *registro = pilha->topo->registro;
    PONT apagar = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    free(apagar);
    return TRUE;
}

bool topoPilha(PILHA* pilha, REGISTRO* registro) {
    if (pilhaVazia(pilha)) {
        return FALSE;
    }
    
    *registro = pilha->topo->registro;
    return TRUE;
}

void destruirPilha(PILHA* pilha) {
    reinicializarPilha(pilha);
}

// FUNÇÃO MAIN PARA TESTAR TODAS AS FUNCIONALIDADES
int main() {
    PILHA pilha;
    REGISTRO reg, temp;
    int i;
    
    printf("=== TESTE COMPLETO - PILHA DINÂMICA (LISTA ENCADEADA) ===\n\n");
    
    // 1. Teste de inicialização
    printf("1. INICIALIZAÇÃO DA PILHA\n");
    inicializarPilha(&pilha);
    printf("Pilha dinâmica inicializada.\n");
    exibirPilha(&pilha);
    printf("Pilha vazia: %s\n", pilhaVazia(&pilha) ? "SIM" : "NÃO");
    printf("Memória disponível: %s\n\n", pilhaCheia() ? "INSUFICIENTE" : "SUFICIENTE");
    
    // 2. Teste de empilhamento
    printf("2. TESTE DE EMPILHAMENTO (PUSH)\n");
    printf("Empilhando elementos de 1 a 8:\n");
    for (i = 1; i <= 8; i++) {
        reg.chave = i * 10;
        if (empilhar(&pilha, reg)) {
            printf("Empilhado: %d | ", reg.chave);
            exibirPilha(&pilha);
        }
    }
    printf("\n");
    
    // 3. Teste de visualização do topo
    printf("3. VISUALIZAÇÃO DO TOPO\n");
    if (topoPilha(&pilha, &temp)) {
        printf("Elemento no topo: %d\n", temp.chave);
    }
    printf("Tamanho atual: %d\n\n", tamanhoPilha(&pilha));
    
    // 4. Teste de desempilhamento
    printf("4. TESTE DE DESEMPILHAMENTO (POP)\n");
    printf("Desempilhando 5 elementos:\n");
    for (i = 0; i < 5; i++) {
        if (desempilhar(&pilha, &temp)) {
            printf("Desempilhado: %d | ", temp.chave);
            exibirPilha(&pilha);
        }
    }
    printf("\n");
    
    // 5. Teste de comportamento LIFO
    printf("5. DEMONSTRAÇÃO DO COMPORTAMENTO LIFO\n");
    printf("Estado atual: ");
    exibirPilha(&pilha);
    
    printf("Empilhando três elementos:\n");
    int novos[] = {100, 200, 300};
    for (i = 0; i < 3; i++) {
        reg.chave = novos[i];
        empilhar(&pilha, reg);
        printf("Empilhado: %d\n", reg.chave);
    }
    
    printf("Desempilhando TODOS os elementos (ordem LIFO):\n");
    printf("Ordem de saída: ");
    while (!pilhaVazia(&pilha)) {
        desempilhar(&pilha, &temp);
        printf("%d ", temp.chave);
    }
    printf("← Último a entrar é o primeiro a sair\n");
    exibirPilha(&pilha);
    printf("\n");
    
    // 6. Teste de pilha vazia
    printf("6. TESTE DE PILHA VAZIA\n");
    printf("Tentando desempilhar pilha vazia:\n");
    if (!desempilhar(&pilha, &temp)) {
        printf("ERRO capturado: Pilha está vazia\n");
    }
    
    printf("Tentando ver topo de pilha vazia:\n");
    if (!topoPilha(&pilha, &temp)) {
        printf("ERRO capturado: Não há topo (pilha vazia)\n");
    }
    printf("\n");
    
    // 7. Teste de estresse - muitos elementos
    printf("7. TESTE DE ESTRESSE - MÚLTIPLAS OPERAÇÕES\n");
    printf("Realizando 1000 operações de empilhar/desempilhar...\n");
    
    int operacoes = 0;
    for (i = 0; i < 500; i++) {
        reg.chave = i;
        if (empilhar(&pilha, reg)) operacoes++;
        
        if (i % 3 == 0 && !pilhaVazia(&pilha)) {
            if (desempilhar(&pilha, &temp)) operacoes++;
        }
    }
    printf("Operações realizadas: %d\n", operacoes);
    printf("Estado final: ");
    exibirPilha(&pilha);
    printf("\n");
    
    // 8. Teste de memória - destruição
    printf("8. TESTE DE DESTRUIÇÃO DA PILHA\n");
    printf("Pilha antes da destruição: ");
    exibirPilha(&pilha);
    
    destruirPilha(&pilha);
    printf("Pilha após destruição: ");
    exibirPilha(&pilha);
    printf("Pilha vazia: %s\n", pilhaVazia(&pilha) ? "SIM" : "NÃO");
    
    // 9. Teste de reinicialização
    printf("\n9. TESTE DE REINICIALIZAÇÃO\n");
    printf("Reinicializando e testando novamente...\n");
    reinicializarPilha(&pilha);  // Já está vazia, mas testando
    
    // Empilhar alguns elementos finais
    reg.chave = 999;
    empilhar(&pilha, reg);
    reg.chave = 888;
    empilhar(&pilha, reg);
    printf("Pilha final: ");
    exibirPilha(&pilha);
    
    // Limpeza final
    destruirPilha(&pilha);
    
    return 0;
}