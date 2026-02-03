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
    char CPF[12];
    char nome_cliente[100];
    char email[100];
    char telefone[15];
    char data_nascimento[12];
    ItemCarrinho *carrinho; //Ponteiro para o carrinho de compras deste cliente
    struct cliente *prox; //Ponteiro para o próximo cliente na lista
} Cliente;

typedef struct produto {
    char codigo[6];
    char nome_produto[100];
    float preco;
    int qtd;
    struct produto *prox; //Ponteiro para o próximo produto na lista
} Produto;
    
void limparBuffer(); //Tira o \n que sobrou no buffer após um scanf

#endif