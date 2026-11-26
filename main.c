
#include <stdio.h>
#include <string.h>

#define MAX 100

// ==========================================
// 1. DEFINICAO DOS TIPOS DE DADOS (TAD)
// ==========================================

// Estrutura que representa um chamado
typedef struct {
    int id;
    char nome[50];
    char descricao[200];
} Chamado;

// Estrutura que representa a fila
typedef struct {
    Chamado chamados[MAX];
    int quantidade;
    int proximoID;
} Fila;

// ==========================================
// 2. PROTOTIPOS DAS FUNCOES
// ==========================================

void inicializarFila(Fila *fila);
int filaVazia(Fila *fila);
int filaCheia(Fila *fila);
int buscarChamado(Fila *fila, int id);

int enfileirar(Fila *fila, char nome[], char descricao[]);
void consultarFila(Fila *fila);
int atualizarChamado(Fila *fila, int id, char nome[], char descricao[]);
int cancelarChamado(Fila *fila, int id);
int atenderProximo(Fila *fila);

// ==========================================
// 3. FUNCOES DA TAD FILA
// ==========================================

// Inicializa a fila
void inicializarFila(Fila *fila) {
    fila->quantidade = 0;
    fila->proximoID = 1;
}

// Verifica se a fila esta vazia
int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

// Verifica se a fila esta cheia
int filaCheia(Fila *fila) {
    return fila->quantidade == MAX;
}

// Busca um chamado pelo ID
int buscarChamado(Fila *fila, int id) {
    int i = 0;

    while (i < fila->quantidade) {
        if (fila->chamados[i].id == id) {
            return i;
        }
        i++;
    }

    return -1;
}

// Adiciona um novo chamado no final da fila
int enfileirar(Fila *fila, char nome[], char descricao[]) {

    if (filaCheia(fila)) {
        return -1;
    }

    int id = fila->proximoID;

    fila->chamados[fila->quantidade].id = id;

    strcpy(fila->chamados[fila->quantidade].nome, nome);

    strcpy(fila->chamados[fila->quantidade].descricao, descricao);

    fila->quantidade++;
    fila->proximoID++;

    return id;
}

// Mostra todos os chamados da fila
void consultarFila(Fila *fila) {

    if (filaVazia(fila)) {
        printf("\nNenhum chamado aguardando atendimento.\n");
        return;
    }

    printf("\n========================================\n");
    printf("       CHAMADOS AGUARDANDO ATENDIMENTO\n");
    printf("========================================\n");

    int i = 0;

    while (i < fila->quantidade) {

        printf("\nID: %d\n", fila->chamados[i].id);
        printf("Cliente: %s\n", fila->chamados[i].nome);
        printf("Problema: %s\n", fila->chamados[i].descricao);

        if (i == 0) {
            printf("Status: PROXIMO PARA ATENDIMENTO\n");
        } else {
            printf("Status: AGUARDANDO NA FILA\n");
        }

        printf("----------------------------------------\n");

        i++;
    }
}

// Atualiza os dados de um chamado
int atualizarChamado(Fila *fila, int id, char nome[], char descricao[]) {

    int posicao = buscarChamado(fila, id);

    if (posicao == -1) {
        return 0;
    }

    strcpy(fila->chamados[posicao].nome, nome);

    strcpy(fila->chamados[posicao].descricao, descricao);

    return 1;
}

// Cancela um chamado especifico
int cancelarChamado(Fila *fila, int id) {

    int posicao = buscarChamado(fila, id);

    if (posicao == -1) {
        return 0;
    }

    int i = posicao;

    while (i < fila->quantidade - 1) {

        fila->chamados[i] = fila->chamados[i + 1];

        i++;
    }

    fila->quantidade--;

    return 1;
}

// Finaliza o atendimento do primeiro chamado
int atenderProximo(Fila *fila) {

    if (filaVazia(fila)) {
        return 0;
    }

    printf("\n========================================\n");
    printf("          ATENDIMENTO FINALIZADO\n");
    printf("========================================\n");

    printf("ID: %d\n", fila->chamados[0].id);
    printf("Cliente: %s\n", fila->chamados[0].nome);
    printf("Problema: %s\n", fila->chamados[0].descricao);

    // Desloca os chamados para a esquerda
    int i = 0;

    while (i < fila->quantidade - 1) {

        fila->chamados[i] = fila->chamados[i + 1];

        i++;
    }

    fila->quantidade--;

    printf("\nChamado removido da fila com sucesso!\n");

    return 1;
}

// ==========================================
// 4. PROGRAMA PRINCIPAL
// ==========================================

int main() {

    Fila fila;
    int opcao;
    int id;
    int resultado;

    char nome[50];
    char descricao[200];

    inicializarFila(&fila);

    do {

        printf("\n========================================\n");
        printf("       SISTEMA DE SUPORTE AO CLIENTE\n");
        printf("========================================\n");

        printf("1. Abrir novo chamado\n");
        printf("2. Consultar chamados\n");
        printf("3. Atualizar chamado\n");
        printf("4. Cancelar chamado\n");
        printf("5. Finalizar proximo atendimento\n");
        printf("6. Sair do sistema\n");

        printf("----------------------------------------\n");
        printf("Digite a opcao desejada: ");

        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

            // ABRIR CHAMADO
            case 1:

                if (filaCheia(&fila)) {

                    printf("\nFila de atendimento cheia!\n");

                } else {

                    printf("\n[NOVO CHAMADO]\n");

                    printf("Nome do cliente: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    printf("Descricao do problema: ");
                    fgets(descricao, sizeof(descricao), stdin);
                    descricao[strcspn(descricao, "\n")] = '\0';

                    if (strlen(nome) == 0 || strlen(descricao) == 0) {

                        printf("\nPreencha todos os campos!\n");

                    } else {

                        resultado = enfileirar(&fila, nome, descricao);

                        if (resultado != -1) {

                            printf("\nChamado registrado com sucesso!\n");
                            printf("Numero do chamado: %d\n", resultado);

                        }
                    }
                }

                break;

            // CONSULTAR CHAMADOS
            case 2:

                consultarFila(&fila);

                break;

            // ATUALIZAR CHAMADO
            case 3:

                if (filaVazia(&fila)) {

                    printf("\nNao existem chamados para atualizar.\n");

                } else {

                    printf("\n[ATUALIZAR CHAMADO]\n");

                    printf("Digite o ID do chamado: ");
                    scanf("%d", &id);
                    getchar();

                    if (buscarChamado(&fila, id) == -1) {

                        printf("\nChamado nao encontrado!\n");

                    } else {

                        printf("Novo nome do cliente: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = '\0';

                        printf("Nova descricao do problema: ");
                        fgets(descricao, sizeof(descricao), stdin);
                        descricao[strcspn(descricao, "\n")] = '\0';

                        if (strlen(nome) == 0 || strlen(descricao) == 0) {

                            printf("\nPreencha todos os campos!\n");

                        } else {

                            atualizarChamado(&fila, id, nome, descricao);

                            printf("\nChamado atualizado com sucesso!\n");
                        }
                    }
                }

                break;

            // CANCELAR CHAMADO
            case 4:

                if (filaVazia(&fila)) {

                    printf("\nNao existem chamados para cancelar.\n");

                } else {

                    printf("\n[CANCELAR CHAMADO]\n");

                    printf("Digite o ID do chamado: ");
                    scanf("%d", &id);
                    getchar();

                    resultado = cancelarChamado(&fila, id);

                    if (resultado == 1) {

                        printf("\nChamado cancelado com sucesso!\n");

                    } else {

                        printf("\nID nao encontrado!\n");
                    }
                }

                break;

            // FINALIZAR ATENDIMENTO
            case 5:

                resultado = atenderProximo(&fila);

                if (resultado == 0) {

                    printf("\nNao existem chamados para atender.\n");

                }

                break;

            // SAIR
            case 6:

                printf("\nEncerrando o sistema. Ate breve!\n");

                break;

            default:

                printf("\nOpcao invalida! Escolha de 1 a 6.\n");

                break;
        }

    } while (opcao != 6);

    return 0;
}
