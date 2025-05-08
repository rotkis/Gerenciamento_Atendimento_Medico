#ifndef PESQUISA_H
#define PESQUISA_H
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

// Criação e destruição
ABB* criar_arvore();
void destruir_arvore(ABB* arvore);

// Operações básicas
void inserir_abb(ABB* arvore, Registro* paciente, int criterio);
void remover_abb(ABB* arvore, const char* rg);

// Percursos
void mostrar_por_ano(ABB* arvore);
void mostrar_por_mes(ABB* arvore);
void mostrar_por_dia(ABB* arvore);
void mostrar_por_idade(ABB* arvore);

// Busca
Registro* buscar_paciente_abb(ABB* arvore, const char* rg);

#endif // !ABB_H
