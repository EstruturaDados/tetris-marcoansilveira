#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// ----------------------------------------------------
// STRUCT PECA (equivalente a Pessoa do exemplo)
// ----------------------------------------------------
typedef struct {
    char tipo; // I, O, T, L
    int id;
} Peca;

// ----------------------------------------------------
// STRUCT FILA
// ----------------------------------------------------
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// ----------------------------------------------------
// Inicializar fila
// ----------------------------------------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// ----------------------------------------------------
// Verificações
// ----------------------------------------------------
int filaCheia(Fila *f) {
    return f->total == MAX;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

// ----------------------------------------------------
// Gerar peça automaticamente
// ----------------------------------------------------
Peca gerarPeca(int id) {

    char tipos[] = {'I', 'O', 'T', 'L'};
    
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;

    return p;
}

// ----------------------------------------------------
// Inserir peça (enqueue)
// ----------------------------------------------------
void inserir(Fila *f, Peca p) {

    if (filaCheia(f)) {
        printf("Fila cheia! Nao e possivel inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

// ----------------------------------------------------
// Remover peça (dequeue)
// ----------------------------------------------------
void remover(Fila *f, Peca *p) {

    if (filaVazia(f)) {
        printf("Fila vazia! Nao ha pecas para jogar.\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

// ----------------------------------------------------
// Mostrar fila
// ----------------------------------------------------
void mostrarFila(Fila *f) {

    printf("\nFila de Pecas: ");

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }

    printf("\n");
}

// ----------------------------------------------------
// Menu
// ----------------------------------------------------
void exibirMenu() {
    printf("\n1 - Jogar Peca (dequeue)\n");
    printf("2 - Inserir Nova Peca (enqueue)\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

// ----------------------------------------------------
// MAIN
// 🧩 Nível Novato: Fila de Peças Futuras
//
// - Crie uma struct Peca com os campos: tipo (char) e id (int).
// - Implemente uma fila circular com capacidade para 5 peças.
// - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
// - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
// - Exiba a fila após cada ação com uma função mostrarFila().
// - Use um menu com opções como:
//      1 - Jogar peça (remover da frente)
//      0 - Sair
// - A cada remoção, insira uma nova peça ao final da fila.
// ----------------------------------------------------
int main() {

    Fila fila;
    inicializarFila(&fila);

    int contadorID = 0;
    int opcao;

    // Inicializa fila com 5 peças
    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca(contadorID++));
    }

    do {

        mostrarFila(&fila);
        exibirMenu();
        scanf("%d", &opcao);

        Peca p;

        switch (opcao) {

            case 1:
                remover(&fila, &p);
                if (p.id != 0 || fila.total >= 0) {
                    printf("Voce jogou a peca: [%c %d]\n", p.tipo, p.id);
                }
                break;

            case 2:
                inserir(&fila, gerarPeca(contadorID++));
                break;

            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}