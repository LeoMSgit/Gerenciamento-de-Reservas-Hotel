#include <stdio.h>
#include <string.h>

// Definindo a estrutura de endereço
typedef struct endereco {
    char ender[40];
    char munic[20];
    char UF[3];
    char cep[10];
} tipoEnder;

// Definindo a estrutura de hóspede
typedef struct hospede {
    char cpf[14];
    char nome[40];
    char telefone[15];
    int idade;
    tipoEnder endereco;
    float valorHospedagem;
} tipoHospede;

// Definindo a estrutura de apartamento
typedef struct apartamento {
    char situacao; // ‘O’ = Ocupado, ‘R’ = Reservado, ‘.’ = livre
    tipoHospede hospede;
} tipoApto;

// Criando a matriz de estrutura do hotel
tipoApto Hotel[20][14];

//Função para Inicializar a Matriz do Hotel
void inicializaHotel(tipoApto Hotel[20][14]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            Hotel[i][j].situacao = '.';
        }
    }
}
//Funcao para Exibir a Matriz do Hotel
void exibirHotel(tipoApto Hotel[20][14]) {
    printf("Situacao do Hotel (20 andares, 14 apartamentos por andar):\n");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            printf("%c ", Hotel[i][j].situacao);
        }
        printf("\n");
    }
}
//Funcao para fazer Reserva
void reserva(tipoApto Hotel[20][14], int i, int j) {
    if (Hotel[i][j].situacao == '.') {
        Hotel[i][j].situacao = 'R';
        printf("Apartamento %d no andar %d reservado com sucesso!\n", j + 1, 20 - i);
    } else {
        printf("O apartamento %d no andar %d ja esta ocupado ou reservado.\n", j + 1, 20 - i);
    }
}
//Funcao para Cancelar Reserva
void cancelarReserva(tipoApto Hotel[20][14], int i, int j) {
    if (Hotel[i][j].situacao == 'R') {
        Hotel[i][j].situacao = '.';
        printf("Reserva do apartamento %d no andar %d cancelada com sucesso!\n", j + 1, 20 - i);
    } else {
        printf("O apartamento %d no andar %d nao esta reservado.\n", j + 1, 20 - i);
    }
}
//Funcao para fazer Check-in
void checkIn(tipoApto Hotel[20][14], int i, int j, tipoHospede hospede) {
    if (Hotel[i][j].situacao == 'R') {
        Hotel[i][j].situacao = 'O';
        Hotel[i][j].hospede = hospede;
        printf("Check-in realizado com sucesso no apartamento %d do andar %d!\n", j + 1, 20 - i);
    } else {
        printf("O apartamento %d no andar %d não esta reservado.\n", j + 1, 20 - i);
    }
}
//Funcao para fazer Check-out
void checkOut(tipoApto Hotel[20][14], int i, int j) {
    if (Hotel[i][j].situacao == 'O') {
        Hotel[i][j].situacao = '.';
        printf("Check-out realizado com sucesso no apartamento %d do andar %d!\n", j + 1, 20 - i);
    } else {
        printf("O apartamento %d no andar %d nao esta ocupado.\n", j + 1, 20 - i);
    }
}
//Menu Principal
void menu() {
    int opcao, andar, apto, i, j;
    tipoHospede hospede;

    do {
        printf("Menu Principal\n");
        printf("1. Reservar Apartamento\n");
        printf("2. Cancelar Reserva\n");
        printf("3. Check-in\n");
        printf("4. Check-out\n");
        printf("5. Visualizar Hotel\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o andar (1-20): ");
                scanf("%d", &andar);
                printf("Digite o numero do apartamento (1-14): ");
                scanf("%d", &apto);
                i = 20 - andar;
                j = apto - 1;
                reserva(Hotel, i, j);
                break;

            case 2:
                printf("Digite o andar (1-20): ");
                scanf("%d", &andar);
                printf("Digite o numero do apartamento (1-14): ");
                scanf("%d", &apto);
                i = 20 - andar;
                j = apto - 1;
                cancelarReserva(Hotel, i, j);
                break;

            case 3:
                printf("Digite o andar (1-20): ");
                scanf("%d", &andar);
                printf("Digite o numero do apartamento (1-14): ");
                scanf("%d", &apto);
                i = 20 - andar;
                j = apto - 1;
                printf("Digite o CPF do hospede: ");
                scanf("%s", hospede.cpf);
                printf("Digite o nome do hospede: ");
                scanf("%s", hospede.nome);
                printf("Digite o telefone do hospede: ");
                scanf("%s", hospede.telefone);
                printf("Digite a idade do hospede: ");
                scanf("%d", &hospede.idade);
                printf("Digite o valor da hospedagem: ");
                scanf("%f", &hospede.valorHospedagem);
                checkIn(Hotel, i, j, hospede);
                break;

            case 4:
                printf("Digite o andar (1-20): ");
                scanf("%d", &andar);
                printf("Digite o numero do apartamento (1-14): ");
                scanf("%d", &apto);
                i = 20 - andar;
                j = apto - 1;
                checkOut(Hotel, i, j);
                break;

            case 5:
                exibirHotel(Hotel);
                break;

            case 6:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 6);
}
//Função Principal
int main() {
    // Inicialização da matriz do Hotel
    inicializaHotel(Hotel);

    // Exibir o estado inicial da matriz do hotel
    exibirHotel(Hotel);

    // Exibir o menu principal
    menu();

    return 0;
}
