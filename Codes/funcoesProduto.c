#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoesProduto.h"

//Não tenho certeza se coloco o ponteiro assim ou se uso ponteiro de ponteiro
Produto* criarProduto(Produto *lista_de_produtos) {
    Produto *novo = (Produto*) malloc(sizeof(Produto));

    if (novo == NULL) {
        printf("Erro de alocacao!\n");
        return lista_de_produtos;
    }

    printf("Codigo: ");
    scanf("%d", &novo->codigo);

    printf("Nome: ");
    scanf(" %[^\n]", novo->nome);

    printf("Preco: ");
    scanf("%f", &novo->preco);

    printf("Quantidade: ");
    scanf("%d", &novo->qtd);

    novo->prox = lista_de_produtos;   
    lista_de_produtos = novo;         

    return lista_de_produtos;
}

void listarProdutos(Produto *lista_de_produtos) {
    Produto *aux = lista_de_produtos;

    if (aux == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    while (aux != NULL) {
        printf("\nCodigo: %d", aux->codigo);
        printf("\nNome: %s", aux->nome);
        printf("\nPreco: %.2f", aux->preco);
        printf("\nQuantidade: %d\n", aux->qtd);
        aux = aux->prox;
    }
}

void editarProduto(Produto *lista_de_produtos, int codigo) {
    Produto *p = buscarProduto(lista_de_produtos, codigo);

    if (p == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Novo nome: ");
    scanf(" %[^\n]", p->nome);

    printf("Novo preco: ");
    scanf("%f", &p->preco);

    printf("Nova quantidade: ");
    scanf("%d", &p->qtd);

    printf("Produto atualizado!\n");
}

Produto* removerProduto(Produto *lista_de_produtos, int codigo) {
    Produto *atual = lista_de_produtos;
    Produto *anterior = NULL;

    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Produto nao encontrado.\n");
        return lista_de_produtos;
    }

    if (anterior == NULL) {
        lista_de_produtos = atual->prox;  
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Produto removido!\n");

    return lista_de_produtos;
}


