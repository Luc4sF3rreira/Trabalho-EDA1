#ifndef FUNCOES_CLIENTE_H
#define FUNCOES_CLIENTE_H

#include "estruturas.h"

void limparBuffer();
int validarCPF(char *CPF);
int validarNome(char *nome);
int validarEmail(char *email);
int validarTelefone(char *telefone);
int validarDataNascimento(char *data_nascimento);

void cadastrar_cliente(Cliente **lista_clientes);
void listar_clientes(Cliente *lista_clientes);
Cliente* buscar_cliente(Cliente *lista_clientes, char *CPF );
void editar_cliente(Cliente *lista_clientes);
void remover_cliente(Cliente **lista_clientes);

#endif