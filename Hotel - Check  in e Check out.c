#include <stdio.h>
#include <stdlib.h>

// Estrutura Dados Hospede - Endereco
struct stendereco {
    char rua[100];
    char numero[5];
    char bairro[40];
    char cidade[40];
    char uf[3]; // Alteração do tamanho de 2 para 3 para incluir o caractere nulo
};

// Estrutura Dados Hospede
struct stquarto {
    char status;
    char nome[50];
    char cpf[12]; // Alteração do tamanho de 11 para 12 para incluir o caractere nulo
    char telefone[12]; // Alteração do tamanho de 11 para 12 para incluir o caractere nulo
    struct stendereco ender; // Estrutura Dados Hospede - Endereco Aninhada
};

// Declaração Funções
void fMostraMat(int m[20][14], char status[20][14]);
int fMenu();
void fCriaMat(int m[20][14], char status[20][14]);
void clearInputBuffer();
void fRealizarCheckIn(int m[20][14], char status[20][14]);
void fRealizarCheckOut(int m[20][14], char status[20][14]);
void fRealizarReserva(int m[20][14], char status[20][14]);
void fCancelarReserva(int m[20][14], char status[20][14]);

// Declaração Variáveis Globais
int n = 1;
int m[20][14];
char status[20][14]; // Matriz para armazenar o status dos quartos

// FUNCAO PRINCIPAL
int main() {
    fCriaMat(m, status);
    while (1) { // Loop continuo ate o usuario optar por sair
        if (fMenu() == 6) {
            printf("\n\nSaindo do sistema.\n");
            break; // Sai do loop e termina o programa
        }
    }
    return 0;
}

// CRIAR MATRIZ
void fCriaMat(int m[20][14], char status[20][14]) {
    // Variavel para preencher a matriz
    int count = 1;

    // Preenchendo a matriz com quartos de 1 a 280 e status '.' (livre)
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            m[i][j] = count++;
            status[i][j] = '.'; // Todos os quartos comecam como livres
        }
    }
}

// MOSTRAR MATRIZ
void fMostraMat(int m[20][14], char status[20][14]) {
    printf("Quartos: ");
    for (int k = 0; k < 14; k++) {
        printf("\t%d", k + 1);
    } // Imprimindo o apartamento correspondente
    printf("\n");
    for (int i = 0; i < 20; i++) {
        printf("Andar %2d: ", 20 - i); // Imprimindo o andar correspondente
        for (int j = 0; j < 14; j++) {
            printf("\t%c", status[19 - i][j]);
        }
        printf("\n");
    }
    printf("\n---------------------------------------------------------------------\n");
}

// MENU PRINCIPAL
int fMenu() {
    int menu; // Declaração da variável menu

    printf("\nBEM VINDO AO MENU PRINCIPAL DO HOTEL\n");
    printf("1 - Mostrar Mapa; 2 - Check-in; 3 - Check-out; 4 - Realizar Reserva; 5 - Cancelar Reserva; 6 - Sair\n");

    if (scanf("%d", &menu) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return 1; // Retorna 1 para continuar no menu
    }

    switch (menu) {
        case 1:
            printf("\nIMPRIMINDO MAPA...\n\n");
            fMostraMat(m, status);
            break;
        case 2:
            fRealizarCheckIn(m, status);
            break;
        case 3:
            fRealizarCheckOut(m, status);
            break;
        case 4:
            fRealizarReserva(m, status);
            break;
        case 5:
            fCancelarReserva(m, status);
            break;
        case 6:
            return 6; // Retorna 6 para sair do programa
        default:
            printf("Opcao invalida! Por favor, tente novamente.\n");
    }

    return 1; // Retorna 1 para continuar no menu
}

// REALIZAR CHECK-IN
void fRealizarCheckIn(int m[20][14], char status[20][14]) {
    int andarQuarto;
    int numeroQuarto;

    printf("\nDigite o numero do andar para check-in (0 para retornar ao Menu): ");

    if (scanf("%d", &andarQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }
    // Retorno Menu Principal
    if (andarQuarto == 0) {
        return;
    }
    // Validar se o número do andar
    if (andarQuarto < 1 || andarQuarto > 20) {
        printf("Numero do andar invalido! Por favor, tente novamente.\n");
        return;
    }

    printf("\nDigite o numero do quarto para check-in (0 para retornar ao Menu): ");
    if (scanf("%d", &numeroQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }
    // Retorno Menu Principal
    if (numeroQuarto == 0) {
        return;
    }
    // Validar se o número do quarto é válido
    if (numeroQuarto < 1 || numeroQuarto > 14) {
        printf("Numero do quarto invalido! Por favor, tente novamente.\n");
        return;
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            if (i == (andarQuarto - 1) && j == (numeroQuarto - 1)) {
                if (status[i][j] == '.') {
                    status[i][j] = 'O'; // Ocupado
                    printf("Check-in realizado com sucesso no quarto %d %d.\n", andarQuarto, numeroQuarto);
                    fMostraMat(m, status); // Imprime a matriz após o check-in
                } else if (status[i][j] == 'R') {
                    printf("O quarto %d %d esta reservado. Não é possível fazer check-in.\n", andarQuarto, numeroQuarto);
                } else {
                    printf("O quarto %d %d ja esta ocupado.\n", andarQuarto, numeroQuarto);
                }
                return;
            }
        }
    }
    printf("Quarto %d nao encontrado.\n", numeroQuarto);
}

// REALIZAR CHECK-OUT
void fRealizarCheckOut(int m[20][14], char status[20][14]) {
    int andarQuarto;
    int numeroQuarto;

    printf("\nDigite o numero do andar para check-out: ");
    if (scanf("%d", &andarQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }

    // Validar se o número do andar é válido
    if (andarQuarto < 1 || andarQuarto > 20) {
        printf("Numero do andar invalido! Por favor, tente novamente.\n");
        return;
    }

    // Retorno Menu Principal
    if (andarQuarto == 0) {
        return;
    }

    printf("\nDigite o numero do quarto para check-out: ");
    if (scanf("%d", &numeroQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }

    // Validar se o número do quarto é válido
    if (numeroQuarto < 1 || numeroQuarto > 14) {
        printf("Numero do quarto invalido! Por favor, tente novamente.\n");
        return;
    }

    // Retorno Menu Principal
    if (numeroQuarto == 0) {
        return;
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            if (i == (andarQuarto - 1) && j == (numeroQuarto - 1)) {
                if (status[i][j] == 'O') { // Ocupado
                    status[i][j] = '.'; // Vago
                    printf("Check-out realizado com sucesso no quarto %d %d.\n", andarQuarto, numeroQuarto);
                    fMostraMat(m, status); // Imprime a matriz após o check-out
                } else if (status[i][j] == 'R') {
                    printf("O quarto %d %d está reservado. Não é possível fazer check-out.\n", andarQuarto, numeroQuarto);
                } else {
                    printf("O quarto %d %d já está livre.\n", andarQuarto, numeroQuarto);
                }
                return;
            }
        }
    }
}

// REALIZAR RESERVA
void fRealizarReserva(int m[20][14], char status[20][14]) {
    int andarQuarto;
    int numeroQuarto;

    printf("\nDigite o numero do andar para reserva (0 para retornar ao Menu): ");

    if (scanf("%d", &andarQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }
    // Retorno Menu Principal
    if (andarQuarto == 0) {
        return;
    }
    // Validar se o número do andar
    if (andarQuarto < 1 || andarQuarto > 20) {
        printf("Numero do andar invalido! Por favor, tente novamente.\n");
        return;
    }

    printf("\nDigite o numero do quarto para reserva (0 para retornar ao Menu): ");
    if (scanf("%d", &numeroQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }
    // Retorno Menu Principal
    if (numeroQuarto == 0) {
        return;
    }
    // Validar se o número do quarto é válido
    if (numeroQuarto < 1 || numeroQuarto > 14) {
        printf("Numero do quarto invalido! Por favor, tente novamente.\n");
        return;
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            if (i == (andarQuarto - 1) && j == (numeroQuarto - 1)) {
                if (status[i][j] == '.') {
                    status[i][j] = 'R'; // Reservado
                    printf("Reserva realizada com sucesso no quarto %d %d.\n", andarQuarto, numeroQuarto);
                    fMostraMat(m, status); // Imprime a matriz após a reserva
                } else if (status[i][j] == 'O') {
                    printf("O quarto %d %d ja esta ocupado.\n", andarQuarto, numeroQuarto);
                } else {
                    printf("O quarto %d %d ja esta reservado.\n", andarQuarto, numeroQuarto);
                }
                return;
            }
        }
    }
    printf("Quarto %d nao encontrado.\n", numeroQuarto);
}

// CANCELAR RESERVA
void fCancelarReserva(int m[20][14], char status[20][14]) {
    int andarQuarto;
    int numeroQuarto;

    printf("\nDigite o numero do andar para cancelar a reserva (0 para retornar ao Menu): ");

    if (scanf("%d", &andarQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }
    // Retorno Menu Principal
    if (andarQuarto == 0) {
        return;
    }
    // Validar se o número do andar
    if (andarQuarto < 1 || andarQuarto > 20) {
        printf("Numero do andar invalido! Por favor, tente novamente.\n");
        return;
    }

    printf("\nDigite o numero do quarto para cancelar a reserva (0 para retornar ao Menu): ");
    if (scanf("%d", &numeroQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }
    // Retorno Menu Principal
    if (numeroQuarto == 0) {
        return;
    }
    // Validar se o número do quarto é válido
    if (numeroQuarto < 1 || numeroQuarto > 14) {
        printf("Numero do quarto invalido! Por favor, tente novamente.\n");
        return;
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            if (i == (andarQuarto - 1) && j == (numeroQuarto - 1)) {
                if (status[i][j] == 'R') { // Reservado
                    status[i][j] = '.'; // Vago
                    printf("Reserva cancelada com sucesso no quarto %d %d.\n", andarQuarto, numeroQuarto);
                    fMostraMat(m, status); // Imprime a matriz após o cancelamento
                } else if (status[i][j] == 'O') {
                    printf("O quarto %d %d ja esta ocupado.\n", andarQuarto, numeroQuarto);
                } else {
                    printf("O quarto %d %d nao esta reservado.\n", andarQuarto, numeroQuarto);
                }
                return;
            }
        }
    }
}

// LIMPAS BUFFER DE ENTRADA
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
