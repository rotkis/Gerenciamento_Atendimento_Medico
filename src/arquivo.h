#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "cadastro.h"

// Função para carregar pacientes de um arquivo para a lista
int carregar_pacientes(const char* dados, Lista* lista);

// Função para salvar pacientes da lista em um arquivo
int salvar_pacientes(const char* dados, Lista* lista);

#endif
