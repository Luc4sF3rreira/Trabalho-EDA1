#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../estruturas.h"
#include "../Funcoes_Produto/funcoesProduto.h"
#include "funcoesCarrinho.h"

ItemCarrinho* adicionarAoCarrinho(ItemCarrinho *carrinho, Produto *lista_produtos) {
    char codigo[6];
    int qtd;
    Produto *produto = NULL;

    if (listarProdutos(lista_produtos)) {
        printf("\nDigite o codigo do produto para adicionar ao carrinho: ");
    } else {
        printf("\n");
    } 

    while(produto == NULL) {
        scanf(" %5[^\n]", codigo);
        limparBuffer();        

        if (validarCodigo(codigo, lista_produtos)) {
            produto = buscarProduto(lista_produtos, codigo);
            if (produto == NULL) {
                printf("Produto nao encontrado. Informe o codigo novamente: ");
            }
        } else {
            printf("Digite o codigo novamente: "); 
    } 
}
    printf("Digite a quantidade desejada: ");
    while(1) {
        scanf(" %d", &qtd);
        limparBuffer();

        if (validarQuantidade(qtd)) break;
        else printf("Digite a quantidade novamente: ");

        if (qtd <= 0 || qtd > produto->qtd) {      
            printf("Quantidade invalida.\n");
            return carrinho;
        }

    }

    //cria novo item do carrinho
    ItemCarrinho *novo = calloc(1, sizeof(ItemCarrinho));

    strcpy(novo->nomeProduto, produto->nome_produto);
    strcpy(novo->codigoProduto, produto->codigo);
    novo->precoProduto = produto->preco;
    novo->quantidade = qtd;
    novo->prox = carrinho;
    carrinho = novo;

    // atualiza estoque
    produto->qtd -= qtd;

    printf("Produto adicionado ao carrinho!\n");

    return novo; //novo vira o início da lista
}

void mostrarCarrinho(ItemCarrinho *carrinho) {
    float total = 0;

    if (carrinho == NULL) {
        printf("\nCarrinho vazio.\n");
        return;
    }

    printf("\n====== CARRINHO ======\n");
    while (carrinho != NULL) {
        float subtotal = carrinho->quantidade * carrinho->precoProduto;
        total += subtotal;

        printf("%s | %d x R$ %.2f = R$ %.2f\n",
               carrinho->nomeProduto,
               carrinho->quantidade,
               carrinho->precoProduto,
               subtotal);

        carrinho = carrinho->prox;
    }

    printf("TOTAL: R$ %.2f\n", total);
}

ItemCarrinho* retirarDoCarrinho(ItemCarrinho *carrinho, Produto *lista_produtos) {
    char codigo[6];
    ItemCarrinho *atual = carrinho;
    ItemCarrinho *anterior = NULL;

    printf("Digite o codigo do produto para remover: ");
    scanf(" %5[^\n]", codigo);
    limparBuffer();

    while (atual != NULL && strcmp(atual->codigoProduto, codigo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Produto nao encontrado no carrinho.\n");
        return carrinho;
    }

    // devolve ao estoque
    Produto *produto = buscarProduto(lista_produtos, codigo);
    if (produto != NULL) {
        produto->qtd += atual->quantidade;
    }

    if (anterior == NULL)
        carrinho = atual->prox;
    else
        anterior->prox = atual->prox;

    free(atual);
    printf("Produto removido do carrinho.\n");

    return carrinho;
}
