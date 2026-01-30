#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct itemCarrinho {
    int codigoProduto;
    char nomeProduto[50];
    float precoProduto;
    int quantidade;
    struct itemCarrinho *prox; //Ponteiro para o próximo item do carrinho
} ItemCarrinho;

typedef struct cliente {
    int CPF[11];
    char nome[100];
    char email[100];
    char telefone[10];
    char data_nascimento[10];
    ItemCarrinho *carrinho; //Ponteiro para o carrinho de compras deste cliente
    struct cliente *prox; //Ponteiro para o próximo cliente na lista
} Cliente;

typedef struct produto {
    int codigo;
    char nome[50];
    float preco;
    int qtd;
    struct produto *prox; //Ponteiro para o próximo produto na lista
} Produto;

#endif