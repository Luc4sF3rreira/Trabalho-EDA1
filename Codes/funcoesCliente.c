#include <stdio.h>
#include <stdlib.h>
#include "funcoesCliente.h"

void limparBuffer() { //Tira o \n que sobrou
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrar_cliente(Cliente **lista_clientes) {
    Cliente *novo = (Cliente*) calloc(1, sizeof(Cliente));

    printf("Digite o CPF (11 dígitos): ");
    while (1) {
        if (scanf("%10d", novo->CPF) != 1) {
            printf("CPF inválido. Digite novamente: ");
            limparBuffer();
        }
        else if (buscar_cliente(*lista_clientes, novo->CPF) != NULL) {
            printf("CPF já cadastrado.\n");
            free(novo);
            return;
        }
        else {
            break;
        }
    }
    printf("Digite o nome: ");
    scanf(" %99[^\n]", novo->nome); 
    limparBuffer(); 

    printf("Digite o email: ");
    scanf(" %99[^\n]", novo->email);
    limparBuffer();
    
    printf("Digite o telefone ((XX)9 XXXX-XXXX): ");
    scanf(" 9 %9[^\n]", novo->telefone);
    limparBuffer();

    printf("Digite a data de nascimento (DD/MM/AAAA): ");
    scanf(" %9[^\n]", novo->data_nascimento);
    limparBuffer();

    novo->prox = *lista_clientes; //O novo aponta para o início da lista
    *lista_clientes = novo; //A lista agora começa com o novo cliente
    
    printf("Cliente cadastrado com sucesso!\n");
}

void listar_clientes (Cliente *lista_clientes) {
    if (lista_clientes == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Clientes ---\n");
    while (lista_clientes != NULL) {
        printf("CPF: %d | Nome: %s | Email: %s | Telefone: %s | Data de Nascimento: %s\n",
               lista_clientes->CPF, lista_clientes->nome, lista_clientes->email, 
               lista_clientes->telefone, lista_clientes->data_nascimento);

        lista_clientes = lista_clientes->prox;
    } 
}

Cliente* buscar_cliente(Cliente *lista_clientes, int *CPF) {
    int CPF[11];
    printf("Informe o CPF do cliente a ser encontrado: ");
    scanf("%10d", CPF);
    limparBuffer();

    while (lista_clientes != NULL) {
        if (memcmp(lista_clientes->CPF, CPF, 11 * sizeof(int)) == 0) return lista_clientes; //Retorna o cliente encontrado
        lista_clientes = lista_clientes->prox;
    }
    return NULL;
}

void editar_cliente (Cliente *lista_clientes) {
    int CPF[11];
    printf("Informe o CPF do cliente para editar: ");
    scanf("%10d", CPF);
    limparBuffer();

    Cliente *cliente = buscar_cliente(lista_clientes, CPF);
    if (cliente == NULL) {
        printf("Cliente não encontrado.\n");
        return;
    }
    printf("Escolha o campo para editar:\n");
    printf("1. CPF\n2. Nome\n3. Email\n4. Telefone\n5. Data de Nascimento\n");
    int opcao;
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao) {
        case 1:
            printf("CPF atual: %d\n", cliente->CPF);
            printf("Digite o novo CPF: ");
            scanf(" %10[^\n]", cliente->CPF);
            limparBuffer();
            break;
        
        case 2:
            printf("Nome atual: %s\n", cliente->nome);
            printf("Digite novo nome: ");
            scanf(" %99[^\n]", cliente->nome);
            limparBuffer();
            break;
        
        case 3:
            printf("Email atual: %s\n", cliente->email);
            printf("Digite novo email: ");
            scanf(" %99[^\n]", cliente->email);
            limparBuffer();
            break;

        case 4:
            printf("Email atual: %s\n", cliente->email);
            printf("Digite novo email: ");
            scanf(" %99[^\n]", cliente->email);
            limparBuffer();
            break;

        case 5:
            printf("Email atual: %s\n", cliente->email);
            printf("Digite novo email: ");
            scanf(" %99[^\n]", cliente->email);
            limparBuffer();
            break;
    }

}