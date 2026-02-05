#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

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

        if (validarCodigo(codigo)) {
            produto = buscarProduto(lista_produtos, codigo);
            if (produto == NULL) {
                printf("Produto nao encontrado. Informe o codigo novamente: ");
            }
            else if (produto->qtd <= 0) {
                printf("Produto esgotado! Tente novamente: ");
                produto = NULL;
            }
        } else {
            printf("Digite o codigo novamente: "); 
        } 
    }   

    printf("Digite a quantidade desejada: ");
    while(1) {
        scanf(" %d", &qtd);
        limparBuffer();

        if (qtd <= 0 || qtd > produto->qtd) {      
            printf("Quantidade invalida.\n");
            return carrinho;
        }
        if (validarQuantidade(qtd)) break;
        else printf("Digite a quantidade novamente: ");
    }

    ItemCarrinho *auxiliar = carrinho;

    while(auxiliar != NULL) {
        if (strcmp(auxiliar->codigoProduto, codigo) == 0){
            auxiliar->quantidade += qtd;
            produto->qtd -= qtd;

            return carrinho;
        }
        auxiliar = auxiliar->prox;
    }

    
    ItemCarrinho *novo = calloc(1, sizeof(ItemCarrinho));

    strcpy(novo->nomeProduto, produto->nome_produto);
    strcpy(novo->codigoProduto, produto->codigo);
    novo->precoProduto = produto->preco;
    novo->quantidade = qtd;
    novo->prox = carrinho;
    carrinho = novo;

    
    produto->qtd -= qtd;

    printf("\n<Produto adicionado ao carrinho!\n");
    sleep(2);

    return novo; 
}

ItemCarrinho* buscarItem(char *codigo, ItemCarrinho *carrinho) {
    while (carrinho != NULL) {
        if (strcmp(carrinho->codigoProduto, codigo) == 0) return carrinho; 
        carrinho = carrinho->prox;
    }
    return NULL;
}

int mostrarCarrinho(ItemCarrinho *carrinho) {
    float total = 0;

    if (carrinho == NULL) {
        printf("\nCarrinho vazio.\n");
        return 0;
    }

    printf("====== CARRINHO ======\n");
    while (carrinho != NULL) {
        float subtotal = carrinho->quantidade * carrinho->precoProduto;
        total += subtotal;

        printf("%s | %s | %d x R$ %.2f = R$ %.2f\n", 
            carrinho->codigoProduto,
            carrinho->nomeProduto,
            carrinho->quantidade,
            carrinho->precoProduto,
            subtotal);

        carrinho = carrinho->prox;
    }

    printf("\n==== TOTAL: R$ %.2f ====\n", total);
    printf("\n\n");

    return 1;
}

ItemCarrinho* retirarDoCarrinho(ItemCarrinho *carrinho, Produto *lista_produtos) {
    if(carrinho == NULL){
        printf("\nNenhum produto no carrinho.\n"); 
        return NULL;
    }

    char codigo[6];
    int qtd;

    ItemCarrinho *produtoCarrinho = NULL;
    
    if (mostrarCarrinho(carrinho)) {
        printf("\nDigite o codigo do produto para retirar do carrinho: ");
    } else {
        printf("\n");
    } 

    while(produtoCarrinho == NULL) {
        scanf(" %5[^\n]", codigo);
        limparBuffer();        

        if (validarCodigo(codigo)) {
            produtoCarrinho = buscarItem(codigo, carrinho);
            if (produtoCarrinho == NULL) {
                printf("Produto nao encontrado no carrinho. Informe o codigo novamente: ");
            }
        } else {
            printf("Digite o codigo novamente: "); 
        } 
    }   

    printf("Digite a quantidade a ser retirada: ");
    while(1) {
        scanf(" %d", &qtd);
        limparBuffer();

        if (qtd <= 0 || qtd > (produtoCarrinho->quantidade)) {      
            printf("Quantidade invalida.\n");
            return carrinho;
        }
        if (validarQuantidade(qtd)) break;
        else printf("Digite a quantidade novamente: ");
    }
    
    ItemCarrinho *atual = carrinho;
    ItemCarrinho *anterior = NULL;
    
    while (atual != NULL && strcmp(atual->codigoProduto, codigo) != 0) {
	    anterior = atual;
        atual = atual->prox;
    }
    
    Produto *produtoEstoque = buscarProduto(lista_produtos, codigo);
    
    if (produtoEstoque != NULL) {
            produtoEstoque->qtd += qtd;
        }
        atual->quantidade -= qtd;

    if (atual->quantidade == 0){
        if (anterior == NULL) {
            carrinho = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
    }

    printf("\n<Remoção concluída>\n");
    sleep(2);
    
    return carrinho;

    
}
