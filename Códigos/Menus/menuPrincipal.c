#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../estruturas.h"
#include "../FuncoesCliente/funcoesCliente.h"
#include "../FuncoesProduto/funcoesProduto.h"
#include "menus.h"

int main() {
    int opcao;
    Cliente* clientes = NULL;
    Produto* produtos = NULL;

    do {
        printf("\n==== Sistema de Gestao ====\n");
        printf("1. Gerenciamento de clientes\n");
        printf("2. Gerenciamento de produtos\n");
        printf("3. Modo Compra\n");
        printf("4. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
        case 1:
            clientes = menuClientes(clientes);
            break;

        case 2:
            produtos = menuProdutos(produtos, clientes);
            break;

        case 3:
            printf("\nModo Compra selecionado.\n");
            break;

        case 4:
            printf("\nFinalizando o sistema.\n");
            exit(0);
        }
    } while (opcao != 4);

    return 0;
}
