#ifndef MENUS_H
#define MENUS_H

#include "../estruturas.h"

void limparBuffer();
Cliente* menuClientes(Cliente *listaClientes);
Produto* menuProdutos(Produto *listaProdutos, Cliente *listaClientes);


#endif