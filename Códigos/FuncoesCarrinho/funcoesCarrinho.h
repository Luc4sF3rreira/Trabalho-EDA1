#ifndef FUNCOES_CARRINHO_H
#define FUNCOES_CARRINHO_H

#include "../estruturas.h"
#include "../FuncoesProduto/funcoesProduto.h"
#include "../FuncoesCliente/funcoesCliente.h"

void limparBuffer(); 

ItemCarrinho* removerDoCarrinho(ItemCarrinho *carrinho, Produto *lista_produtos);
void mostrarCarrinho(ItemCarrinho *carrinho);
ItemCarrinho* adicionarAoCarrinho(ItemCarrinho *carrinho, Produto *lista_produtos);

#endif