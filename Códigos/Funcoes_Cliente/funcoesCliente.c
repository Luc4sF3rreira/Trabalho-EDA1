#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "funcoesCliente.h"


//Funções para validação
int validarCPF(char *CPF) { 
    if (strlen(CPF) != 11) { 
        printf("\n### CPF deve conter 11 digitos ###\n");
        return 0; 
    }
    for (int i = 0; i < 11; i++) { 
        if (!isdigit(CPF[i])) {
            printf("\n### CPF deve conter apenas numeros ###\n");
            return 0; 
        }
    }
    return 1;
}

int validarNomeCliente(char *nome_cliente) {
    if (strlen(nome_cliente) < 3) { 
        printf("\n### Nome muito curto ###\n");
        return 0; 
    }
    if (strlen(nome_cliente) > 100) { 
        printf("\n### Nome muito longo ###\n");
        return 0; 
    }
    for (int i = 0; i < strlen(nome_cliente); i++) { 
        if (!isalpha(nome_cliente[i]) && nome_cliente[i] != ' ') {
            printf("\n### Nome deve conter apenas letras e espacos ###\n");
            return 0; } 
    }
    return 1;
}

int validarEmail(char *email) {  
    if (strlen(email) < 6) { 
        printf("\n### Email muito curto ###\n");
        return 0; }
    if (strchr(email, '@') == NULL) { 
        printf("\n### Email deve conter o caractere '@' ###\n");
        return 0; }
    else if (strstr(email, "@gmail.com") != NULL) return 1;
    else if (strstr(email, "@hotmail.com") != NULL) return 1;
    else if (strstr(email, "@outlook.com") != NULL) return 1;
    else if (strstr(email, "@yahoo.com") != NULL) return 1;
    else if (strstr(email, "@uol.com.br") != NULL) return 1;
    
    printf("\n### Email deve ser de um provedor conhecido (gmail, hotmail, outlook, yahoo, uol) ###\n");
    return 0; 
}

int validarTelefone(char *telefone) {
    if (telefone[2] != ' ') {
        printf("\n### Telefone deve conter um espaco entre o DDD e o numero ###\n");
        return 0; 
    }
    if (strlen(telefone) != 12) { 
        printf("\n### Telefone deve conter 12 caracteres no formato \"XX XXXXXXXXX\" ###\n");
        return 0; 
    }
    for (int i = 0; i < 12; i++) { 
        if (i == 2) continue; 
        if (!isdigit(telefone[i])) {
            printf("\n### Telefone deve conter apenas numeros ###\n");
            return 0;
        }
    }
    return 1;
}

int validarDataNascimento(char *data_nascimento) { 
    if (strlen(data_nascimento) != 10) {
        printf("\n### Data de nascimento deve estar no formato \"DD/MM/AAAA\" ###\n");
        return 0; 
    }
    if (data_nascimento[2] != '/' || data_nascimento[5] != '/') { 
        printf("\n### Data de nascimento deve estar no formato \"DD/MM/AAAA\" ###\n");
        return 0;
    } 
    for (int i = 0; i < 10; i++) { 
        if (i == 2 || i == 5) continue; 
        if (!isdigit(data_nascimento[i])) {
            printf("\n### Data de nascimento deve conter apenas numeros nas posicoes corretas ###\n");
            return 0;
        }
    }

    char dia_str[3] = {data_nascimento[0], data_nascimento[1], '\0'};
    char mes_str[3] = {data_nascimento[3], data_nascimento[4], '\0'};
    char ano_str[5] = {data_nascimento[6], data_nascimento[7], data_nascimento[8], data_nascimento[9], '\0'};

    
    int dia = atoi(dia_str); 
    int mes = atoi(mes_str);
    int ano = atoi(ano_str);

    if (dia < 1 || dia > 31) {
        printf("\n### Dia invalido na data de nascimento ###\n");
        return 0;
    }
    if (mes < 1 || mes > 12) {
        printf("\n### Mes invalido na data de nascimento ###\n");
        return 0;
    }
    if (ano < 1900 || ano > 2024) {
        printf("\n### Ano invalido na data de nascimento ###\n");
        return 0;
    }
    return 1;
}


//Funções para gerencimento de clientes
Cliente* cadastrarCliente(Cliente *lista_clientes) {
    Cliente *novo = (Cliente*) calloc(1, sizeof(Cliente));

    printf("----- Cadastro de Cliente -----\n\n");
    printf("Digite o CPF (11 digitos): ");
    while(1) {
        scanf(" %11[^\n]", novo->CPF);
        limparBuffer();

        if (validarCPF(novo->CPF)) {
            Cliente *aux;
            for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                if (strcmp(aux->CPF, novo->CPF) == 0) {
                    printf("-> CPF ja cadastrado. Tente outro CPF: ");
                    break;
                }
            }
            if (aux == NULL) break; 

        } else {  
            printf("-> Digite o CPF novamente: ");    
        }
    }
    
    printf("\nDigite o nome: ");
    while(1) {
        scanf(" %99[^\n]", novo->nome_cliente);
        limparBuffer();        

        if (validarNomeCliente(novo->nome_cliente)) break; 
        else printf("-> Digite o nome novamente: ");
    }

    
    printf("\nDigite o email: ");
    while(1) {
        scanf(" %99[^\n]", strlwr(novo->email));
        limparBuffer();        

        if (validarEmail(strlwr(novo->email))) {
            Cliente *aux;
            for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                if (strcmp(aux->email, novo->email) == 0) {
                    printf("-> Email ja cadastrado. Tente outro email: ");
                    break;
                }
            }
            if (aux == NULL) break; 

        } else {  
            printf("-> Digite o email novamente: ");    
        }   
    }

    
    printf("\nDigite o telefone (XX XXXXXXXXX): ");
    while(1) {
        scanf(" %12[^\n]", novo->telefone);
        limparBuffer();        

        if (validarTelefone(novo->telefone)) {
            Cliente *aux;
            for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                if (strcmp(aux->telefone, novo->telefone) == 0) {
                    printf("-> Telefone ja cadastrado. Tente outro telefone: ");
                    break;
                }
            }
            if (aux == NULL) break; 
        } else {  
            printf("-> Digite o telefone novamente: ");    
        }
    }
    
    printf("\nDigite a data de nascimento (DD/MM/AAAA): ");
    while(1) {
        scanf(" %11[^\n]", novo->data_nascimento);
        limparBuffer();        

        if (validarDataNascimento(novo->data_nascimento)) break; 
        else printf("-> Digite a data de nascimento novamente: "); 
    }

    novo->prox = lista_clientes; 
    
    printf("\n<Cliente cadastrado com sucesso!>\n");
    sleep(2);

    return novo; 
}

int listarClientes (Cliente *lista_clientes) {
    if (lista_clientes == NULL) {
        printf("### Nenhum cliente cadastrado. ###\n");
        return 0;
    }
    printf("----- Lista de Clientes Cadastrados -----\n\n");
    while (lista_clientes != NULL) {
        printf("CPF: %s || Nome: %s || Email: %s || Telefone: %s || Data de Nascimento: %s\n",
               lista_clientes->CPF, lista_clientes->nome_cliente, lista_clientes->email, 
               lista_clientes->telefone, lista_clientes->data_nascimento);
               if (lista_clientes->prox != NULL) printf("---------------------------------------------------------------------------------------------------------------------\n");

        lista_clientes = lista_clientes->prox;
    }
    printf("\n");
    return 1;
}

Cliente* buscarCliente(Cliente *lista_clientes, char *CPF) {
    while (lista_clientes != NULL) {
        if (strcmp(lista_clientes->CPF, CPF) == 0) return lista_clientes; 
        lista_clientes = lista_clientes->prox;
    }
    return NULL;
}

void editarCliente (Cliente *lista_clientes) {
    char CPF[12];
    Cliente *cliente = NULL;

    printf("----- Editar cliente -----\n");
    printf("\nInforme o CPF do cliente para editar: ");
    while(cliente == NULL) {
        scanf(" %11[^\n]", CPF);
        limparBuffer();        

        if (validarCPF(CPF)) {
            cliente = buscarCliente(lista_clientes, CPF);
            if (cliente == NULL) {
                printf("-> Cliente nao encontrado. Informe o CPF novamente: ");
            }
        } else {  
            printf("-> Digite o CPF novamente: ");
        } 
    }

    cliente = buscarCliente(lista_clientes, CPF);
    while (cliente == NULL) {
        printf("-> Cliente nao encontrado. Informe o CPF novamente: ");
        scanf(" %11[^\n]", CPF);
        limparBuffer();        

        if (validarCPF(CPF)) {
            cliente = buscarCliente(lista_clientes, CPF);
        } else {
            printf("-> Digite o CPF novamente: ");
        }
    }
    printf("\n<Cliente encontrado: %s>", cliente->nome_cliente);

    int opcao;

    do {
        printf("\n1. CPF\n2. Nome\n3. Email\n4. Telefone\n5. Data de Nascimento\n\n");
        printf("Escolha o campo para editar: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
        case 1:
            printf("\n<CPF atual: %s>\n", cliente->CPF);
            printf("Digite o novo CPF: ");
            char novoCPF[12];

            while (1) {
                scanf(" %11[^\n]", novoCPF);
                limparBuffer();

                if (validarCPF(novoCPF)) {
                    Cliente *aux;
                    int duplicado = 0; 
                    for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                        if (strcmp(aux->CPF, novoCPF) == 0 && aux != cliente) {
                            printf("-> CPF ja cadastrado para outro cliente. Tente outro CPF: ");
                            duplicado = 1;
                            break;
                        }
                    }                    
                    if (!duplicado) {
                        strcpy(cliente->CPF, novoCPF); 
                        printf("\n<CPF alterado com sucesso!>\n\n");
                        sleep(1);
                        break; 
                    }                    
                } else {
                    printf("-> Digite o CPF novamente: ");
                }
            }
            break;

        case 2:
            printf("<Nome atual: %s>\n", cliente->nome_cliente);
            printf("Digite novo nome: ");
            while (1) {
                scanf(" %99[^\n]", cliente->nome_cliente);
                limparBuffer();

                if (validarNomeCliente(cliente->nome_cliente))
                    break; 
                else
                    printf("-> Digite o nome novamente: ");
            }
            printf("\n<Nome alterado com sucesso!>\n");
            sleep(1);
            break;

        case 3:
            printf("\n<Email atual: %s>\n", cliente->email);
            printf("Digite o novo email: ");
            char novoEmail[100];

            while (1) {
                scanf(" %99[^\n]", novoEmail);
                limparBuffer();

                if (validarEmail(novoEmail)) {
                    Cliente *aux;
                    int duplicado = 0; 
                    for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                        if (strcmp(aux->email, novoEmail) == 0 && aux != cliente) {
                            printf("-> Email ja cadastrado para outro cliente. Tente outro email: ");
                            duplicado = 1;
                            break;
                        }
                    }                    
                    if (!duplicado) {
                        strcpy(cliente->email, novoEmail); 
                        printf("\n<Email alterado com sucesso!>\n");
                        sleep(1);
                        break; 
                    }                    
                } else {
                    printf("-> Digite o email novamente: ");
                }
            }
            break;

        case 4:
            printf("<Telefone atual: %s>\n", cliente->telefone);
            printf("Digite novo telefone (XX XXXXXXXXX): ");
            while (1) {
                scanf(" %12[^\n]", cliente->telefone);
                limparBuffer();

                if (validarTelefone(cliente->telefone)) {
                    Cliente *aux;
                    int duplicado = 0; 
                    for (aux = lista_clientes; aux != NULL; aux = aux->prox) {
                        if (strcmp(aux->telefone, cliente->telefone) == 0 && aux != cliente) {
                            printf("-> Telefone ja cadastrado para outro cliente. Tente outro telefone: ");
                            duplicado = 1;
                            break;
                        }
                    }                    
                    if (!duplicado) {
                        strcpy(cliente->telefone, cliente->telefone); 
                        printf("\n<Telefone alterado com sucesso!>\n\n");
                        sleep(1);
                        break; 
                    }                    
                } else {
                    printf("-> Digite o telefone novamente: ");
                }
            }
            break;

        case 5:
            printf("\n<Data de nascimento atual: %s>\n", cliente->data_nascimento);
            printf("Digite nova data de nascimento (DD/MM/AAAA): ");
            while (1) {
                scanf(" %11[^\n]", cliente->data_nascimento);
                limparBuffer();

                if (validarDataNascimento(cliente->data_nascimento))
                    break; 
                else
                    printf("-> Digite a data de nascimento novamente: ");
            }
            printf("\n<Data de nascimento alterada com sucesso!>\n");
            sleep(1);
            break;

        default:
            printf("\n### Opcao invalida, tente novamente. ###\n");
            break;
        }

    } while (opcao < 1 || opcao > 5);
    printf("<Edicao de cliente concluida!>\n");
    sleep(2);
}

Cliente* removerCliente(Cliente *lista_clientes) {
    char CPF[12];
    Cliente *cliente = NULL;

    printf("----- Remover cliente -----\n\n");
    printf("Informe o CPF do cliente a ser removido: ");
    while(cliente == NULL) {
        scanf(" %11[^\n]", CPF);
        limparBuffer();        

        if (validarCPF(CPF)) {
            cliente = buscarCliente(lista_clientes, CPF);
            if (cliente == NULL) {
                printf("-> Cliente nao encontrado. Informe o CPF novamente: ");
            }
        } else {
            printf("-> Digite o CPF novamente: ");
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

    printf("\n<Cliente removido com sucesso!>\n");
    sleep(2);

    return lista_clientes;
}


