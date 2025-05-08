#ifndef ATENDIMENTO_PRIORITARIO_H
#define ATENDIMENTO_PRIORITARIO_H

#include "cadastro.h" // Inclua apenas o necessário

#define CAPACIDADE_MAX 20 // Capacidade fixa conforme especificado

typedef struct Heap {
    Registro* dados[CAPACIDADE_MAX]; // Vetor de ponteiros para Registro
    int qtde; // Quantidade atual de pacientes no heap
} Heap;

// Declarações de funções
void inicializar_heap(Heap* heap);
void inserir_heap(Heap* heap, Registro* paciente);
Registro* remover_heap(Heap* heap);
void mostrar_heap(const Heap* heap);
void heapify(Heap* heap, int indice);

#endif
