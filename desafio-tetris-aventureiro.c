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
        printf("Pilha cheia! Nao e possivel reservar.\n");
        return;
    }

    p->topo++;
    p->itens[p->topo] = nova;
}

void pop(Pilha *p, Peca *removida) {

    if (pilhaVazia(p)) {
        printf("Pilha vazia! Nada para usar.\n");
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

    printf("\nFila de Pecas: ");

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX_FILA) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }

    printf("\n");
}

void mostrarPilha(Pilha *p) {

    printf("Pilha de Reserva (Topo -> Base): ");

    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
    }

    if (pilhaVazia(p)) {
        printf("(vazia)");
    }

    printf("\n");
}

// ----------------------------------------------------
// MENU
// ----------------------------------------------------
void exibirMenu() {
    printf("\n1 - Jogar Peca\n");
    printf("2 - Reservar Peca\n");
    printf("3 - Usar Peca Reservada\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

// ----------------------------------------------------
// MAIN
// ----------------------------------------------------
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
                    printf("Peca reservada: [%c %d]\n", p.tipo, p.id);

                    inserirFila(&fila, gerarPeca(contadorID++));
                } else {
                    printf("Nao e possivel reservar! Pilha cheia.\n");
                }
                break;

            case 3: // Usar peça reservada
                if (!pilhaVazia(&pilha)) {
                    pop(&pilha, &p);
                    printf("Peca usada da reserva: [%c %d]\n", p.tipo, p.id);
                } else {
                    printf("Nao ha pecas na reserva!\n");
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}