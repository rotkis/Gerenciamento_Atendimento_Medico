#include "atendimento.h"
#include "cadastro.h"
#include <stdio.h>
#include <stdlib.h>

EFila *cria_Efila(Registro *paciente){
	EFila *efila = malloc(sizeof(EFila));
	efila->proximo = NULL;
	efila->anterior = NULL;
	efila->dados = paciente;

	return efila;
}

Fila *cria_fila(){
	Fila *fila = malloc(sizeof(Fila));
	fila->head = NULL;
	fila->tail = NULL;
	fila->qtde = 0;

	return fila;
}

void enfileirar(Fila *fila, Registro *paciente){
    EFila *nova = cria_Efila(paciente);
    if (fila->qtde == 0) {
      fila->head = nova;
    } else {
      fila->tail->proximo =  nova;
      nova->anterior = fila->tail;
    }
    fila->tail = nova;
    fila->qtde++;
}

Registro* desenfileirar(Fila *fila){
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

void mostrar_fila(Fila *fila){
    EFila *atual = fila->head;
    while (atual != NULL) {
      printf("%s ", atual->dados->nome);
      atual = atual->proximo;
    }
    printf("\n");
}
