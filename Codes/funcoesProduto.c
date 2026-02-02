#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoesProduto.h"

void limparBuffer() { //Tira o \n que sobrou no buffer após um scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarCodigo(int *codigo, Produto *lista_de_produtos) {
    if (codigo <= 0) {
        printf("Codigo invalido. Deve ser um numero positivo.\n\n");
        return 0;
    }
    for (Produto *p = lista_de_produtos; p != NULL; p = p->prox) {
        if (p->codigo == *codigo) {
            printf("Codigo ja existe. Escolha outro codigo.\n\n");
            return 0;
        }
    }
    for (int i = 0; i < strlen(codigo); i++) { //Verifica se todos os caracteres são números
        if (!isdigit(codigo[i])) {
            printf("Codigo deve conter apenas numeros.\n\n");
            return 0; 
        }
    }
    return 1;
}

int validarNome(char *nome_produto) {
    if (strlen(nome_produto) > 100) { //Verifica se o nome tem no máximo 100 caracteres
        printf("Nome muito longo.\n\n");
        return 0; 
    }
    for (int i = 0; i < strlen(nome_produto); i++) { //Verifica se todos os caracteres são letras
        if (!isalpha(nome_produto[i]) && nome_produto[i] != ' ') {
            printf("Nome deve conter apenas letras e espacos.\n\n");
            return 0; } 
    }
    return 1;
}

Produto* criarProduto(Produto *lista_de_produtos) {
    Produto *novo = (Produto*) calloc(1, sizeof(Produto));

    printf("Codigo: ");
    scanf("%d", &novo->codigo);
    limparBuffer();

    printf("Nome: ");
    scanf(" %99[^\n]", novo->nome_produto);
    limparBuffer();

    printf("Preco: ");
    scanf("%f", &novo->preco);
    limparBuffer();

    printf("Quantidade: ");
    scanf("%d", &novo->qtd);
    limparBuffer();

    novo->prox = lista_de_produtos;   
    lista_de_produtos = novo;         

    return lista_de_produtos;
}

Produto* buscarProduto(Produto *lista_de_produtos, int codigo) {
    while (lista_de_produtos != NULL) {
        if (lista_de_produtos->codigo == codigo) return lista_de_produtos; //Retorna o produto encontrado
        lista_de_produtos = lista_de_produtos->prox;
    }
    return NULL;
} 

void listarProdutos(Produto *lista_de_produtos) {
    Produto *aux = lista_de_produtos;

    if (aux == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Produtos ---\n");
    while (aux != NULL) {
        printf("Codigo: %d || Nome: %s || Preco: %.2f || Quantidade: %d\n",
               aux->codigo, aux->nome_produto, aux->preco, aux->qtd);
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
    scanf(" %99[^\n]", p->nome_produto);
    limparBuffer();

    printf("Novo preco: ");
    scanf("%f", &p->preco);
    limparBuffer();

    printf("Nova quantidade: ");
    scanf("%d", &p->qtd);
    limparBuffer();

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


