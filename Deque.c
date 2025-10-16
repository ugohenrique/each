#include <stdio.h>
#include <stdlib.h>

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
    struct aux *anterior;
    struct aux *proximo;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct {
    PONT cabeca;
} DEQUE;

// Protótipos das funções - OPERAÇÕES DE DEQUE
void inicializarDeque(DEQUE* deque);
void reinicializarDeque(DEQUE* deque);
void destruirDeque(DEQUE* deque);
int tamanhoDeque(const DEQUE* deque);
bool dequeVazio(const DEQUE* deque);
void exibirDequeInicio(const DEQUE* deque);
void exibirDequeFim(const DEQUE* deque);
bool inserirInicio(DEQUE* deque, REGISTRO registro);
bool inserirFim(DEQUE* deque, REGISTRO registro);
bool removerInicio(DEQUE* deque, REGISTRO* registro);
bool removerFim(DEQUE* deque, REGISTRO* registro);
bool primeiroElemento(const DEQUE* deque, REGISTRO* registro);
bool ultimoElemento(const DEQUE* deque, REGISTRO* registro);

// Implementações
void inicializarDeque(DEQUE* deque) {
    deque->cabeca = (PONT)malloc(sizeof(ELEMENTO));
    if (deque->cabeca == NULL) {
        printf("Erro: Falha na alocação do nó cabeça!\n");
        exit(1);
    }
    deque->cabeca->proximo = deque->cabeca;
    deque->cabeca->anterior = deque->cabeca;
}

void reinicializarDeque(DEQUE* deque) {
    PONT atual = deque->cabeca->proximo;
    
    while (atual != deque->cabeca) {
        PONT proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    deque->cabeca->proximo = deque->cabeca;
    deque->cabeca->anterior = deque->cabeca;
}

void destruirDeque(DEQUE* deque) {
    reinicializarDeque(deque);
    free(deque->cabeca);
    deque->cabeca = NULL;
}

int tamanhoDeque(const DEQUE* deque) {
    int contador = 0;
    PONT atual = deque->cabeca->proximo;
    
    while (atual != deque->cabeca) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

bool dequeVazio(const DEQUE* deque) {
    return deque->cabeca->proximo == deque->cabeca;
}

void exibirDequeInicio(const DEQUE* deque) {
    PONT atual = deque->cabeca->proximo;
    
    if (dequeVazio(deque)) {
        printf("Deque: [ VAZIO ]\n");
        return;
    }
    
    printf("Deque (início → fim): [ ");
    while (atual != deque->cabeca) {
        printf("%d ", atual->registro.chave);
        atual = atual->proximo;
    }
    printf("] (Tamanho: %d)\n", tamanhoDeque(deque));
}

void exibirDequeFim(const DEQUE* deque) {
    PONT atual = deque->cabeca->anterior;
    
    if (dequeVazio(deque)) {
        printf("Deque: [ VAZIO ]\n");
        return;
    }
    
    printf("Deque (fim → início): [ ");
    while (atual != deque->cabeca) {
        printf("%d ", atual->registro.chave);
        atual = atual->anterior;
    }
    printf("] (Tamanho: %d)\n", tamanhoDeque(deque));
}

bool inserirInicio(DEQUE* deque, REGISTRO registro) {
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    if (novo == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        return false;
    }
    
    novo->registro = registro;
    
    // Insere entre a cabeça e o primeiro elemento
    novo->anterior = deque->cabeca;
    novo->proximo = deque->cabeca->proximo;
    
    deque->cabeca->proximo->anterior = novo;
    deque->cabeca->proximo = novo;
    
    return true;
}

bool inserirFim(DEQUE* deque, REGISTRO registro) {
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    if (novo == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        return false;
    }
    
    novo->registro = registro;
    
    // Insere entre o último elemento e a cabeça
    novo->proximo = deque->cabeca;
    novo->anterior = deque->cabeca->anterior;
    
    deque->cabeca->anterior->proximo = novo;
    deque->cabeca->anterior = novo;
    
    return true;
}

bool removerInicio(DEQUE* deque, REGISTRO* registro) {
    if (dequeVazio(deque)) {
        printf("Erro: Deque vazio! Não há elementos para remover do início.\n");
        return false;
    }
    
    PONT remover = deque->cabeca->proximo;
    *registro = remover->registro;
    
    // Ajusta os ponteiros
    deque->cabeca->proximo = remover->proximo;
    remover->proximo->anterior = deque->cabeca;
    
    free(remover);
    return true;
}

bool removerFim(DEQUE* deque, REGISTRO* registro) {
    if (dequeVazio(deque)) {
        printf("Erro: Deque vazio! Não há elementos para remover do fim.\n");
        return false;
    }
    
    PONT remover = deque->cabeca->anterior;
    *registro = remover->registro;
    
    // Ajusta os ponteiros
    deque->cabeca->anterior = remover->anterior;
    remover->anterior->proximo = deque->cabeca;
    
    free(remover);
    return true;
}

bool primeiroElemento(const DEQUE* deque, REGISTRO* registro) {
    if (dequeVazio(deque)) {
        return false;
    }
    
    *registro = deque->cabeca->proximo->registro;
    return true;
}

bool ultimoElemento(const DEQUE* deque, REGISTRO* registro) {
    if (dequeVazio(deque)) {
        return false;
    }
    
    *registro = deque->cabeca->anterior->registro;
    return true;
}
// Função main para teste completo
int main() {
    DEQUE deque;
    REGISTRO reg, temp;
    int i;
    
    printf("=== TESTE COMPLETO - DEQUE (DOUBLE-ENDED QUEUE) ===\n\n");
    
    // 1. Teste de inicialização
    printf("1. INICIALIZAÇÃO DO DEQUE\n");
    inicializarDeque(&deque);
    printf("Deque circular duplamente encadeado inicializado.\n");
    exibirDequeInicio(&deque);
    printf("Deque vazio: %s\n\n", dequeVazio(&deque) ? "SIM" : "NÃO");
    
    // 2. Teste de inserção no início
    printf("2. INSERÇÃO NO INÍCIO\n");
    printf("Inserindo 30, 20, 10 no início:\n");
    reg.chave = 30; inserirInicio(&deque, reg);
    reg.chave = 20; inserirInicio(&deque, reg);
    reg.chave = 10; inserirInicio(&deque, reg);
    exibirDequeInicio(&deque);
    exibirDequeFim(&deque);
    printf("\n");
    
    // 3. Teste de inserção no fim
    printf("3. INSERÇÃO NO FIM\n");
    printf("Inserindo 40, 50, 60 no fim:\n");
    reg.chave = 40; inserirFim(&deque, reg);
    reg.chave = 50; inserirFim(&deque, reg);
    reg.chave = 60; inserirFim(&deque, reg);
    exibirDequeInicio(&deque);
    exibirDequeFim(&deque);
    printf("\n");
    
    // 4. Teste de consulta das extremidades
    printf("4. CONSULTA DAS EXTREMIDADES\n");
    if (primeiroElemento(&deque, &temp)) {
        printf("Primeiro elemento: %d\n", temp.chave);
    }
    if (ultimoElemento(&deque, &temp)) {
        printf("Último elemento: %d\n", temp.chave);
    }
    printf("\n");
    
    // 5. Teste de remoção do início
    printf("5. REMOÇÃO DO INÍCIO\n");
    printf("Removendo 3 elementos do início:\n");
    for (i = 0; i < 3; i++) {
        if (removerInicio(&deque, &temp)) {
            printf("Removido do início: %d | ", temp.chave);
            exibirDequeInicio(&deque);
        }
    }
    printf("\n");
    
    // 6. Teste de remoção do fim
    printf("6. REMOÇÃO DO FIM\n");
    printf("Removendo 2 elementos do fim:\n");
    for (i = 0; i < 2; i++) {
        if (removerFim(&deque, &temp)) {
            printf("Removido do fim: %d | ", temp.chave);
            exibirDequeInicio(&deque);
        }
    }
    printf("\n");
    
    // 7. Teste de operações mistas
    printf("7. OPERAÇÕES MISTAS\n");
    printf("Estado atual: ");
    exibirDequeInicio(&deque);
    
    printf("Inserindo 100 no início e 200 no fim:\n");
    reg.chave = 100; inserirInicio(&deque, reg);
    reg.chave = 200; inserirFim(&deque, reg);
    exibirDequeInicio(&deque);
    
    printf("Removendo do início e fim alternadamente:\n");
    removerInicio(&deque, &temp);
    printf("Removido do início: %d\n", temp.chave);
    removerFim(&deque, &temp);
    printf("Removido do fim: %d\n", temp.chave);
    printf("Estado final: ");
    exibirDequeInicio(&deque);
    printf("\n");
    
    // 8. Teste de deque vazio
    printf("8. TESTE DE DEQUE VAZIO\n");
    printf("Esvaziando o deque completamente...\n");
    while (!dequeVazio(&deque)) {
        removerInicio(&deque, &temp);
        printf("Removido: %d | Elementos restantes: %d\n", temp.chave, tamanhoDeque(&deque));
    }
    
    printf("Tentando remover de deque vazio:\n");
    if (!removerInicio(&deque, &temp)) {
        printf("Erro capturado: Deque está vazio\n");
    }
    if (!removerFim(&deque, &temp)) {
        printf("Erro capturado: Deque está vazio\n");
    }
    printf("\n");
    
    // 9. Teste de estresse
    printf("9. TESTE DE ESTRESSE\n");
    printf("Realizando 100 operações de inserção/remoção...\n");
    
    int operacoes = 0;
    for (i = 0; i < 50; i++) {
        reg.chave = i;
        if (i % 2 == 0) {
            if (inserirInicio(&deque, reg)) operacoes++;
        } else {
            if (inserirFim(&deque, reg)) operacoes++;
        }
        
        if (i % 5 == 0 && !dequeVazio(&deque)) {
            if (i % 10 == 0) {
                if (removerInicio(&deque, &temp)) operacoes++;
            } else {
                if (removerFim(&deque, &temp)) operacoes++;
            }
        }
    }
    printf("Operações realizadas: %d\n", operacoes);
    printf("Estado final: ");
    exibirDequeInicio(&deque);
    printf("\n");
    
    // 10. Teste de destruição
    printf("10. DESTRUIÇÃO DO DEQUE\n");
    printf("Deque antes da destruição: ");
    exibirDequeInicio(&deque);
    
    destruirDeque(&deque);
    printf("Deque destruído com sucesso!\n");
    
    return 0;
}