#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/// Estrutura da Sala (nó da árvore binária)
typedef struct Sala {
    char nome[50];
    struct Sala *esq;
    struct Sala *dir;
} Sala;


/// Cria dinamicamente uma sala usando malloc
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro: Falha ao alocar memória!\n");
        exit(1);
    }

    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
}


/// Verifica se a árvore está vazia
int arvoreVazia(Sala *raiz) {
    return (raiz == NULL);
}


/// Libera memória da árvore inteira (sem aparecer ao usuário)
void liberarArvore(Sala *raiz) {
    if (raiz == NULL)
        return;

    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);

    free(raiz);
}


/// Exploração interativa com opção para VOLTAR ao Hall
void explorarSalas(Sala *raiz) {

    if (arvoreVazia(raiz)) {
        printf("A árvore está vazia! Não há salas para explorar.\n");
        return;
    }

    Sala *atual = raiz;
    char escolha;

    while (1) {

        printf("\nVocê está na sala: %s\n", atual->nome);

        // Caso seja nó folha
        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Não há mais caminhos a partir daqui.\n");

            printf("\nDeseja voltar ao Hall (v) ou sair (s)? ");
            scanf(" %c", &escolha);

            if (escolha == 'v') {
                atual = raiz;
                continue;
            } else {
                printf("Exploração encerrada.\n");
                return;
            }
        }

        // Opções de navegação
        printf("Deseja ir para:\n");
        if (atual->esq != NULL)
            printf("  (e) Esquerda → %s\n", atual->esq->nome);
        if (atual->dir != NULL)
            printf("  (d) Direita  → %s\n", atual->dir->nome);
        printf("  (v) Voltar ao Hall de Entrada\n");
        printf("  (s) Sair da exploração\n");

        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esq != NULL) {
            atual = atual->esq;
        }
        else if (escolha == 'd' && atual->dir != NULL) {
            atual = atual->dir;
        }
        else if (escolha == 'v') {
            atual = raiz;
        }
        else if (escolha == 's') {
            printf("Exploração encerrada.\n");
            return;
        }
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}


/// Função principal: monta a árvore e inicia a exploração
int main() {

    // Criação das salas (dinâmico com malloc)
    Sala *hall       = criarSala("Hall de Entrada");
    Sala *salaEstar  = criarSala("Sala de Estar");
    Sala *cozinha    = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim     = criarSala("Jardim");
    Sala *quarto     = criarSala("Quarto");
    Sala *adega      = criarSala("Adega");

    // Montagem da árvore
    hall->esq = salaEstar;
    hall->dir = cozinha;

    salaEstar->esq = biblioteca;
    salaEstar->dir = jardim;

    cozinha->dir = adega;
    jardim->dir  = quarto;

    // Exploração da mansão
    explorarSalas(hall);

    // Liberação da memória da árvore inteira
    liberarArvore(hall);

    return 0;
}
