#ifndef FUNCOES_PRODUTO_H
#define FUNCOES_PRODUTO_H

#include "../estruturas.h"

//Funções para validação
int validarCodigo(char *codigo, Produto *lista_de_produtos);
int validarNomeProduto(char *nome_produto);
int validarPreco(float preco);
int validarQuantidade(int qtd);

//Funções para gerenciamento de produtos
Produto* cadastrarProduto(Produto *lista_de_produtos);
Produto* buscarProduto(Produto *lista_de_produtos, char *codigo);
void listarProdutos(Produto *lista_de_produtos);
void editarProduto(Produto *lista_de_produtos);
Produto* removerProduto(Produto *lista_de_produtos, Cliente *lista_clientes);

#endif