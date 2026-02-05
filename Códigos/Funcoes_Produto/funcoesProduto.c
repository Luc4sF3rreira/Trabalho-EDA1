#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoesProduto.h"


//Funções para validação 
int validarCodigo(char *codigo) {
    if (strlen(codigo) != 5) {
        printf("\nCodigo de identificacao deve conter exatamente 5 digitos.\n");
        return 0; 
    }
    for (int i = 0; i < 5; i++) {
        if (!isdigit(codigo[i])) {
            printf("\nCodigo deve conter apenas numeros.\n");
            return 0; 
        }
    }
    return 1;
}

int validarNomeProduto(char *nome_produto) {
    if (strlen(nome_produto) > 100) { //Verifica se o nome tem no máximo 100 caracteres
        printf("\nNome muito longo.\n");
        return 0; 
    }
    for (int i = 0; i < strlen(nome_produto); i++) { //Verifica se todos os caracteres são letras
        if (!isalpha(nome_produto[i]) && nome_produto[i] != ' ') {
            printf("\nNome deve conter apenas letras e espacos.\n");
            return 0; } 
    }
    return 1;
}

int validarPreco(float preco) { 
    if (preco <= 0 || preco > 100000.00) {
        printf("\nPreco invalido! O preco deve estar entre 0 e 100.000.\n");
        return 0;
    }    
    return 1;
}

int validarQuantidade(int qtd) { 
    if (qtd <= 0 || qtd > 10000) {
        printf("\nQuantidade invalida! A quantidade deve estar entre 0 e 10.000.\n");
        return 0;
    }
    return 1;
}


//Funções para gerenciamento de produtos
Produto* cadastrarProduto(Produto *lista_de_produtos) {
    Produto *novo = (Produto*) calloc(1, sizeof(Produto));

    //Solicita e valida o codigo do produto
    printf("\nDigite o codigo de identificacao (5 digitos e apenas numeros): ");
    while(1) {
        scanf(" %5[^\n]", novo->codigo);
        limparBuffer();        

        if (validarCodigo(novo->codigo)) {
            Produto *aux;
            for (aux = lista_de_produtos; aux != NULL; aux = aux->prox) {
                if (strcmp(aux->codigo, novo->codigo) == 0) {
                    printf("Codigo de identificacao ja cadastrado. Tente outro codigo: ");
                    break;
                }
            }
            if (aux == NULL) break; //Sai do loop se o codigo for válido e não estiver cadastrado

        } else {  
            printf("Digite o codigo de identificacao novamente: ");    
        }
    }
    
    //Solicita e valida o nome do produto
    printf("\nDigite o nome do produto: ");
    while(1) {
        scanf(" %99[^\n]", novo->nome_produto);
        limparBuffer();        

        if (validarNomeProduto(novo->nome_produto)) {
            Produto *aux;
            for (aux = lista_de_produtos; aux != NULL; aux = aux->prox) {
                if (strcmp(aux->nome_produto, novo->nome_produto) == 0) {
                    printf("Nome do produto ja cadastrado. Tente outro nome: ");
                    break;
                }
            }
            if (aux == NULL) break; //Sai do loop se o nome for válido e não estiver cadastrado
        } else {  
            printf("Digite o nome do produto novamente: ");    
        }
    }

    //Solicita e valida o preco do produto
    printf("\nDigite o preco do produto: R$ ");
    while(1) {
        scanf("%f", &novo->preco);
        limparBuffer();

        if (validarPreco(novo->preco)) break; //Sai do loop se o preco for válido
        else printf("Digite o preco do produto novamente: R$ ");
    }

    //Solicita e valida a quantidade do produto
    printf("\nDigite a quantidade em estoque: ");
    while(1) {
        scanf("%d", &novo->qtd);
        limparBuffer();

        if (validarQuantidade(novo->qtd)) break; //Sai do loop se a quantidade for válida
        else printf("Digite a quantidade do produto novamente: ");
    }

    novo->prox = lista_de_produtos;   
    lista_de_produtos = novo;         

    return lista_de_produtos;
}

Produto* buscarProduto(Produto *lista_de_produtos, char *codigo) {
    while (lista_de_produtos != NULL) {
        if (strcmp(lista_de_produtos->codigo, codigo) == 0) return lista_de_produtos; //Retorna o produto encontrado
        lista_de_produtos = lista_de_produtos->prox;
    }
    return NULL;
} 

int listarProdutos(Produto *lista_de_produtos) {
    Produto *aux = lista_de_produtos;

    if (aux == NULL) {
        printf("\nNenhum produto cadastrado.\n");
        return 0;
    }
    printf("\n--- Lista de Produtos ---\n");
    while (aux != NULL) {
        if (aux->qtd > 0) {
             printf("Codigo: %s || Nome: %s || Preco: R$ %.2f || Quantidade: %d\n",
            aux->codigo, aux->nome_produto, aux->preco, aux->qtd);
        }
        aux = aux->prox;
    }
    return 1;
}

void editarProduto (Produto *lista_de_produtos) {
    char codigo[6];
    Produto *produto = NULL;

    printf("\nInforme o codigo do produto para editar: ");
    while(produto == NULL) {
        scanf(" %5[^\n]", codigo);
        limparBuffer();        

        if (validarCodigo(codigo)) {
            produto = buscarProduto(lista_de_produtos, codigo);
            if (produto == NULL) {
                printf("Produto nao encontrado. Informe o codigo novamente: ");
            }
        } else {
            printf("Digite o codigo novamente: "); 
    } 
}

    produto = buscarProduto(lista_de_produtos, codigo);
    while (produto == NULL) {
        printf("Produto nao encontrado. Informe o codigo novamente: ");
        scanf(" %5[^\n]", codigo);
        limparBuffer();        

        if (validarCodigo(codigo)) {
            produto = buscarProduto(lista_de_produtos, codigo);
        } else {
            printf("Digite o codigo novamente: ");
        }
    }
    printf("\nProduto encontrado: %s", produto->nome_produto);

    int opcao;    
    do {
        printf("\n1. Codigo\n2. Nome do produto\n3. Preco\n4. Quantidade\n");
        printf("Escolha o campo para editar: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
        case 1:
            printf("Codigo atual: %s\n", produto->codigo);
            printf("\nDigite o novo codigo: ");
            char novoCodigo[6];

            while (1) {
                scanf(" %5[^\n]", novoCodigo);
                limparBuffer();

                if (validarCodigo(novoCodigo)) {
                    Produto *aux;
                    int duplicado = 0; 
                    for (aux = lista_de_produtos; aux != NULL; aux = aux->prox) {
                        if (strcmp(aux->codigo, novoCodigo) == 0 && aux != produto) {
                            printf("Codigo ja cadastrado para outro produto. Tente outro codigo: ");
                            duplicado = 1;
                            break;
                        }
                    }                    
                    if (!duplicado) {
                        strcpy(produto->codigo, novoCodigo); 
                        printf("Codigo alterado com sucesso!\n\n");
                        break; 
                    }                    
                } else {
                    printf("Digite o codigo novamente: ");
                }
            }
            break;

        case 2:
            printf("Nome atual do produto: %s\n", produto->nome_produto);
            printf("\nDigite o novo nome do produto: ");
            char novoNome[100];

            while (1) {
                scanf(" %99[^\n]", novoNome);
                limparBuffer();

                if (validarNomeProduto(novoNome)) {
                    Produto *aux;
                    int duplicado = 0; 
                    for (aux = lista_de_produtos; aux != NULL; aux = aux->prox) {
                        if (strcmp(aux->nome_produto, novoNome) == 0 && aux != produto) {
                            printf("Nome ja cadastrado para outro produto. Tente outro nome: ");
                            duplicado = 1;
                            break;
                        }
                    }                    
                    if (!duplicado) {
                        strcpy(produto->nome_produto, novoNome); 
                        printf("Nome alterado com sucesso!\n\n");
                        break; 
                    }                    
                } else {
                    printf("Digite o nome novamente: ");
                }
            }
            break;

        case 3:
            printf("Preco atual: %f\n", produto->preco);
            printf("Digite novo preco: R$ ");
            while (1) {
                scanf("%f", &produto->preco);
                limparBuffer();

                if (validarPreco(produto->preco))
                    break;
                else
                    printf("Digite o preco novamente: R$ ");
            }
            break;

        case 4:
            printf("Quantidade atual: %d\n", produto->qtd);
            printf("Digite nova quantidade: ");
            while (1) {
                scanf("%d", &produto->qtd);
                limparBuffer();

                if (validarQuantidade(produto->qtd))
                    break;
                else
                    printf("Digite a quantidade novamente: ");
            }
            break;

        default:
            printf("Opcao invalida.\n");
            break;
        }

    } while (opcao < 1 || opcao > 4);
}

Produto* removerProduto(Produto *lista_de_produtos, Cliente *lista_clientes) {
    if (lista_de_produtos == NULL) {
        printf("\nNenhum produto cadastrado para remover.\n");
        return NULL;
    }

    char codigo[6];
    Produto *produtoRemover = NULL;

    printf("\nInforme o codigo do produto a ser removido: ");    
    while(produtoRemover == NULL) {
        scanf(" %5[^\n]", codigo);
        limparBuffer();

        if (validarCodigo(codigo)) {
            produtoRemover = buscarProduto(lista_de_produtos, codigo);
            if (produtoRemover == NULL) {
                printf("Produto nao encontrado. Informe o codigo novamente: ");
            }
        } else {
            printf("Digite o codigo novamente: ");
        }
    }

    Cliente *cliente_atual = lista_clientes;
    while (cliente_atual != NULL) {
        ItemCarrinho *carrinhoAtual = cliente_atual->carrinho; //Pega o 1º item do carrinho
        ItemCarrinho *carrinhoAnterior = NULL; 

        while (carrinhoAtual != NULL)        {
            if (strcmp(carrinhoAtual->codigoProduto, codigo) == 0) { //Compara o codigo do carrinho com o codigo do produto a ser removido
                ItemCarrinho *temp = carrinhoAtual; //Guarda quem vai ser removido

                if (carrinhoAnterior == NULL) {
                    cliente_atual->carrinho = carrinhoAtual->prox; //Primeiro item do carrinho
                } else {
                    carrinhoAnterior->prox = carrinhoAtual->prox; //Item do meio ou final do carrinho
                }
                carrinhoAtual = carrinhoAtual->prox; //Avança para o próximo item do carrinho
                free(temp); //Remove o item do carrinho

            } else {
                carrinhoAnterior = carrinhoAtual; //O produto atual vira o anterior
                carrinhoAtual = carrinhoAtual->prox; 
            }
        }
        cliente_atual = cliente_atual->prox; //Vai para o próximo cliente
    }

    Produto *atual = lista_de_produtos;
    Produto *anterior = NULL;

    while (atual != NULL && strcmp(atual->codigo, codigo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (anterior == NULL) {
        lista_de_produtos = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual); 
    printf("Produto removido com sucesso!\n");
    return lista_de_produtos;
}

