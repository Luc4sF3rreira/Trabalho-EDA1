#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../estruturas.h"
#include "../Funcoes_Cliente/funcoesCliente.h"
#include "../Funcoes_Produto/funcoesProduto.h"
#include "subMenus.h"

int main() {
    int opcao;
    Cliente* clientes = NULL;
    Produto* produtos = NULL;

    do {
        system("cls");        
        printf("======= Sistema de Gestao =======\n");
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
            menuModoCompra(clientes, produtos);
            break;

        case 4:
            printf("\nSaindo do sistema.\n");
            exit(0);

        default:
                printf("\nOpcao invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}
