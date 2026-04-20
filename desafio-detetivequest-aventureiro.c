#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------------------------------------
// STRUCT SALA (árvore binária da mansão)
// ----------------------------------------------------
struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
};

// ----------------------------------------------------
// STRUCT BST DE PISTAS
// ----------------------------------------------------
struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
};

// ----------------------------------------------------
// Criar sala (com ou sem pista)
// ----------------------------------------------------
struct Sala* criarSala(char* nome, char* pista) {

    struct Sala* nova = (struct Sala*) malloc(sizeof(struct Sala));

    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);

    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

// ----------------------------------------------------
// Criar nó da BST de pistas
// ----------------------------------------------------
struct PistaNode* criarPistaNode(char* pista) {

    struct PistaNode* novo = (struct PistaNode*) malloc(sizeof(struct PistaNode));

    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

// ----------------------------------------------------
// Inserir pista na BST (ordenado)
// ----------------------------------------------------
struct PistaNode* inserirPista(struct PistaNode* raiz, char* pista) {

    if (raiz == NULL)
        return criarPistaNode(pista);

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

// ----------------------------------------------------
// Exibir pistas em ordem alfabética
// ----------------------------------------------------
void exibirPistas(struct PistaNode* raiz) {

    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// ----------------------------------------------------
// Explorar salas + coletar pistas
// ----------------------------------------------------
void explorarSalasComPistas(struct Sala* atual, struct PistaNode** arvorePistas) {

    char opcao;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n", atual->nome);

        // Coleta pista automaticamente (se existir)
        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        printf("\nEscolha o caminho:\n");
        printf("e - Esquerda\n");
        printf("d - Direita\n");
        printf("s - Sair\n");
        printf("Opcao: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Nao ha caminho para a esquerda!\n");
        }
        else if (opcao == 'd') {
            if (atual->direita != NULeL)
                atual = atual->direita;
            else
                printf("Nao ha caminho para a direita!\n");
        }
        else if (opcao == 's') {
            printf("\nExploracao encerrada.\n");
            break;
        }
        else {
            printf("Opcao invalida!\n");
        }
    }
}

// ----------------------------------------------------
// Liberar árvore de salas
// ----------------------------------------------------
void liberarSalas(struct Sala* raiz) {
    if (raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

// ----------------------------------------------------
// Liberar BST de pistas
// ----------------------------------------------------
void liberarPistas(struct PistaNode* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

// ----------------------------------------------------
// MAIN
// ----------------------------------------------------
int main() {

    // ---------------- MONTAGEM DA MANSÃO ----------------
    struct Sala* raiz = criarSala("Hall de Entrada", "");

    raiz->esquerda = criarSala("Sala de Estar", "Controle remoto quebrado");
    raiz->direita = criarSala("Biblioteca", "Livro com pagina rasgada");

    raiz->esquerda->esquerda = criarSala("Quarto", "Lencol manchado");
    raiz->esquerda->direita = criarSala("Cozinha", "Faca fora do lugar");

    raiz->direita->esquerda = criarSala("Escritorio", "Documento suspeito");
    raiz->direita->direita = criarSala("Jardim", "Pegadas na terra");

    // BST de pistas
    struct PistaNode* pistas = NULL;

    printf("=== DETECTIVE QUEST - COLETA DE PISTAS ===\n");

    // Exploração
    explorarSalasComPistas(raiz, &pistas);

    // ---------------- RESULTADO FINAL ----------------
    printf("\n=== PISTAS COLETADAS (ORDENADAS) ===\n");
    exibirPistas(pistas);

    // Liberação de memória
    liberarSalas(raiz);
    liberarPistas(pistas);

    return 0;
}