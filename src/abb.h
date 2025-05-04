#ifndef ABB_H
#define ABB_H
#include "cadastro.h"
typedef struct EABB {
    Registro* dados;
    struct EABB* esq;
    struct EABB* dir;
} EABB;

typedef struct ABB {
    EABB* raiz;
    int qtde;
} ABB;

void inserir_abb(ABB* arvore, Registro* paciente, int criterio); // Critério: 0=ano, 1=mês...
void em_ordem(ABB* arvore, int criterio); // Mostrar ordenado

#endif // !ABB_H

