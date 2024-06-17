//JLM-Ativ4 - Projeto Hotel
//Leonardo, Matheus, João Alfredo – 09/06/2024
//Controlar a ocupação, check-in, check-out e reservas dos apartamentos do hotel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura Dados Hospede - Endereco
struct stendereco {
	char rua[100];
	char numero[5];
	char bairro[40];
	char cidade[40];
	char uf[3];
};

// Estrutura Dados Hospede
struct stquarto {
	char status;
	char nome[50];
	char cpf[12];
	char telefone[12];
	char email[50];
	struct stendereco ender; // Estrutura Dados Hospede - Endereco Aninhada
};

// Declaração Funções
void fMostraMat(int m[20][14], struct stquarto quartos[20][14]);
int fMenu();
void fCriaMat(int m[20][14], struct stquarto quartos[20][14]);
void clearInputBuffer();
void fRealizarCheckIn(int m[20][14], struct stquarto quartos[20][14]);
void fRealizarCheckOut(int m[20][14], struct stquarto quartos[20][14]);
void fRealizarReserva(int m[20][14], struct stquarto quartos[20][14]);
void fCancelarReserva(int m[20][14], struct stquarto quartos[20][14]);
void fInformacoesHospede(int m[20][14], struct stquarto quartos[20][14]);
int ValidaNome(const char *nome);
int ValidaCPF(const char *cpf);
int ValidaTelefone(const char *telefone);
int ValidaUF(const char *uf);

// Declaração Variáveis Globais
int n = 1;
int m[20][14];
struct stquarto quartos[20][14]; // Matriz para armazenar os quartos e os dados dos hóspedes

// FUNCAO PRINCIPAL
int main() {
	fCriaMat(m, quartos);
	while (1) { // Loop contínuo até o usuário optar por sair
		if (fMenu() == 7) {
			printf("\n\nSaindo do sistema.\n");
			break; // Sai do loop e termina o programa
		}
	}
	return 0;
}

// CRIAR MATRIZ
void fCriaMat(int m[20][14], struct stquarto quartos[20][14]) {
	// Variável para preencher a matriz
	int count = 1;

	// Preenchendo a matriz com quartos de 1 a 280 e status '.' (livre)
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 14; j++) {
			m[i][j] = count++;
			quartos[i][j].status = '.';
		}
	}
}

// MOSTRAR MATRIZ E OCUPAÇÃO
void fMostraMat(int m[20][14], struct stquarto quartos[20][14]) {
	int totalQuartos = 20 * 14;
	int vagos = 0;
	int ocupados = 0;
	int reservados = 0;

	printf("Quartos: ");
	for (int k = 0; k < 14; k++) {
		printf("\t%d", k + 1);
	}
	printf("\n");
	for (int i = 0; i < 20; i++) {
		printf("Andar %2d: ", 20 - i);
		for (int j = 0; j < 14; j++) {
			printf("\t%c", quartos[19 - i][j].status);
			if (quartos[19 - i][j].status == '.') {
				vagos++;
			} else if (quartos[19 - i][j].status == 'O') {
				ocupados++;
			} else if (quartos[19 - i][j].status == 'R') {
				reservados++;
			}
		}
		printf("\n");
	}
	printf("\n---------------------------------------------------------------------\n");
	printf("Porcentagem de quartos vagos: %.2f%%\n", ((float)vagos / totalQuartos) * 100);
	printf("Porcentagem de quartos ocupados: %.2f%%\n", ((float)ocupados / totalQuartos) * 100);
	printf("Porcentagem de quartos reservados: %.2f%%\n", ((float)reservados / totalQuartos) * 100);
}

// MENU PRINCIPAL
int fMenu() {
	int menu; // Declaração da variável menu

	printf("\nBEM VINDO AO MENU PRINCIPAL DO HOTEL\n");
	printf("1 - Mostrar Mapa;\n2 - Check-in;\n3 - Check-out;\n4 - Realizar Reserva;\n5 - Cancelar Reserva;\n6 - Informacoes do Hospede;\n7 - Sair;\n");
	printf("Digite uma opcao: ");
	if (scanf("%d", &menu) != 1) {
		clearInputBuffer();
		printf("Entrada invalida! Por favor, insira um numero.\n");
		return 1; // Retorna 1 para continuar no menu
	}

	switch (menu) {
		case 1:
			printf("\nIMPRIMINDO MAPA...\n\n");
			fMostraMat(m, quartos);
			break;
		case 2:
			fRealizarCheckIn(m, quartos);
			break;
		case 3:
			fRealizarCheckOut(m, quartos);
			break;
		case 4:
			fRealizarReserva(m, quartos);
			break;
		case 5:
			fCancelarReserva(m, quartos);
			break;
		case 6:
			fInformacoesHospede(m, quartos);
			break;
		case 7:
			return 7; // Retorna 7 para sair do programa
		default:
			printf("\nOpcao invalida! Por favor, tente novamente.\n");
	}

	return 1; // Retorna 1 para continuar no menu
}

//REALIZAR CHECK-IN
void fRealizarCheckIn(int m[20][14], struct stquarto quartos[20][14]) {
	int andarQuarto;
	int numeroQuarto;
	struct stquarto novoHospede;

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
	// Validar se o número do andar é válido
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

	if (quartos[andarQuarto - 1][numeroQuarto - 1].status == '.') {
		// Preencher dados do hospede
		printf("\nDigite o nome do hospede: ");
		clearInputBuffer();
		fgets(novoHospede.nome, sizeof(novoHospede.nome), stdin);
		strtok(novoHospede.nome, "\n"); // Remover a quebra de linha do final

		// Validar se o nome não está em branco e contém apenas letras e espaços
		int nomeValido = 1;
		for (int i = 0; novoHospede.nome[i] != '\0'; i++) {
			if (!isalpha(novoHospede.nome[i]) && novoHospede.nome[i] != ' ') {
				nomeValido = 0;
				break;
			}
		}
		if (strlen(novoHospede.nome) == 0 || !nomeValido) {
			printf("Nome do hospede invalido! Por favor, insira um nome valido sem numeros.\n");
			return;
		}

		printf("\nDigite o CPF do hospede (apenas numeros): ");
		fgets(novoHospede.cpf, sizeof(novoHospede.cpf), stdin);
		strtok(novoHospede.cpf, "\n"); // Remover a quebra de linha do final

		// Validar se o CPF não está em branco e possui o tamanho correto e contém apenas números
		int cpfValido = 1;
		for (int i = 0; novoHospede.cpf[i] != '\0'; i++) {
			if (!isdigit(novoHospede.cpf[i])) {
				cpfValido = 0;
				break;
			}
		}
		if (strlen(novoHospede.cpf) != 11 || !cpfValido) {
			printf("CPF do hospede invalido! Por favor, insira um CPF valido.\n");
			return;
		}

		printf("\nDigite o telefone do hospede (apenas numeros, com DDD): ");
		clearInputBuffer();
		fgets(novoHospede.telefone, sizeof(novoHospede.telefone), stdin);
		strtok(novoHospede.telefone, "\n"); // Remover a quebra de linha do final

		// Validar se o telefone não está em branco e possui o tamanho correto e contém apenas números
		int telefoneValido = 1;
		int digitCount = 0;
		for (int i = 0; novoHospede.telefone[i] != '\0'; i++) {
			if (isdigit(novoHospede.telefone[i])) {
				digitCount++;
			} else if (novoHospede.telefone[i] != ' ') {
				telefoneValido = 0;
				break;
			}
		}
		if (strlen(novoHospede.telefone) != 11 || digitCount != 11 || !telefoneValido) {
			printf("Telefone do hospede invalido! Por favor, insira um telefone valido.\n");
			return;
		}

		// Digitar o email do hóspede
		printf("\nDigite o email do hospede: ");
		clearInputBuffer();
		fgets(novoHospede.email, sizeof(novoHospede.email), stdin);
		strtok(novoHospede.email, "\n"); // Remover a quebra de linha do final

		// Validar se o email não está em branco e contém o símbolo '@'
		int emailValido = 0;
		for (int i = 0; novoHospede.email[i] != '\0'; i++) {
			if (novoHospede.email[i] == '@') {
				emailValido = 1;
				break;
			}
		}
		if (strlen(novoHospede.email) == 0 || !emailValido) {
			printf("Email do hospede invalido! Por favor, insira um email valido.\n");
		}

		// Preencher dados do endereço
		printf("\nDigite a rua do hospede (apenas nome): ");
		clearInputBuffer();
		fgets(novoHospede.ender.rua, sizeof(novoHospede.ender.rua), stdin);
		strtok(novoHospede.ender.rua, "\n"); // Remover a quebra de linha do final

		// Validar se o bairro não está vazio e não contém números
		int ruaValido = 1;
		for (int i = 0; novoHospede.ender.rua[i] != '\0'; i++) {
			if (!isalpha(novoHospede.ender.rua[i]) && novoHospede.ender.rua[i] != ' ') {
				ruaValido = 0;
				break;
			}
		}
		if (strlen(novoHospede.ender.rua) == 0 || !ruaValido) {
			printf("Rua do hospede invalido! Por favor, insira um valor valido.\n");
			return;
		}

		printf("\nDigite o numero do hospede: ");
		fgets(novoHospede.ender.numero, sizeof(novoHospede.ender.numero), stdin);
		strtok(novoHospede.ender.numero, "\n"); // Remover a quebra de linha do final

		// Validar se o número da rua contém apenas dígitos
		int numeroValido = 1;
		if (strlen(novoHospede.ender.numero) > 0) { // Verifica se a string não está vazia
			for (int i = 0; novoHospede.ender.numero[i] != '\0'; i++) {
				if (!isdigit(novoHospede.ender.numero[i])) {
					numeroValido = 0;
					break;
				}
			}
		} else {
			numeroValido = 0; // Se a string está vazia, é inválida
		}

		if (!numeroValido) {
			printf("Numero do hospede invalido! Por favor, insira um valor numerico valido.\n");
			return;
		}

		printf("\nDigite o bairro do hospede: ");
		fgets(novoHospede.ender.bairro, sizeof(novoHospede.ender.bairro), stdin);
		strtok(novoHospede.ender.bairro, "\n"); // Remover a quebra de linha do final

		// Validar se o bairro não está vazio e não contém números
		int bairroValido = 1;
		for (int i = 0; novoHospede.ender.bairro[i] != '\0'; i++) {
			if (!isalpha(novoHospede.ender.bairro[i]) && novoHospede.ender.bairro[i] != ' ') {
				bairroValido = 0;
				break;
			}
		}
		if (strlen(novoHospede.ender.bairro) == 0 || !bairroValido) {
			printf("Bairro do hospede invalido! Por favor, insira um valor valido.\n");
			return;
		}

		printf("\nDigite a cidade do hospede: ");
		fgets(novoHospede.ender.cidade, sizeof(novoHospede.ender.cidade), stdin);
		strtok(novoHospede.ender.cidade, "\n"); // Remover a quebra de linha do final

		// Validar se a cidade não está vazia e não contém números
		int cidadeValida = 1;
		for (int i = 0; novoHospede.ender.cidade[i] != '\0'; i++) {
			if (!isalpha(novoHospede.ender.cidade[i]) && novoHospede.ender.cidade[i] != ' ') {
				cidadeValida = 0;
				break;
			}
		}
		if (strlen(novoHospede.ender.cidade) == 0 || !cidadeValida) {
			printf("Cidade do hospede invalida! Por favor, insira um valor valido.\n");
			return;
		}

		printf("\nDigite o UF do hospede: ");
		fgets(novoHospede.ender.uf, sizeof(novoHospede.ender.uf), stdin);
		strtok(novoHospede.ender.uf, "\n"); // Remover a quebra de linha do final

		// Validar se o UF é válido
		int ufValido = 1;
		if (strlen(novoHospede.ender.uf) != 2 || !isalpha(novoHospede.ender.uf[0]) || !isalpha(novoHospede.ender.uf[1])) {
			ufValido = 0;
		}
		if (!ufValido) {
			printf("UF do hospede invalido! Por favor, insira um UF valido.\n");
			return;
		}

		// Atualiza as informações do quarto e altera o status para ocupado
		strcpy(quartos[andarQuarto - 1][numeroQuarto - 1].nome, novoHospede.nome);
		strcpy(quartos[andarQuarto - 1][numeroQuarto - 1].cpf, novoHospede.cpf);
		strcpy(quartos[andarQuarto - 1][numeroQuarto - 1].telefone, novoHospede.telefone);
		strcpy(quartos[andarQuarto - 1][numeroQuarto - 1].ender.rua, novoHospede.ender.rua);
		strcpy(quartos[andarQuarto - 1][numeroQuarto - 1].ender.numero, novoHospede.ender.numero);
		strcpy(quartos[andarQuarto - 1][numeroQuarto - 1].ender.bairro, novoHospede.ender.bairro);
		strcpy(quartos[andarQuarto - 1][numeroQuarto - 1].ender.cidade, novoHospede.ender.cidade);
		strcpy(quartos[andarQuarto - 1][numeroQuarto - 1].ender.uf, novoHospede.ender.uf);
		quartos[andarQuarto - 1][numeroQuarto - 1].status = 'O'; // Ocupado

		printf("\nCheck-in de %s realizado com sucesso, no quarto %d do andar %d!\n\n", novoHospede.nome, numeroQuarto, andarQuarto);

	} else {
		printf("\nQuarto ja ocupado ou reservado!\n");
	}
	fMostraMat(m, quartos);
}


// REALIZAR CHECK-OUT
void fRealizarCheckOut(int m[20][14], struct stquarto quartos[20][14]) {
	int andarQuarto;
	int numeroQuarto;

	printf("\nDigite o numero do andar para check-out (0 para retornar ao Menu): ");
	if (scanf("%d", &andarQuarto) != 1) {
		clearInputBuffer();
		printf("Entrada invalida! Por favor, insira um numero.\n");
		return;
	}
	// Retorno Menu Principal
	if (andarQuarto == 0) {
		return;
	}
	// Validar se o número do andar é válido
	if (andarQuarto < 1 || andarQuarto > 20) {
		printf("Numero do andar invalido! Por favor, tente novamente.\n");
		return;
	}

	printf("\nDigite o numero do quarto para check-out (0 para retornar ao Menu): ");
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

	if (quartos[andarQuarto - 1][numeroQuarto - 1].status == 'O') {
		char nomeHospede[50]; // Variável para armazenar o nome do hóspede

		// Copia o nome do hóspede para a variável local
		strcpy(nomeHospede, quartos[andarQuarto - 1][numeroQuarto - 1].nome);

		quartos[andarQuarto - 1][numeroQuarto - 1].status = '.';
		printf("\nCheck-out de %s realizado com sucesso, no quarto %d do andar %d!\n\n", nomeHospede, numeroQuarto, andarQuarto);
	} else {
		printf("\nQuarto nao esta ocupado! Por favor, selecione um quarto ocupado para realizar check-out.\n");
	}
	fMostraMat(m, quartos);
}


// REALIZAR RESERVA
void fRealizarReserva(int m[20][14], struct stquarto quartos[20][14]) {
	int andarQuarto;
	int numeroQuarto;
	struct stquarto novoHospede;

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
	// Validar se o número do andar é válido
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

	if (quartos[andarQuarto - 1][numeroQuarto - 1].status == '.') {
		// Preencher dados do hospede
		printf("\nDigite o nome do hospede: ");
		clearInputBuffer();
		fgets(novoHospede.nome, sizeof(novoHospede.nome), stdin);
		strtok(novoHospede.nome, "\n"); // Remover a quebra de linha do final

		// Validar se o nome não está em branco e contém apenas letras e espaços
		int nomeValido = 1;
		for (int i = 0; novoHospede.nome[i] != '\0'; i++) {
			if (!isalpha(novoHospede.nome[i]) && novoHospede.nome[i] != ' ') {
				nomeValido = 0;
				break;
			}
		}
		if (strlen(novoHospede.nome) == 0 || !nomeValido) {
			printf("Nome do hospede invalido! Por favor, insira um nome valido sem numeros.\n");
			return;
		}

		printf("\nDigite o CPF do hospede (apenas numeros): ");
		fgets(novoHospede.cpf, sizeof(novoHospede.cpf), stdin);
		strtok(novoHospede.cpf, "\n"); // Remover a quebra de linha do final

		// Validar se o CPF não está em branco e possui o tamanho correto e contém apenas números
		int cpfValido = 1;
		for (int i = 0; novoHospede.cpf[i] != '\0'; i++) {
			if (!isdigit(novoHospede.cpf[i])) {
				cpfValido = 0;
				break;
			}
		}
		if (strlen(novoHospede.cpf) != 11 || !cpfValido) {
			printf("CPF do hospede invalido! Por favor, insira um CPF valido.\n");
			return;
		}

		printf("\nDigite o telefone do hospede (apenas numeros, com DDD): ");
		clearInputBuffer();
		fgets(novoHospede.telefone, sizeof(novoHospede.telefone), stdin);
		strtok(novoHospede.telefone, "\n"); // Remover a quebra de linha do final

		// Validar se o telefone não está em branco e possui o tamanho correto e contém apenas números
		int telefoneValido = 1;
		int digitCount = 0;
		for (int i = 0; novoHospede.telefone[i] != '\0'; i++) {
			if (isdigit(novoHospede.telefone[i])) {
				digitCount++;
			} else if (novoHospede.telefone[i] != ' ') {
				telefoneValido = 0;
				break;
			}
		}
		if (strlen(novoHospede.telefone) != 11 || digitCount != 11 || !telefoneValido) {
			printf("Telefone do hospede invalido! Por favor, insira um telefone valido.\n");
			return;
		}

		// Digitar o email do hóspede
		printf("\nDigite o email do hospede: ");
		clearInputBuffer();
		fgets(novoHospede.email, sizeof(novoHospede.email), stdin);
		strtok(novoHospede.email, "\n"); // Remover a quebra de linha do final

		// Validar se o email não está em branco e contém o símbolo '@'
		int emailValido = 0;
		for (int i = 0; novoHospede.email[i] != '\0'; i++) {
			if (novoHospede.email[i] == '@') {
				emailValido = 1;
				break;
			}
		}
		if (strlen(novoHospede.email) == 0 || !emailValido) {
			printf("Email do hospede invalido! Por favor, insira um email valido.\n");
		}


		// Atualiza as informações do quarto e altera o status para ocupado
		strcpy(quartos[andarQuarto - 1][numeroQuarto - 1].nome, novoHospede.nome);
		strcpy(quartos[andarQuarto - 1][numeroQuarto - 1].cpf, novoHospede.cpf);
		quartos[andarQuarto - 1][numeroQuarto - 1].status = 'O'; // Ocupado

		printf("\nCheck-in de %s realizado com sucesso, no quarto %d do andar %d!\n\n", novoHospede.nome, numeroQuarto, andarQuarto);

	} else {
		printf("\nQuarto ja ocupado ou reservado!\n");
	}
	fMostraMat(m, quartos);
}

// CANCELAR RESERVA
void fCancelarReserva(int m[20][14], struct stquarto quartos[20][14]) {
	int andarQuarto;
	int numeroQuarto;

	printf("\nDigite o numero do andar para cancelar reserva (0 para retornar ao Menu): ");
	if (scanf("%d", &andarQuarto) != 1) {
		clearInputBuffer();
		printf("Entrada invalida! Por favor, insira um numero.\n");
		return;
	}
	// Retorno Menu Principal
	if (andarQuarto == 0) {
		return;
	}
	// Validar se o número do andar é válido
	if (andarQuarto < 1 || andarQuarto > 20) {
		printf("Numero do andar invalido! Por favor, tente novamente.\n");
		return;
	}

	printf("\nDigite o numero do quarto para cancelar reserva (0 para retornar ao Menu): ");
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

	if (quartos[andarQuarto - 1][numeroQuarto - 1].status == 'R') {
		quartos[andarQuarto - 1][numeroQuarto - 1].status = '.';
		printf("\nCancelamento de reserva de %s realizada com sucesso, no quarto %d do andar %d!\n\n", quartos[andarQuarto - 1][numeroQuarto - 1].nome, numeroQuarto, andarQuarto);
	} else {
		printf("\nQuarto nao esta reservado! Por favor, selecione um quarto reservado para cancelar a reserva.\n");
	}
	fMostraMat(m, quartos);
}


// INFORMACOES DO HOSPEDE
void fInformacoesHospede(int m[20][14], struct stquarto quartos[20][14]) {
	int andarQuarto;
	int numeroQuarto;

	printf("\nDigite o numero do andar para consultar informacoes (0 para retornar ao Menu): ");
	if (scanf("%d", &andarQuarto) != 1) {
		clearInputBuffer();
		printf("Entrada invalida! Por favor, insira um numero.\n");
		return;
	}
	// Retorno Menu Principal
	if (andarQuarto == 0) {
		return;
	}
	// Validar se o número do andar é válido
	if (andarQuarto < 1 || andarQuarto > 20) {
		printf("Numero do andar invalido! Por favor, tente novamente.\n");
		return;
	}

	printf("\nDigite o numero do quarto para consultar informacoes (0 para retornar ao Menu): ");
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

	if (quartos[andarQuarto - 1][numeroQuarto - 1].status == 'O') {
		printf("\nNome: %s\n", quartos[andarQuarto - 1][numeroQuarto - 1].nome);
		printf("CPF: %s\n", quartos[andarQuarto - 1][numeroQuarto - 1].cpf);
		printf("Telefone: %s\n", quartos[andarQuarto - 1][numeroQuarto - 1].telefone);
		printf("Email: %s\n", quartos[andarQuarto - 1][numeroQuarto - 1].email);
		printf("Endereco:\n");
		printf("   Rua: %s\n", quartos[andarQuarto - 1][numeroQuarto - 1].ender.rua);
		printf("   Numero: %s\n", quartos[andarQuarto - 1][numeroQuarto - 1].ender.numero);
		printf("   Bairro: %s\n", quartos[andarQuarto - 1][numeroQuarto - 1].ender.bairro);
		printf("   Cidade: %s\n", quartos[andarQuarto - 1][numeroQuarto - 1].ender.cidade);
		printf("   UF: %s\n", quartos[andarQuarto - 1][numeroQuarto - 1].ender.uf);

		printf("\nInformacoes de %s consultadas com sucesso, no quarto %d do andar %d!\n\n", quartos[andarQuarto - 1][numeroQuarto - 1].nome, numeroQuarto, andarQuarto);
	} else {
		printf("\nQuarto nao esta ocupado! Por favor, selecione um quarto ocupado para consultar informacoes.\n");
	}
}

// LIMPAS BUFFER DE ENTRADA
void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}
