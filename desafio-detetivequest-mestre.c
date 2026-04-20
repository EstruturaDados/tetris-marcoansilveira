#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10

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
// STRUCT HASH (pista -> suspeito)
// ----------------------------------------------------
typedef struct Nodo {
    char pista[100];
    char suspeito[50];
    struct Nodo* proximo;
} Nodo;

Nodo* tabela_hash[TAMANHO_TABELA];

// ----------------------------------------------------
// FUNÇÃO HASH
// ----------------------------------------------------
int funcao_hash(const char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAMANHO_TABELA;
}

// ----------------------------------------------------
// INSERIR NA HASH
// ----------------------------------------------------
void inserirNaHash(const char* pista, const char* suspeito) {

    int indice = funcao_hash(pista);

    Nodo* novo = (Nodo*) malloc(sizeof(Nodo));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->proximo = tabela_hash[indice];
    tabela_hash[indice] = novo;
}

// ----------------------------------------------------
// BUSCAR SUSPEITO
// ----------------------------------------------------
char* encontrarSuspeito(const char* pista) {

    int indice = funcao_hash(pista);
    Nodo* atual = tabela_hash[indice];

    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }

    return NULL;
}

// ----------------------------------------------------
// CRIAR SALA
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
// INSERIR PISTA NA BST
// ----------------------------------------------------
struct PistaNode* inserirPista(struct PistaNode* raiz, char* pista) {

    if (raiz == NULL) {
        struct PistaNode* novo = (struct PistaNode*) malloc(sizeof(struct PistaNode));
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

// ----------------------------------------------------
// EXIBIR PISTAS EM ORDEM
// ----------------------------------------------------
void exibirPistas(struct PistaNode* raiz) {

    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// ----------------------------------------------------
// CONTAR PISTAS POR SUSPEITO
// ----------------------------------------------------
int contarPistasSuspeito(struct PistaNode* raiz, const char* suspeito) {

    if (raiz == NULL)
        return 0;

    int count = 0;

    char* s = encontrarSuspeito(raiz->pista);
    if (s != NULL && strcmp(s, suspeito) == 0) {
        count = 1;
    }

    return count +
           contarPistasSuspeito(raiz->esquerda, suspeito) +
           contarPistasSuspeito(raiz->direita, suspeito);
}

// ----------------------------------------------------
// EXPLORAR SALAS
// ----------------------------------------------------
void explorarSalas(struct Sala* atual, struct PistaNode** pistas) {

    char opcao;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);
            *pistas = inserirPista(*pistas, atual->pista);
        }

        printf("\nEscolha:\n");
        printf("e - Esquerda\n");
        printf("d - Direita\n");
        printf("s - Sair\n");
        printf("Opcao: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Sem caminho a esquerda!\n");
        }
        else if (opcao == 'd') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Sem caminho a direita!\n");
        }
        else if (opcao == 's') {
            break;
        }
        else {
            printf("Opcao invalida!\n");
        }
    }
}

// ----------------------------------------------------
// VERIFICAR SUSPEITO FINAL
// ----------------------------------------------------
void verificarSuspeitoFinal(struct PistaNode* pistas) {

    char suspeito[50];

    printf("\nDigite o suspeito final: ");
    scanf(" %[^\n]", suspeito);

    int total = contarPistasSuspeito(pistas, suspeito);

    printf("\nTotal de pistas contra %s: %d\n", suspeito, total);

    if (total >= 2) {
        printf("ACUSACAO CONFIRMADA! %s e o culpado.\n", suspeito);
    } else {
        printf("Provas insuficientes! %s nao pode ser condenado.\n", suspeito);
    }
}

// ----------------------------------------------------
// MAIN
// ----------------------------------------------------
int main() {

    // Inicializa tabela hash
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela_hash[i] = NULL;
    }

    // Mapeamento pista -> suspeito
    inserirNaHash("Controle remoto quebrado", "Carlos");
    inserirNaHash("Livro rasgado", "Ana");
    inserirNaHash("Lencol manchado", "Carlos");
    inserirNaHash("Faca fora do lugar", "Bruno");
    inserirNaHash("Documento suspeito", "Ana");
    inserirNaHash("Pegadas na terra", "Carlos");

    // Montagem da mansão
    struct Sala* raiz = criarSala("Hall de Entrada", "");

    raiz->esquerda = criarSala("Sala de Estar", "Controle remoto quebrado");
    raiz->direita = criarSala("Biblioteca", "Livro rasgado");

    raiz->esquerda->esquerda = criarSala("Quarto", "Lencol manchado");
    raiz->esquerda->direita = criarSala("Cozinha", "Faca fora do lugar");

    raiz->direita->esquerda = criarSala("Escritorio", "Documento suspeito");
    raiz->direita->direita = criarSala("Jardim", "Pegadas na terra");

    struct PistaNode* pistas = NULL;

    printf("=== DETECTIVE QUEST - MESTRE ===\n");

    explorarSalas(raiz, &pistas);

    printf("\n=== PISTAS COLETADAS ===\n");
    exibirPistas(pistas);

    verificarSuspeitoFinal(pistas);

    return 0;
}