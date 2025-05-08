#ifndef DESFAZER_H
#define DESFAZER_H

#include "cadastro.h"

// Tipos de operações que podem ser desfeitas
typedef enum {
    OPERACAO_ENFILEIRAR,
    OPERACAO_DESENFILEIRAR
} TipoOperacao;

// Estrutura que representa uma operação
typedef struct Operacao {
    TipoOperacao tipo;
    Registro* paciente;  // Paciente envolvido na operação
} Operacao;

// Nó da pilha
typedef struct EPilha {
    Operacao dados;
    struct EPilha* proximo;
} EPilha;

// Estrutura da pilha
typedef struct Pilha {
    EPilha* topo;
    int qtde;
} Pilha;

// Funções
Pilha* criar_pilha();
void empilhar(Pilha* pilha, Operacao operacao);
Operacao desempilhar(Pilha* pilha);
void mostrar_operacoes(Pilha* pilha);
void liberar_pilha(Pilha* pilha);

#endif
