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
    int topo;
} PILHA;

// Protótipos das funções - OPERAÇÕES DE PILHA
void inicializarPilha(PILHA* pilha);
void reinicializarPilha(PILHA* pilha);
int tamanhoPilha(PILHA* pilha);
bool pilhaCheia(PILHA* pilha);
bool pilhaVazia(PILHA* pilha);
void exibirPilha(PILHA* pilha);
bool empilhar(PILHA* pilha, REGISTRO registro);
bool desempilhar(PILHA* pilha, REGISTRO* registro);
bool topoPilha(PILHA* pilha, REGISTRO* registro);

// Implementações
void inicializarPilha(PILHA* pilha) {
    pilha->topo = -1;
}

void reinicializarPilha(PILHA* pilha) {
    pilha->topo = -1;
}

int tamanhoPilha(PILHA* pilha) {
    return pilha->topo + 1;
}

bool pilhaCheia(PILHA* pilha) {
    return pilha->topo >= MAX - 1;
}

bool pilhaVazia(PILHA* pilha) {
    return pilha->topo == -1;
}

void exibirPilha(PILHA* pilha) {
    int i;
    printf("Pilha (topo → base): \" ");
    for (i = pilha->topo; i >= 0; i--) {
        printf("%d ", pilha->dados[i].chave);
    }
    printf("\" (Tamanho: %d)\n", tamanhoPilha(pilha));
}

bool empilhar(PILHA* pilha, REGISTRO registro) {
    if (pilhaCheia(pilha)) {
        printf("ERRO: Pilha cheia! Não foi possível empilhar %d\n", registro.chave);
        return FALSE;
    }
    
    pilha->topo++;
    pilha->dados[pilha->topo] = registro;
    return TRUE;
}

bool desempilhar(PILHA* pilha, REGISTRO* registro) {
    if (pilhaVazia(pilha)) {
        printf("ERRO: Pilha vazia! Não há elementos para desempilhar\n");
        return FALSE;
    }
    
    *registro = pilha->dados[pilha->topo];
    pilha->topo--;
    return TRUE;
}

bool topoPilha(PILHA* pilha, REGISTRO* registro) {
    if (pilhaVazia(pilha)) {
        return FALSE;
    }
    
    *registro = pilha->dados[pilha->topo];
    return TRUE;
}

// FUNÇÃO MAIN PARA TESTAR TODAS AS FUNCIONALIDADES
int main() {
    PILHA pilha;
    REGISTRO reg, temp;
    int i;
    
    printf("=== TESTE COMPLETO - PILHA (LIFO) ===\n\n");
    
    // 1. Teste de inicialização
    printf("1. INICIALIZAÇÃO DA PILHA\n");
    inicializarPilha(&pilha);
    printf("Pilha inicializada.\n");
    exibirPilha(&pilha);
    printf("Pilha vazia: %s\n", pilhaVazia(&pilha) ? "SIM" : "NÃO");
    printf("Pilha cheia: %s\n\n", pilhaCheia(&pilha) ? "SIM" : "NÃO");
    
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
    printf("\n");
    
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
    
    // 5. Teste misto (empilhar e desempilhar)
    printf("5. TESTE MISTO\n");
    printf("Estado atual: ");
    exibirPilha(&pilha);
    
    printf("Empilhando 25 e 35:\n");
    reg.chave = 25;
    empilhar(&pilha, reg);
    reg.chave = 35;
    empilhar(&pilha, reg);
    exibirPilha(&pilha);
    
    printf("Desempilhando 2 elementos:\n");
    desempilhar(&pilha, &temp);
    printf("Desempilhado: %d\n", temp.chave);
    desempilhar(&pilha, &temp);
    printf("Desempilhado: %d\n", temp.chave);
    printf("Estado final: ");
    exibirPilha(&pilha);
    printf("\n");
    
    // 6. Teste de pilha cheia
    printf("6. TESTE DE LIMITES - PILHA CHEIA\n");
    reinicializarPilha(&pilha);
    printf("Pilha reinicializada: ");
    exibirPilha(&pilha);
    
    printf("Preenchendo pilha até o limite (%d elementos)...\n", MAX);
    for (i = 1; i <= MAX + 3; i++) {
        reg.chave = i;
        if (!empilhar(&pilha, reg)) {
            printf("Pilha cheia! Não foi possível empilhar %d\n", i);
            break;
        }
    }
    printf("Pilha final: ");
    exibirPilha(&pilha);
    printf("\n");
    
    // 7. Teste de pilha vazia
    printf("7. TESTE DE LIMITES - PILHA VAZIA\n");
    printf("Esvaziando a pilha...\n");
    while (!pilhaVazia(&pilha)) {
        desempilhar(&pilha, &temp);
        printf("Desempilhado: %d | Elementos restantes: %d\n", 
               temp.chave, tamanhoPilha(&pilha));
    }
    
    printf("Tentando desempilhar pilha vazia:\n");
    if (!desempilhar(&pilha, &temp)) {
        printf("ERRO capturado: Pilha está vazia\n");
    }
    
    // 8. Demonstração do comportamento LIFO
    printf("\n8. DEMONSTRAÇÃO DO COMPORTAMENTO LIFO\n");
    reinicializarPilha(&pilha);
    
    printf("Empilhando: A, B, C\n");
    reg.chave = 'A'; empilhar(&pilha, reg);
    reg.chave = 'B'; empilhar(&pilha, reg);
    reg.chave = 'C'; empilhar(&pilha, reg);
    exibirPilha(&pilha);
    
    printf("Desempilhando: ");
    while (!pilhaVazia(&pilha)) {
        desempilhar(&pilha, &temp);
        printf("%c ", temp.chave);
    }
    printf("← Último a entrar é o primeiro a sair (LIFO)\n");
    
    return 0;
}