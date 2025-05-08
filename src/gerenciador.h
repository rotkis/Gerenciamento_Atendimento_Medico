#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "cadastro.h"
#include "atendimento.h"
#include "atendimento_prioritario.h"


typedef struct Gerenciador {
    Fila fila_comum;          // Fila de atendimento normal
    Heap fila_prioritaria;    // Heap para atendimento prioritário
    Lista *lista_pacientes;    // Lista principal de cadastro
} Gerenciador;

// Inicializa todas as estruturas
void inicializar_gerenciador(Gerenciador* gerenciador);

// Sincroniza as filas (remove de uma ao adicionar na outra)
void mover_para_fila_prioritaria(Gerenciador* gerenciador, const char* rg);
void mover_para_fila_comum(Gerenciador* gerenciador, const char* rg);

#endif
