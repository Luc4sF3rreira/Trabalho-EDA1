#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoesCliente.h"


//Funções para validação
int validarCPF(char *CPF) { 
    if (strlen(CPF) != 11) { //Verifica se o CPF tem 11 dígitos
        printf("\nCPF deve conter 11 digitos.\n");
        return 0; 
    }
    for (int i = 0; i < 11; i++) { //Verifica se todos os caracteres são números
        if (!isdigit(CPF[i])) {
            printf("\nCPF deve conter apenas numeros.\n");
            return 0; 
        }
    }
    return 1;
}

int validarNomeCliente(char *nome_cliente) {
    if (strlen(nome_cliente) < 3) { //Verifica se o nome tem pelo menos 3 caracteres
        printf("\nNome muito curto.\n");
        return 0; 
    }
    if (strlen(nome_cliente) > 100) { //Verifica se o nome tem no máximo 100 caracteres
        printf("\nNome muito longo.\n");
        return 0; 
    }
    for (int i = 0; i < strlen(nome_cliente); i++) { //Verifica se todos os caracteres são letras
        if (!isalpha(nome_cliente[i]) && nome_cliente[i] != ' ') {
            printf("\nNome deve conter apenas letras e espacos.\n");
            return 0; } 
    }
    return 1;
}

int validarEmail(char *email) {  //Verifca os provedores mais comuns
    if (strlen(email) < 6) { //Verifica se o email tem pelo menos 6 caracteres
        printf("\nEmail muito curto.\n");
        return 0; }
    if (strchr(email, '@') == NULL) { //Verifica se o email contém o caractere '@'
        printf("\nEmail deve conter o caractere '@'.\n");
        return 0; }
    else if (strstr(email, "@gmail.com") != NULL) return 1;
    else if (strstr(email, "@hotmail.com") != NULL) return 1;
    else if (strstr(email, "@outlook.com") != NULL) return 1;
    else if (strstr(email, "@yahoo.com") != NULL) return 1;
    else if (strstr(email, "@uol.com.br") != NULL) return 1;
    
    printf("\nEmail deve ser de um provedor conhecido (gmail, hotmail, outlook, yahoo, uol).\n");
    return 0; 
}

int validarTelefone(char *telefone) {
    if (telefone[2] != ' ') {
        printf("\nTelefone deve conter um espaco entre o DDD e o numero.\n");
        return 0; //Verifica se o terceiro caractere é um espaço
    }
    if (strlen(telefone) != 12) { //Verifica se o telefone tem 12 caracteres
        printf("\nTelefone deve conter 12 caracteres no formato XX XXXXXXXXX.\n");
        return 0; 
    }
    for (int i = 0; i < 12; i++) { //Verifica se todos os caracteres são números, exceto o espaço
        if (i == 2) continue; //Ao chegar no espaço, pula para o próximo caractere
        if (!isdigit(telefone[i])) {
            printf("\nTelefone deve conter apenas numeros.\n");
            return 0;
        }
    }
    return 1;
}

int validarDataNascimento(char *data_nascimento) { //Verifica se a data de nascimento tem 10 caracteres
    if (strlen(data_nascimento) != 10) {
        printf("\nData de nascimento deve estar no formato DD/MM/AAAA.\n");
        return 0; 
    }
    if (data_nascimento[2] != '/' || data_nascimento[5] != '/') { //Verifica se o terceiro e o quinto caractere são barras
        printf("\nData de nascimento deve estar no formato DD/MM/AAAA.\n");
        return 0;
    } 
    for (int i = 0; i < 10; i++) { //Verifica se todos os caracteres são números, exceto as barras
        if (i == 2 || i == 5) continue; //Ao chegar nas barras, pula para o próximo caractere
        if (!isdigit(data_nascimento[i])) {
            printf("\nData de nascimento deve conter apenas numeros nas posicoes corretas.\n");
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
        printf("\nDia invalido na data de nascimento.\n");
        return 0;
    }
    if (mes < 1 || mes > 12) {
        printf("\nMês invalido na data de nascimento.\n");
        return 0;
    }
    if (ano < 1900 || ano > 2024) {
        printf("\nAno invalido na data de nascimento.\n");
        return 0;
    }
    return 1;
}


//Funções para gerenciamento de clientes
Cliente* cadastrarCliente(Cliente *lista_clientes) {
    Cliente *novo = (Cliente*) calloc(1, sizeof(Cliente));

    //Solicita e valida o CPF do cliente
    printf("\nDigite o CPF (11 digitos): ");
    while(1) {
        scanf(" %11[^\n]", novo->CPF);
        limparBuffer();        

        if (validarCPF(novo->CPF)) {
            Cliente *aux;
            for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                if (strcmp(aux->CPF, novo->CPF) == 0) {
                    printf("CPF ja cadastrado. Tente outro CPF: ");
                    break;
                }
            }
            if (aux == NULL) break; //Sai do loop se o CPF for válido e não estiver cadastrado

        } else {  
            printf("Digite o CPF novamente: ");    
        }
    }

    //Solicita e valida o nome do cliente
    printf("\nDigite o nome: ");
    while(1) {
        scanf(" %99[^\n]", novo->nome_cliente);
        limparBuffer();        

        if (validarNomeCliente(novo->nome_cliente)) break; //Sai do loop se o nome for válido
        else printf("Digite o nome novamente: ");
    }

    //Solicita e valida o email do cliente
    printf("\nDigite o email: ");
    while(1) {
        scanf(" %99[^\n]", strlwr(novo->email));
        limparBuffer();        

        if (validarEmail(strlwr(novo->email))) {
            Cliente *aux;
            for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                if (strcmp(aux->email, novo->email) == 0) {
                    printf("Email ja cadastrado. Tente outro email: ");
                    break;
                }
            }
            if (aux == NULL) break; //Sai do loop se o email for válido e não estiver cadastrado

        } else {  
            printf("Digite o email novamente: ");    
        }   
    }

    //Solicita e valida o telefone do cliente 
    printf("\nDigite o telefone (XX XXXXXXXXX): ");
    while(1) {
        scanf(" %12[^\n]", novo->telefone);
        limparBuffer();        

        if (validarTelefone(novo->telefone)) {
            Cliente *aux;
            for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                if (strcmp(aux->telefone, novo->telefone) == 0) {
                    printf("Telefone ja cadastrado. Tente outro telefone: ");
                    break;
                }
            }
            if (aux == NULL) break; //Sai do loop se o telefone for válido e não estiver cadastrado
        } else {  
            printf("Digite o telefone novamente: ");    
        }
    }

    //Solicita e valida a data de nascimento do cliente
    printf("\nDigite a data de nascimento (DD/MM/AAAA): ");
    while(1) {
        scanf(" %11[^\n]", novo->data_nascimento);
        limparBuffer();        

        if (validarDataNascimento(novo->data_nascimento)) break; //Sai do loop se a data de nascimento for válida
        else printf("Digite a data de nascimento novamente: "); 
    }

    novo->prox = lista_clientes; //O novo aponta para o início da lista
    
    printf("\nCliente cadastrado com sucesso!\n");

    return novo; //Retorna o novo início da lista
}

void listarClientes (Cliente *lista_clientes) {
    if (lista_clientes == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Clientes ---\n");
    while (lista_clientes != NULL) {
        printf("CPF: %s || Nome: %s || Email: %s || Telefone: %s || Data de Nascimento: %s\n",
               lista_clientes->CPF, lista_clientes->nome_cliente, lista_clientes->email, 
               lista_clientes->telefone, lista_clientes->data_nascimento);

        lista_clientes = lista_clientes->prox;
    } 
}

Cliente* buscarCliente(Cliente *lista_clientes, char *CPF) {
    while (lista_clientes != NULL) {
        if (strcmp(lista_clientes->CPF, CPF) == 0) return lista_clientes; //Retorna o cliente encontrado
        lista_clientes = lista_clientes->prox;
    }
    return NULL;
}

void editarCliente (Cliente *lista_clientes) {
    char CPF[12];
    Cliente *cliente = NULL;

    printf("\nInforme o CPF do cliente para editar: ");
    while(cliente == NULL) {
        scanf(" %11[^\n]", CPF);
        limparBuffer();        

        if (validarCPF(CPF)) {
            cliente = buscarCliente(lista_clientes, CPF);
            if (cliente == NULL) {
                printf("Cliente nao encontrado. Informe o CPF novamente: ");
            }
        } else {  
            printf("Digite o CPF novamente: ");
        } 
    }

    cliente = buscarCliente(lista_clientes, CPF);
    while (cliente == NULL) {
        printf("Cliente nao encontrado. Informe o CPF novamente: ");
        scanf(" %11[^\n]", CPF);
        limparBuffer();        

        if (validarCPF(CPF)) {
            cliente = buscarCliente(lista_clientes, CPF);
        } else {
            printf("Digite o CPF novamente: ");
        }
    }
    printf("\nCliente encontrado: %s", cliente->nome_cliente);

    int opcao;

    do {
        printf("\n1. CPF\n2. Nome\n3. Email\n4. Telefone\n5. Data de Nascimento\n");
        printf("Escolha o campo para editar: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
        case 1:
            printf("CPF atual: %s\n", cliente->CPF);
            printf("\nDigite o novo CPF: ");
            char novoCPF[12];

            while (1) {
                scanf(" %11[^\n]", novoCPF);
                limparBuffer();

                if (validarCPF(novoCPF)) {
                    Cliente *aux;
                    int duplicado = 0; 
                    for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                        if (strcmp(aux->CPF, novoCPF) == 0 && aux != cliente) {
                            printf("CPF ja cadastrado para outro cliente. Tente outro CPF: ");
                            duplicado = 1;
                            break;
                        }
                    }                    
                    if (!duplicado) {
                        strcpy(cliente->CPF, novoCPF); 
                        printf("CPF alterado com sucesso!\n\n");
                        break; 
                    }                    
                } else {
                    printf("Digite o CPF novamente: ");
                }
            }
            break;

        case 2:
            printf("Nome atual: %s\n", cliente->nome_cliente);
            printf("Digite novo nome: ");
            while (1) {
                scanf(" %99[^\n]", cliente->nome_cliente);
                limparBuffer();

                if (validarNomeCliente(cliente->nome_cliente))
                    break; // Sai do loop se o nome for válido
                else
                    printf("Digite o nome novamente: ");
            }
            printf("Nome alterado com sucesso!\n");
            break;

        case 3:
            printf("Email atual: %s\n", cliente->email);
            printf("\nDigite o novo email: ");
            char novoEmail[100];

            while (1) {
                scanf(" %99[^\n]", novoEmail);
                limparBuffer();

                if (validarEmail(novoEmail)) {
                    Cliente *aux;
                    int duplicado = 0; 
                    for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                        if (strcmp(aux->email, novoEmail) == 0 && aux != cliente) {
                            printf("Email ja cadastrado para outro cliente. Tente outro email: ");
                            duplicado = 1;
                            break;
                        }
                    }                    
                    if (!duplicado) {
                        strcpy(cliente->email, novoEmail); 
                        printf("Email alterado com sucesso!\n\n");
                        break; 
                    }                    
                } else {
                    printf("Digite o email novamente: ");
                }
            }
            break;

        case 4:
            printf("Telefone atual: %s\n", cliente->telefone);
            printf("\nDigite novo telefone (XX XXXXXXXXX): ");
            while (1) {
                scanf(" %12[^\n]", cliente->telefone);
                limparBuffer();

                if (validarTelefone(cliente->telefone)) {
                    Cliente *aux;
                    int duplicado = 0; 
                    for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                        if (strcmp(aux->telefone, cliente->telefone) == 0 && aux != cliente) {
                            printf("Telefone ja cadastrado para outro cliente. Tente outro telefone: ");
                            duplicado = 1;
                            break;
                        }
                    }                    
                    if (!duplicado) {
                        strcpy(cliente->telefone, cliente->telefone); 
                        printf("Telefone alterado com sucesso!\n\n");
                        break; 
                    }                    
                } else {
                    printf("Digite o telefone novamente: ");
                }
            }
            break;

        case 5:
            printf("Data de nascimento atual: %s\n", cliente->data_nascimento);
            printf("\nDigite nova data de nascimento (DD/MM/AAAA): ");
            while (1) {
                scanf(" %11[^\n]", cliente->data_nascimento);
                limparBuffer();

                if (validarDataNascimento(cliente->data_nascimento))
                    break; // Sai do loop se a data de nascimento for válida
                else
                    printf("Digite a data de nascimento novamente: ");
            }
            printf("Data de nascimento alterada com sucesso!\n");
            break;

        default:
            printf("Opcao invalida, tente novamente.\n");
            break;
        }

    } while (opcao < 1 || opcao > 5);
}

Cliente* removerCliente(Cliente *lista_clientes) {
    char CPF[12];
    Cliente *cliente = NULL;

    printf("\nInforme o CPF do cliente a ser removido: ");
    while(cliente == NULL) {
        scanf(" %11[^\n]", CPF);
        limparBuffer();        

        if (validarCPF(CPF)) {
            cliente = buscarCliente(lista_clientes, CPF);
            if (cliente == NULL) {
                printf("\nCliente nao encontrado. Informe o CPF novamente: ");
            }
        } else {
            printf("\nDigite o CPF novamente: ");
        } 
    }

    Cliente *atual = lista_clientes;
    Cliente *anterior = NULL;

    while (atual != NULL && strcmp(atual->CPF, CPF) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (anterior == NULL) {
        lista_clientes = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    ItemCarrinho *item = atual->carrinho;
    while (item != NULL) {
        ItemCarrinho *temp = item;
        item = item->prox;
        free(temp);
    }
    free(atual);

    printf("Cliente removido com sucesso.\n");
    return lista_clientes;
}


