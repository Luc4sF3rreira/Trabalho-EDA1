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
        printf("\n==== Clientes ====\n");
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
                listaClientes = cadastrarCliente(listaClientes);
                break;

            case 2:
                listarClientes(listaClientes);
                break;
            
            case 3:
                editarCliente(listaClientes);
                break;

            case 4:
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
        printf("\n==== Produtos ====\n");
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
                listaProdutos = cadastrarProduto(listaProdutos);
                break;

            case 2:
                listarProdutos(listaProdutos);
                break;

            case 3:
                editarProduto(listaProdutos);
                break;

            case 4:
                listaProdutos = removerProduto(listaProdutos, listaClientes);
                break;

            case 5:
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (subOpcao != 5);

    return listaProdutos;
}

ItemCarrinho* menuModoCompra(Cliente* listaClientes, Produto* listaProdutos) {
    int subOpcao;
    ItemCarrinho* carrinhoAtual = NULL;
    
    char cpf[12];
    printf("Digite o CPF do cliente para acessar o carrinho: ");
    while(1) {
        scanf(" %11[^\n]", cpf);
        limparBuffer();        

        if (validarCPF(cpf)) {
            Cliente *aux;
            for (aux = listaClientes; aux != NULL; aux = aux->prox) {
                if (strcmp(aux->CPF, cpf) == 0) {
                    printf("CPF ja cadastrado. Tente outro CPF: ");
                    break;
                }
            }
            if (aux == NULL) break; 

        } else {  
            printf("Digite o CPF novamente: ");    
        }
    }
    do {
        printf("\n==== Modo Compra ====\n");
        printf("1. Adicionar produto ao carrinho\n");
        printf("2. Listar produtos no carrinho\n");
        printf("3. Retirar produtos do carrinho\n");
        printf("4. Voltar\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &subOpcao);
        limparBuffer();

        switch(subOpcao) {
            case 1:
                carrinhoAtual = adicionarAoCarrinho(carrinhoAtual, listaProdutos);
                break;

            case 2:
                mostrarCarrinho(carrinhoAtual);
                break;

            case 3:
                carrinhoAtual = retirarDoCarrinho(carrinhoAtual, listaProdutos);
                break;

            case 4:
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (subOpcao != 4);
    
    return carrinhoAtual;
}