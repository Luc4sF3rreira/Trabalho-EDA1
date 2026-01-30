#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesCliente.h"

int main() { //Essa main é apenas para testes rápidos das funções implementadas.
    Cliente *lista_clientes = NULL;

    cadastrar_cliente(&lista_clientes);
    listar_clientes(lista_clientes);
    editar_cliente(lista_clientes);
    listar_clientes(lista_clientes);
    remover_cliente(&lista_clientes);
} 
