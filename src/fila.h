#ifndef FILA_H
#define FILA_H
#include "cadastro.h"

typedef struct EFila {
    Registro* dados;
    struct EFila* proximo;
} EFila;

typedef struct Fila {
    EFila* head;
    EFila* tail;
    int qtde;
} Fila;

void enfileirar(Fila* fila, Registro* paciente);
Registro* desenfileirar(Fila* fila);
#endif // !FILA_H
