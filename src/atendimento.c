#include "atendimento.h"
#include "cadastro.h"
#include <stdio.h>
#include <stdlib.h>

/* ========================
    Função: cria_Efila
    Proposta: Cria um novo nó para a fila duplamente encadeada.
    ======================== */
EFila *cria_Efila(Registro *paciente) {
    EFila *efila = malloc(sizeof(EFila));
    efila->proximo = NULL;
    efila->anterior = NULL;
    efila->dados = paciente;
    return efila;
}

/* ========================
    Função: cria_fila
    Proposta: Cria e inicializa uma nova fila duplamente encadeada vazia.
    ======================== */
Fila *cria_fila() {
    Fila *fila = malloc(sizeof(Fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->qtde = 0;
    return fila;
}

/* ========================
    Função: enfileirar
    Proposta: Adiciona um paciente ao final da fila duplamente encadeada.
    ======================== */
void enfileirar(Fila *fila, Registro *paciente) {
    EFila *nova = cria_Efila(paciente);
    if (fila->qtde == 0) {
        fila->head = nova;
        fila->tail = nova;
    } else {
        fila->tail->proximo = nova;
        nova->anterior = fila->tail;
        fila->tail = nova;
    }
    fila->qtde++;
}

/* ========================
    Função: desenfileirar
    Proposta: Remove e retorna o paciente do início da fila duplamente encadeada.
    ======================== */
Registro *desenfileirar(Fila *fila) {
    if (fila->qtde == 0) return NULL;
    EFila *liberar = fila->head;
    Registro *valor = liberar->dados;
    if (fila->qtde == 1) {
        fila->head = NULL;
        fila->tail = NULL;
    } else {
        fila->head = fila->head->proximo;
        fila->head->anterior = NULL;
    }
    fila->qtde--;
    free(liberar);
    return valor;
}

/* ========================
    Função: mostrar_fila
    Proposta: Exibe os nomes dos pacientes na fila duplamente encadeada.
    ======================== */
void mostrar_fila(Fila *fila) {
    EFila *atual = fila->head;
    while (atual != NULL) {
        printf("%s ", atual->dados->nome);
        atual = atual->proximo;
    }
    printf("\n");
}