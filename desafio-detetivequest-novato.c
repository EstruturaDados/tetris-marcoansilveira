#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------------------------------------
// STRUCT SALA (nó da árvore)
// ----------------------------------------------------
struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
};

// ----------------------------------------------------
// Criar sala (alocação dinâmica)
// ----------------------------------------------------
struct Sala* criarSala(char* nome) {

    struct Sala* nova = (struct Sala*) malloc(sizeof(struct Sala));

    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

// ----------------------------------------------------
// Explorar salas (navegação na árvore)
// ----------------------------------------------------
void explorarSalas(struct Sala* atual) {

    char opcao;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n", atual->nome);

        // Verifica se é folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho! Voce chegou a um comodo final.\n");
            break;
        }

        printf("Escolha o caminho:\n");
        printf("e - Esquerda\n");
        printf("d - Direita\n");
        printf("s - Sair\n");
        printf("Opcao: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Nao ha caminho para a esquerda!\n");
            }
        }
        else if (opcao == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Nao ha caminho para a direita!\n");
            }
        }
        else if (opcao == 's') {
            printf("Exploracao encerrada.\n");
            break;
        }
        else {
            printf("Opcao invalida!\n");
        }
    }
}

// ----------------------------------------------------
// Liberar memória da árvore
// ----------------------------------------------------
void liberar(struct Sala* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

// ----------------------------------------------------
// MAIN
// ----------------------------------------------------
int main() {

    // Montagem da mansão (árvore fixa)
    struct Sala* raiz = criarSala("Hall de Entrada");

    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Biblioteca");

    raiz->esquerda->esquerda = criarSala("Quarto");
    raiz->esquerda->direita = criarSala("Cozinha");

    raiz->direita->esquerda = criarSala("Escritorio");
    raiz->direita->direita = criarSala("Jardim");

    printf("=== DETECTIVE QUEST ===\n");
    printf("Explore a mansao!\n");

    // Inicia exploração
    explorarSalas(raiz);

    // Libera memória
    liberar(raiz);

    return 0;
}