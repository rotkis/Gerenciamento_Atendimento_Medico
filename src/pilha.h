#ifndef PILHA_H
#define PILHA_H
#include "cadastro.h"
typedef struct Operacao {
    char tipo[20]; // "Enfileirar", "Desenfileirar"
    Registro* paciente;
} Operacao;

typedef struct Pilha {
    Operacao* dados;
    int topo;
    int capacidade;
} Pilha;

void push(Pilha* pilha, Operacao op);
Operacao pop(Pilha* pilha);

#endif // !PILHA_H

