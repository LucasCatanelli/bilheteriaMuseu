#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

struct Ticket {
    char nome_cliente[60], sobrenome_cliente[60]; 
    int num, exposicoes, tipo;
    float valor;
};

float calculo_preco(int tipo, int exposicoes) {
float preco_base;

    if (tipo == 1) 
	{ 
        preco_base = 10.0;
    } else if (tipo == 2) { 
        preco_base = 5.0;
    } else if (tipo == 3) { 
        preco_base = 0.0;
    } else {
        printf("Tipo de ingresso inválido.\n");
        return -1.0; 
    }
    if (exposicoes == 1) {
        return preco_base + 2.0;
    } else if (exposicoes == 2) {
        return preco_base + 4.0;
    } else if (exposicoes >= 3) { 
        return preco_base + 6.0;
    }

    return preco_base;
}
float venda_ticket(FILE *arquivo) {
    struct Ticket ticket;

    printf("\n====- Venda de Ticket -====\n");

    printf("Nome do visitante: ");
    scanf("%s", ticket.nome_cliente);

    printf("Sobrenome do visitante: ");
    scanf("%s", ticket.sobrenome_cliente); 

    do {
        printf("Tipo de ticket (1-Inteira, 2-Meia, 3-Isencao(PCD E IDOSOS DE +65 ANOS, POSSUEM ISENCAO APENAS PARA O VALOR DO INGRESSO)): ");
        scanf("%d", &ticket.tipo);
    } 
	while (ticket.tipo < 1 || ticket.tipo > 3);

    do {
        printf("Quantas exposicoes deseja assistir (entre 1 e 4)? : ");
        scanf("%d", &ticket.exposicoes);
    } 
	while (ticket.exposicoes < 1 || ticket.exposicoes > 4);

    ticket.valor = calculo_preco(ticket.tipo, ticket.exposicoes);

    if (ticket.valor >= 0.0) {
        srand(time(NULL)); 
        ticket.num = rand(); 

        fprintf(arquivo, "%d,%s %s,%d,%d,%.2f\n", ticket.num, ticket.nome_cliente, ticket.sobrenome_cliente, ticket.tipo, ticket.exposicoes, ticket.valor);

        printf("\nO Ticket foi vendido com sucesso!\n");
    } else {
        printf("\n Tivemos um erro ao calcular o preço do ticket.\n");
    }
}

float mostragem_ticket(FILE *arquivo) {
    struct Ticket ticket;

    printf("\n====- Tickets Vendidos -====\n");

    fseek(arquivo, 0, SEEK_SET);
    printf("Numero do Ticket, Nome e Sobrenome, Tipo de ticket, Exposicoes, Valor\n");
    while (fscanf(arquivo, "%d,%59[^,],%d,%d,%f", &ticket.num, ticket.nome_cliente, &ticket.tipo, &ticket.exposicoes, &ticket.valor) != EOF) {
        printf("%d, %s, %d, %d, %.2f\n", ticket.num, ticket.nome_cliente, ticket.tipo, ticket.exposicoes, ticket.valor);
    }
}

int main() {
    FILE *arquivo;
    arquivo = fopen("vendasdeticket.csv", "a+");
    int opcao;

    if (arquivo == NULL) {
        printf("Tivemos um erro ao abrir o arquivo.\n");
        return 1;
    }

    srand(time(NULL)); 

    do {
        	printf("\n=====- Menu -=====\n");
        printf("1. Vender Ticket\n");
        printf("2. Mostrar Tickets Vendidos\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        	scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                venda_ticket(arquivo);
                break;
            case 2:
                mostragem_ticket(arquivo);
                break;
            case 3:
                printf("\nEstamos saindo do terminal.\n");
                break;
            default:
                printf("\nA opcao que foi escolhida e invalida. Tente novamente!\n");
        }
    } while (opcao != 3);

    fclose(arquivo);

    return 0;
}
