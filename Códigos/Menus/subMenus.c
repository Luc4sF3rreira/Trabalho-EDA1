#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subMenus.h"
#include "../Funcoes_Cliente/funcoesCliente.h"
#include "../Funcoes_Produto/funcoesProduto.h"
#include "../Modo_Compra/funcoesCarrinho.h"

Cliente* menuClientes(Cliente* listaClientes) {
    int subOpcao;

    do {
        if (subOpcao != 2) system("cls");
        printf("\n----- Clientes -----\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar clientes\n");
        printf("3. Editar cliente\n");
        printf("4. Remover cliente\n");
        printf("5. Voltar\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &subOpcao);
        limparBuffer();

        switch (subOpcao) {
            case 1:
                system("cls");
                listaClientes = cadastrarCliente(listaClientes);
                break;

            case 2:
                system("cls");
                if (listarClientes(listaClientes)) printf("\n");
                else printf("\n");
                break;
            
            case 3:
                system("cls");
                editarCliente(listaClientes);
                break;

            case 4:
                system("cls");
                listaClientes = removerCliente(listaClientes);
                break;

            case 5:
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (subOpcao != 5);
    
    return listaClientes;
}

Produto* menuProdutos(Produto* listaProdutos, Cliente* listaClientes) {
    int subOpcao;

    do {
        if (subOpcao != 2) system("cls");
        printf("\n----- Produtos -----\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos\n");
        printf("3. Editar produto\n");
        printf("4. Remover produto\n");
        printf("5. Voltar\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &subOpcao);
        limparBuffer();

        switch (subOpcao) {
            case 1:
                system("cls");
                listaProdutos = cadastrarProduto(listaProdutos);
                break;

            case 2:
                system("cls");
                if (listarProdutos(listaProdutos)) printf("\n");
                else printf("\n");
                break;

            case 3:
                system("cls");
                editarProduto(listaProdutos);
                break;

            case 4:
                system("cls");
                listaProdutos = removerProduto(listaProdutos, listaClientes);
                break;

            case 5:
                break;

            default:
                printf("### Opcao invalida ### \n");
                printf("Tente novamente.\n\n");
                break;
        }
    } while (subOpcao != 5);

    return listaProdutos;
}

void menuModoCompra(Cliente* listaClientes, Produto* listaProdutos) {
    int subOpcao;
    Cliente *clienteAtual = NULL;    
    char cpf[12];

    system("cls");
    printf("\n--- LOGIN MODO COMPRA ---\n");
    printf("Digite o CPF do cliente para acessar o carrinho: ");
    while (1) {
            scanf(" %11[^\n]", cpf);
            limparBuffer();

            if (strcmp(cpf, "0") == 0) return;

            if (validarCPF(cpf)) {                
                clienteAtual = buscarCliente(listaClientes, cpf);

                if (clienteAtual != NULL) {
                    printf("\nBem-vindo(a), %s!\n", clienteAtual->nome_cliente);
                    break; 
                } else {
                    printf("\nErro: CPF nao encontrado. Cadastre-se primeiro.\n");
                    printf("Tente novamente ou digite '0' para voltar: ");
                }

            } else {
                printf("CPF invalido. Digite novamente (apenas numeros): ");
            }
        }

    do {
        if (subOpcao != 2) system("cls");
        printf("\n----- Modo Compra -----\n");
        printf("1. Adicionar produto ao carrinho\n");
        printf("2. Listar produtos no carrinho\n");
        printf("3. Retirar produtos do carrinho\n");
        printf("4. Voltar\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &subOpcao);
        limparBuffer();

        switch(subOpcao) {
            case 1:
                system("cls");
                adicionarAoCarrinho(clienteAtual->carrinho, listaProdutos);
                break;

            case 2:
                system("cls");
                mostrarCarrinho(clienteAtual->carrinho);
                break;

            case 3:
                system("cls");
                retirarDoCarrinho(clienteAtual->carrinho, listaProdutos);
                break;

            case 4:
                break;

            default:
                printf("### Opcao invalida ### \n");
                printf("Tente novamente.\n\n");
                break;
        }
    } while (subOpcao != 4);
}