#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H
#include "cadastro.h"

typedef struct EFila {
    Registro* dados;
    struct EFila* proximo;
    struct EFila* anterior;
} EFila;

typedef struct Fila {
    EFila* head;
    EFila* tail;
    int qtde;
} Fila;

EFila *cria_Efila(Registro *paciente);
Fila *cria_fila();
void enfileirar(Fila* fila, Registro* paciente);
Registro* desenfileirar(Fila* fila, Registro* paciente);
void mostrar_fila(Fila* fila);
#endif // !FILA_H
