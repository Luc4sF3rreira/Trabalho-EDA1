#ifndef MENUS_H
#define MENUS_H

#include "../estruturas.h"

Cliente* menuClientes(Cliente *listaClientes);
Produto* menuProdutos(Produto *listaProdutos, Cliente *listaClientes);
ItemCarrinho* menuModoCompra(Cliente* listaClientes, Produto* listaProdutos);

#endif