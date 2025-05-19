#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H
#include "cadastro.h"

// Define a estrutura do nó da fila (EFila).
typedef struct EFila {
    Registro* dados;      
    struct EFila* proximo; 
    struct EFila* anterior;
} EFila;

// Define a estrutura da fila (Fila).
typedef struct Fila {
    EFila* head; 
    EFila* tail; 
    int qtde;    
} Fila;

// Declara a função para criar um nó da fila.
EFila *cria_Efila(Registro *paciente);
Fila *cria_fila();
// Declara a função para adicionar um paciente à fila.
void enfileirar(Fila* fila, Registro* paciente);
// Declara a função para remover um paciente da fila.
Registro* desenfileirar(Fila* fila);
void mostrar_fila(Fila* fila);

#endif // !FILA_H