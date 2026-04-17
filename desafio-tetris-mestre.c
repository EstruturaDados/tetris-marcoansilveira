#include <stdio.h>
#include <stdlib.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// ----------------------------------------------------
// STRUCT PECA
// ----------------------------------------------------
typedef struct {
    char tipo; // I, O, T, L
    int id;
} Peca;

// ----------------------------------------------------
// STRUCT FILA (circular)
// ----------------------------------------------------
typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// ----------------------------------------------------
// STRUCT PILHA
// ----------------------------------------------------
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// ----------------------------------------------------
// FILA - Funções básicas
// ----------------------------------------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

void inserirFila(Fila *f, Peca p) {
    if (filaCheia(f)) return;

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

void removerFila(Fila *f, Peca *p) {
    if (filaVazia(f)) return;

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
}

// ----------------------------------------------------
// PILHA - Funções básicas
// ----------------------------------------------------
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia!\n");
        return;
    }

    p->topo++;
    p->itens[p->topo] = nova;
}

void pop(Pilha *p, Peca *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        return;
    }

    *removida = p->itens[p->topo];
    p->topo--;
}

// ----------------------------------------------------
// GERAR PEÇA
// ----------------------------------------------------
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;

    return p;
}

// ----------------------------------------------------
// EXIBIÇÃO
// ----------------------------------------------------
void mostrarFila(Fila *f) {

    printf("Fila de Pecas: ");

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX_FILA) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }

    printf("\n");
}

void mostrarPilha(Pilha *p) {

    printf("Pilha de Reserva (Topo -> Base): ");

    if (pilhaVazia(p)) {
        printf("(vazia)");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
        }
    }

    printf("\n");
}

// ----------------------------------------------------
// TROCA SIMPLES (frente da fila com topo da pilha)
// ----------------------------------------------------
void trocarTopo(Fila *f, Pilha *p) {

    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Nao e possivel trocar!\n");
        return;
    }

    Peca temp = f->itens[f->inicio];
    f->itens[f->inicio] = p->itens[p->topo];
    p->itens[p->topo] = temp;

    printf("Troca realizada!\n");
}

// ----------------------------------------------------
// TROCA MULTIPLA (3 primeiros da fila com 3 da pilha)
// ----------------------------------------------------
void trocaMultipla(Fila *f, Pilha *p) {

    if (f->total < 3 || p->topo < 2) {
        printf("Nao ha elementos suficientes para troca multipla!\n");
        return;
    }

    for (int i = 0; i < 3; i++) {

        int idxFila = (f->inicio + i) % MAX_FILA;

        Peca temp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[p->topo - i];
        p->itens[p->topo - i] = temp;
    }

    printf("Troca multipla realizada!\n");
}

// ----------------------------------------------------
// MENU
// ----------------------------------------------------
void exibirMenu() {

    printf("\n=== Estado Atual ===\n");

    printf("\n1 - Jogar peca da frente da fila\n");
    printf("2 - Enviar peca da fila para reserva (pilha)\n");
    printf("3 - Usar peca da reserva (pilha)\n");
    printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
    printf("5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
    printf("0 - Sair\n");

    printf("Opcao: ");
}

// ----------------------------------------------------
// MAIN
// ----------------------------------------------------
// 🔄  Nível Mestre: Integração Estratégica entre Fila e Pilha
//
// - Implemente interações avançadas entre as estruturas:
//      4 - Trocar a peça da frente da fila com o topo da pilha
//      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
// - Para a opção 4:
//      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
//      Troque os elementos diretamente nos arrays.
// - Para a opção 5:
//      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
//      Use a lógica de índice circular para acessar os primeiros da fila.
// - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
// - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
// - O menu deve ficar assim:
//      4 - Trocar peça da frente com topo da pilha
//      5 - Trocar 3 primeiros da fila com os 3 da pilha
int main() {

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int contadorID = 0;
    int opcao;

    // Inicializa fila cheia
    for (int i = 0; i < MAX_FILA; i++) {
        inserirFila(&fila, gerarPeca(contadorID++));
    }

    do {

        printf("\n=== Estado Atual ===\n\n");
        mostrarFila(&fila);
        mostrarPilha(&pilha);

        exibirMenu();
        scanf("%d", &opcao);

        Peca p;

        switch (opcao) {

            case 1: // Jogar peça
                removerFila(&fila, &p);
                printf("Peca jogada: [%c %d]\n", p.tipo, p.id);

                inserirFila(&fila, gerarPeca(contadorID++));
                break;

            case 2: // Reservar peça
                if (!pilhaCheia(&pilha)) {
                    removerFila(&fila, &p);
                    push(&pilha, p);
                    printf("Peca enviada para reserva: [%c %d]\n", p.tipo, p.id);

                    inserirFila(&fila, gerarPeca(contadorID++));
                } else {
                    printf("Pilha cheia!\n");
                }
                break;

            case 3: // Usar peça da pilha
                if (!pilhaVazia(&pilha)) {
                    pop(&pilha, &p);
                    printf("Peca usada: [%c %d]\n", p.tipo, p.id);
                } else {
                    printf("Pilha vazia!\n");
                }
                break;

            case 4: // Troca simples
                trocarTopo(&fila, &pilha);
                break;

            case 5: // Troca múltipla
                trocaMultipla(&fila, &pilha);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}