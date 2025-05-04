#ifndef HEAP_H
#define HEAP_H
#include "cadastro.h"

typedef struct Heap {
    Registro** dados; // Vetor de ponteiros para Registro
    int qtde;
    int capacidade; // Fixo em 20
} Heap;

void inserir_heap(Heap* heap, Registro* paciente);
Registro* remover_heap(Heap* heap); // Remove o paciente mais idoso

#endif // !HEAP_H
