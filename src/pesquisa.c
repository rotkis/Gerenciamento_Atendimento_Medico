#include "pesquisa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================
    Função: comparar_registros (static)
    Proposta: Compara dois registros de pacientes com base no critério de ordenação fornecido.
    ======================== */
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

/* ========================
    Função: destruir_no (static)
    Proposta: Libera recursivamente a memória de um nó da Árvore de Busca Binária (ABB) e seus filhos.
    ======================== */
static void destruir_no(EABB* no) {
    if (no == NULL) return;
    destruir_no(no->esq);
    destruir_no(no->dir);
    free(no);
}

/* ========================
    Função: criar_arvore
    Proposta: Cria e inicializa uma nova Árvore de Busca Binária (ABB) vazia.
    ======================== */
ABB* criar_arvore() {
    ABB* nova = malloc(sizeof(ABB));
    nova->raiz = NULL;
    nova->qtde = 0;
    return nova;
}

/* ========================
    Função: liberar_nos (static)
    Proposta: Libera recursivamente a memória dos nós da ABB, sem liberar os dados dos pacientes, pois são gerenciados por outra estrutura.
    ======================== */
static void liberar_nos(EABB* no) {
    if (no == NULL) return;
    liberar_nos(no->esq);
    liberar_nos(no->dir);
    free(no);
}

/* ========================
    Função: destruir_arvore
    Proposta: Libera toda a memória alocada para a Árvore de Busca Binária (ABB).
    ======================== */
void destruir_arvore(ABB* arvore) {
    if (arvore == NULL) return;
    liberar_nos(arvore->raiz);
    arvore->raiz = NULL;
    arvore->qtde = 0;
}

/* ========================
    Função: inserir_abb
    Proposta: Insere um novo paciente na Árvore de Busca Binária (ABB) com base no critério de ordenação fornecido.
    ======================== */
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

/* ========================
    Função: em_ordem_ano (static)
    Proposta: Realiza um percurso em ordem na ABB e exibe os pacientes ordenados por ano de registro.
    ======================== */
static void em_ordem_ano(EABB* no) {
    if (no == NULL) return;
    em_ordem_ano(no->esq);
    printf("Paciente: %s (Ano: %d)\n", no->dados->nome, no->dados->entrada->ano);
    em_ordem_ano(no->dir);
}

/* ========================
    Função: mostrar_por_ano
    Proposta: Inicia o percurso em ordem para exibir os pacientes ordenados por ano de registro.
    ======================== */
void mostrar_por_ano(ABB* arvore) {
    em_ordem_ano(arvore->raiz);
}

/* ========================
    Função: em_ordem_mes (static)
    Proposta: Realiza um percurso em ordem na ABB e exibe os pacientes ordenados por mês de registro.
    ======================== */
static void em_ordem_mes(EABB* no) {
    if (no == NULL) return;
    em_ordem_mes(no->esq);
    printf("Paciente: %s (Mês: %d)\n", no->dados->nome, no->dados->entrada->mes);
    em_ordem_mes(no->dir);
}

/* ========================
    Função: mostrar_por_mes
    Proposta: Inicia o percurso em ordem para exibir os pacientes ordenados por mês de registro.
    ======================== */
void mostrar_por_mes(ABB* arvore) {
    em_ordem_mes(arvore->raiz);
}

/* ========================
    Função: em_ordem_dia (static)
    Proposta: Realiza um percurso em ordem na ABB e exibe os pacientes ordenados por dia de registro.
    ======================== */
static void em_ordem_dia(EABB* no) {
    if (no == NULL) return;
    em_ordem_dia(no->esq);
    printf("Paciente: %s (Dia: %d)\n", no->dados->nome, no->dados->entrada->dia);
    em_ordem_dia(no->dir);
}

/* ========================
    Função: mostrar_por_dia
    Proposta: Inicia o percurso em ordem para exibir os pacientes ordenados por dia de registro.
    ======================== */
void mostrar_por_dia(ABB* arvore) {
    em_ordem_dia(arvore->raiz);
}

/* ========================
    Função: em_ordem_idade (static)
    Proposta: Realiza um percurso em ordem na ABB e exibe os pacientes ordenados por idade.
    ======================== */
static void em_ordem_idade(EABB* no) {
    if (no == NULL) return;
    em_ordem_idade(no->esq);
    printf("Paciente: %s (Idade: %d)\n", no->dados->nome, no->dados->idade);
    em_ordem_idade(no->dir);
}

/* ========================
    Função: mostrar_por_idade
    Proposta: Inicia o percurso em ordem para exibir os pacientes ordenados por idade.
    ======================== */
void mostrar_por_idade(ABB* arvore) {
    em_ordem_idade(arvore->raiz);
}

/* ========================
    Função: buscar_paciente_abb
    Proposta: Busca um paciente na Árvore de Busca Binária (ABB) pelo seu RG.
    ======================== */
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