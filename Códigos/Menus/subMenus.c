#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h"
#include "../FuncoesCliente/funcoesCliente.h"
#include "../FuncoesProduto/funcoesProduto.h"

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


