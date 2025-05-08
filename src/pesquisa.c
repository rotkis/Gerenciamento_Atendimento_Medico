#include "pesquisa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções auxiliares
static int comparar_registros(Registro* a, Registro* b, int criterio) {
    switch(criterio) {
        case 0: // Ano
            return a->entrada->ano - b->entrada->ano;
        case 1: // Mês
            return a->entrada->mes - b->entrada->mes;
        case 2: // Dia
            return a->entrada->dia - b->entrada->dia;
        case 3: // Idade
            return a->idade - b->idade;
        default:
            return 0;
    }
}

static void destruir_no(EABB* no) {
    if (no == NULL) return;
    destruir_no(no->esq);
    destruir_no(no->dir);
    free(no);
}

// Implementações
ABB* criar_arvore() {
    ABB* nova = malloc(sizeof(ABB));
    nova->raiz = NULL;
    nova->qtde = 0;
    return nova;
}

void destruir_arvore(ABB* arvore) {
    if (arvore == NULL) return;
    destruir_no(arvore->raiz);
    free(arvore);
}

void inserir_abb(ABB* arvore, Registro* paciente, int criterio) {
    EABB* novo = malloc(sizeof(EABB));
    novo->dados = paciente;
    novo->esq = novo->dir = NULL;

    if (arvore->raiz == NULL) {
        arvore->raiz = novo;
        arvore->qtde++;
        return;
    }

    EABB* atual = arvore->raiz;
    EABB* pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (comparar_registros(paciente, atual->dados, criterio) <= 0) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if (comparar_registros(paciente, pai->dados, criterio) <= 0) {
        pai->esq = novo;
    } else {
        pai->dir = novo;
    }
    arvore->qtde++;
}

// Funções de percurso (implementar as outras de forma similar)
static void em_ordem_ano(EABB* no) {
    if (no == NULL) return;
    em_ordem_ano(no->esq);
    printf("Paciente: %s (Ano: %d)\n", no->dados->nome, no->dados->entrada->ano);
    em_ordem_ano(no->dir);
}

void mostrar_por_ano(ABB* arvore) {
    em_ordem_ano(arvore->raiz);
}

// Funções de percurso (implementar as outras de forma similar)
static void em_ordem_mes(EABB* no) {
    if (no == NULL) return;
    em_ordem_mes(no->esq);
    printf("Paciente: %s (Mês: %d)\n", no->dados->nome, no->dados->entrada->mes);
    em_ordem_mes(no->dir);
}

void mostrar_por_mes(ABB* arvore) {
    em_ordem_mes(arvore->raiz);
}

// Funções de percurso (implementar as outras de forma similar)
static void em_ordem_dia(EABB* no) {
    if (no == NULL) return;
    em_ordem_dia(no->esq);
    printf("Paciente: %s (Dia: %d)\n", no->dados->nome, no->dados->entrada->dia);
    em_ordem_dia(no->dir);
}

void mostrar_por_dia(ABB* arvore) {
    em_ordem_dia(arvore->raiz);
}

// Funções de percurso (implementar as outras de forma similar)
static void em_ordem_idade(EABB* no) {
    if (no == NULL) return;
    em_ordem_idade(no->esq);
    printf("Paciente: %s (Idade: %d)\n", no->dados->nome, no->dados->idade);
    em_ordem_idade(no->dir);
}

void mostrar_por_idade(ABB* arvore) {
    em_ordem_idade(arvore->raiz);
}

// Implementar mostrar_por_mes, mostrar_por_dia, mostrar_por_idade de forma similar

Registro* buscar_paciente_abb(ABB* arvore, const char* rg) {
    EABB* atual = arvore->raiz;
    while (atual != NULL) {
        int cmp = strcmp(rg, atual->dados->rg);
        if (cmp == 0) {
            return atual->dados;
        }
        atual = cmp < 0 ? atual->esq : atual->dir;
    }
    return NULL;
}
