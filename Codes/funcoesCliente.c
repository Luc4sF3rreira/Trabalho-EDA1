#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoesCliente.h"

void limparBuffer() { //Tira o \n que sobrou no buffer após um scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarCPF(char *CPF) { 
    if (strlen(CPF) != 11) { //Verifica se o CPF tem 11 dígitos
        printf("CPF deve conter 11 digitos.\n\n");
        return 0; }
    for (int i = 0; i < 11; i++) { //Verifica se todos os caracteres são números
        if (!isdigit(CPF[i])) {
            printf("CPF deve conter apenas numeros.\n\n");
            return 0; }
    }
    return 1;
}

int validarNome(char *nome) {
    if (strlen(nome) < 3) { //Verifica se o nome tem pelo menos 3 caracteres
        printf("Nome muito curto.\n\n");
        return 0; }
    for (int i = 0; i < strlen(nome); i++) { //Verifica se todos os caracteres são letras
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            printf("Nome deve conter apenas letras e espacos.\n\n");
            return 0; } 
    }
    return 1;
}

int validarEmail(char *email) {  //Verifca os provedores mais comuns
    if (strlen(email) < 6) { //Verifica se o email tem pelo menos 6 caracteres
        printf("Email muito curto.\n\n");
        return 0; }
    if (strchr(email, '@') == NULL) { //Verifica se o email contém o caractere '@'
        printf("Email deve conter o caractere '@'.\n\n");
        return 0; }
    else if (strstr(email, "@gmail.com") != NULL) return 1;
    else if (strstr(email, "@hotmail.com") != NULL) return 1;
    else if (strstr(email, "@outlook.com") != NULL) return 1;
    else if (strstr(email, "@yahoo.com") != NULL) return 1;
    else if (strstr(email, "@uol.com.br") != NULL) return 1;
    
    printf("Email deve ser de um provedor conhecido (gmail, hotmail, outlook, yahoo, uol).\n");
    return 0; 
}

int validarTelefone(char *telefone) {
    if (telefone[2] != ' ') {
        printf("Telefone deve conter um espaco entre o DDD e o numero.\n\n");
        return 0; //Verifica se o terceiro caractere é um espaço
    }
    if (strlen(telefone) != 12) { //Verifica se o telefone tem 12 caracteres
        printf("Telefone deve conter 12 caracteres no formato XX XXXXXXXXX.\n\n");
        return 0; 
    }
    for (int i = 0; i < 12; i++) { //Verifica se todos os caracteres são números, exceto o espaço
        if (i == 2) continue; //Ao chegar no espaço, pula para o próximo caractere
        if (!isdigit(telefone[i])) {
            printf("Telefone deve conter apenas numeros.\n\n");
            return 0;
        }
    }
    return 1;
}

int validarDataNascimento(char *data_nascimento) { //Verifica se a data de nascimento tem 10 caracteres
    if (strlen(data_nascimento) != 10) {
        printf("Data de nascimento deve estar no formato DD/MM/AAAA.\n\n");
        return 0; 
    }
    if (data_nascimento[2] != '/' || data_nascimento[5] != '/') { //Verifica se o terceiro e o quinto caractere são barras
        printf("Data de nascimento deve estar no formato DD/MM/AAAA.\n\n");
        return 0;
    } 
    for (int i = 0; i < 10; i++) { //Verifica se todos os caracteres são números, exceto as barras
        if (i == 2 || i == 5) continue; //Ao chegar nas barras, pula para o próximo caractere
        if (!isdigit(data_nascimento[i])) {
            printf("Data de nascimento deve conter apenas numeros nas posicoes corretas.\n\n");
            return 0;
        }
    }

    char dia_str[3] = {data_nascimento[0], data_nascimento[1], '\0'};
    char mes_str[3] = {data_nascimento[3], data_nascimento[4], '\0'};
    char ano_str[5] = {data_nascimento[6], data_nascimento[7], data_nascimento[8], data_nascimento[9], '\0'};

    //Usar função atoi para converter strings em inteiros, ex: "25" -> 25
    int dia = atoi(dia_str); 
    int mes = atoi(mes_str);
    int ano = atoi(ano_str);

    if (dia < 1 || dia > 31) {
        printf("Dia invalido na data de nascimento.\n\n");
        return 0;
    }
    if (mes < 1 || mes > 12) {
        printf("Mês invalido na data de nascimento.\n\n");
        return 0;
    }
    if (ano < 1900 || ano > 2024) {
        printf("Ano invalido na data de nascimento.\n\n");
        return 0;
    }
    return 1;
}

void cadastrar_cliente(Cliente **lista_clientes) {
    Cliente *novo = (Cliente*) calloc(1, sizeof(Cliente));

    //Solicita e valida o CPF
    printf("Digite o CPF (11 digitos): ");
    while(1) {
        scanf(" %11[^\n]", novo->CPF);
        limparBuffer();        

        if (validarCPF(novo->CPF)) break; //Sai do loop se o CPF for válido
        else printf("Digite o CPF novamente: "); 
    }

    //Solicita o nome
    printf("Digite o nome: ");
    while(1) {
        scanf(" %99[^\n]", novo->nome);
        limparBuffer();        

        if (validarNome(novo->nome)) break; //Sai do loop se o nome for válido
        else printf("Digite o nome novamente: ");
    }

    //Solicita e valida o email
    printf("Digite o email: ");
    while(1) {
        scanf(" %99[^\n]", strlwr(novo->email));
        limparBuffer();        

        if (validarEmail(strlwr(novo->email))) break; //Sai do loop se o email for válido
        else printf("Digite o email novamente: "); 
    }    

    //Solicita e valida o telefone    
    printf("Digite o telefone (XX XXXXXXXXX): ");
    while(1) {
        scanf(" %12[^\n]", novo->telefone);
        limparBuffer();        

        if (validarTelefone(novo->telefone)) break; //Sai do loop se o telefone for válido
        else printf("Digite o telefone novamente: "); 
    }

    //Solicita e valida a data de nascimento
    printf("Digite a data de nascimento (DD/MM/AAAA): ");
    while(1) {
        scanf(" %11[^\n]", novo->data_nascimento);
        limparBuffer();        

        if (validarDataNascimento(novo->data_nascimento)) break; //Sai do loop se a data de nascimento for válida
        else printf("Digite a data de nascimento novamente: "); 
    }

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
        printf("CPF: %s || Nome: %s || Email: %s || Telefone: %s || Data de Nascimento: %s\n",
               lista_clientes->CPF, lista_clientes->nome, lista_clientes->email, 
               lista_clientes->telefone, lista_clientes->data_nascimento);

        lista_clientes = lista_clientes->prox;
    } 
}

Cliente* buscar_cliente(Cliente *lista_clientes, char *CPF) {
    while (lista_clientes != NULL) {
        if (strcmp(lista_clientes->CPF, CPF) == 0) return lista_clientes; //Retorna o cliente encontrado
        lista_clientes = lista_clientes->prox;
    }
    return NULL;
}

void editar_cliente (Cliente *lista_clientes) {
    char CPF[12];
    printf("Informe o CPF do cliente para editar: ");
    while(1) {
        scanf(" %11[^\n]", CPF);
        limparBuffer();        

        if (validarCPF(CPF)) break; //Sai do loop se o CPF for válido
        else printf("Digite o CPF novamente: "); 
    } 

    Cliente *cliente = buscar_cliente(lista_clientes, CPF);
    while (cliente == NULL) {
        printf("Cliente nao encontrado. Informe o CPF novamente: ");
        scanf(" %11[^\n]", CPF);
        limparBuffer();        

        if (validarCPF(CPF)) {
            cliente = buscar_cliente(lista_clientes, CPF);
        } else {
            printf("Digite o CPF novamente: ");
        }
    }
    printf("\nCliente encontrado: %s\n", cliente->nome);
    printf("Escolha o campo para editar:\n");
    printf("1. CPF\n2. Nome\n3. Email\n4. Telefone\n5. Data de Nascimento\n");

    int opcao;
    scanf("%d", &opcao);
    limparBuffer();
    switch (opcao) {
        case 1:
            printf("CPF atual: %s\n", cliente->CPF);
            printf("Digite o novo CPF: ");
            while(1) {
                scanf(" %11[^\n]", cliente->CPF);
                limparBuffer();        

                if (validarCPF(cliente->CPF)) break; //Sai do loop se o CPF for válido
                else printf("Digite o CPF novamente: "); 
            }
            break;
                    
        case 2:
            printf("Nome atual: %s\n", cliente->nome);
            printf("Digite novo nome: ");
            while(1) {
                scanf(" %99[^\n]", cliente->nome);
                limparBuffer();        

                if (validarNome(cliente->nome)) break; //Sai do loop se o nome for válido
                else printf("Digite o nome novamente: ");
            }
            break;
        
        case 3:
            printf("Email atual: %s\n", cliente->email);
            printf("Digite novo email: ");
            while(1) {
                scanf(" %99[^\n]", cliente->email);
                limparBuffer();        

                if (validarEmail(cliente->email)) break; //Sai do loop se o email for válido
                else printf("Digite o email novamente: ");
            }
            break;

        case 4:
            printf("Telefone atual: %s\n", cliente->telefone);
            printf("Digite novo telefone (XX XXXXXXXXX): ");
            while(1) {
                scanf(" %12[^\n]", cliente->telefone);
                limparBuffer();        

                if (validarTelefone(cliente->telefone)) break; //Sai do loop se o telefone for válido
                else printf("Digite o telefone novamente: ");
            }
            break;

        case 5:
            printf("Data de nascimento atual: %s\n", cliente->data_nascimento);
            printf("Digite nova data de nascimento (DD/MM/AAAA): ");
            while(1) {
                scanf(" %11[^\n]", cliente->data_nascimento);
                limparBuffer();        

                if (validarDataNascimento(cliente->data_nascimento)) break; //Sai do loop se a data de nascimento for válida
                else printf("Digite a data de nascimento novamente: ");
            }
            break;
    }
}

void remover_cliente(Cliente **lista_clientes) {
    char CPF[12];
    printf("Informe o CPF do cliente a ser removido: ");
    while(1) {
        scanf(" %11[^\n]", CPF);
        limparBuffer();        

        if (validarCPF(CPF)) break; //Sai do loop se o CPF for válido
        else printf("Digite o CPF novamente: ");
    } 

    Cliente *atual = *lista_clientes;
    Cliente *anterior = NULL;

    while (atual != NULL && strcmp(atual->CPF, CPF) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    while (atual == NULL) {
        printf("Cliente nao encontrado. Informe o CPF novamente: ");
        scanf(" %11[^\n]", CPF);
        limparBuffer();        

        if (validarCPF(CPF)) {
            atual = buscar_cliente(*lista_clientes, CPF);
        } else {
            printf("Digite o CPF novamente: ");
        }
    }

    if (atual == NULL) {
        printf("Cliente não encontrado.\n");
        return;
    }
    if (anterior == NULL) {
        *lista_clientes = atual->prox; //Remover o primeiro cliente da lista
    } else {
        anterior->prox = atual->prox; //Remover cliente do meio ou fim da lista
    }

    ItemCarrinho *item = atual->carrinho;
    while (item != NULL) { //Libera a memória do carrinho de compras do cliente
        ItemCarrinho *temp = item;
        item = item->prox;
        free(temp);
    }
    free(atual);
    printf("Cliente removido com sucesso.\n");
}


