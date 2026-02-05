#ifndef FUNCOES_CARRINHO_H
#define FUNCOES_CARRINHO_H

#include "../estruturas.h"
#include "../Funcoes_Cliente/funcoesCliente.h"
#include "../Funcoes_Produto/funcoesProduto.h"


ItemCarrinho* adicionarAoCarrinho(ItemCarrinho *carrinho, Produto *lista_produtos);
ItemCarrinho* buscarItem(char *codigo, ItemCarrinho *carrinho);
int mostrarCarrinho(ItemCarrinho *carrinho);
ItemCarrinho* retirarDoCarrinho(ItemCarrinho *carrinho, Produto *lista_produtos);

#endif