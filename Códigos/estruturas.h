#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct itemCarrinho {
    char codigoProduto[6];
    char nomeProduto[50];
    float precoProduto;
    int quantidade;
    struct itemCarrinho *prox; 
} ItemCarrinho;

typedef struct cliente {
    char CPF[12];
    char nome_cliente[100];
    char email[100];
    char telefone[15];
    char data_nascimento[12];
    ItemCarrinho *carrinho; 
    struct cliente *prox; 
} Cliente;

typedef struct produto {
    char codigo[6];
    char nome_produto[100];
    float preco;
    int qtd;
    struct produto *prox; 
} Produto;
    
void limparBuffer(); 

#endif