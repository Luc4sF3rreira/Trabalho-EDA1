#ifndef FUNCOES_CLIENTE_H
#define FUNCOES_CLIENTE_H

#include "../estruturas.h"

//Funções para validação
int validarCPF(char *CPF);
int validarNomeCliente(char *nome);
int validarEmail(char *email);
int validarTelefone(char *telefone);
int validarDataNascimento(char *data_nascimento);

//Funções para gerenciamento de clientes
Cliente* cadastrarCliente(Cliente *lista_clientes);
int listarClientes(Cliente *lista_clientes);
Cliente* buscarCliente(Cliente *lista_clientes, char *CPF );
void editarCliente(Cliente *lista_clientes);
Cliente* removerCliente(Cliente *lista_clientes);

#endif