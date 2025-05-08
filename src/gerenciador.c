#include "gerenciador.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void inicializar_gerenciador(Gerenciador* gerenciador) {
    criar_lista(&gerenciador->lista_pacientes);
    gerenciador->fila_comum = *cria_fila();
    inicializar_heap(&gerenciador->fila_prioritaria);
}

// Move um paciente da fila comum para a prioritária
void mover_para_fila_prioritaria(Gerenciador* gerenciador, const char* rg) {
    // Busca o paciente na fila comum
    EFila* atual = gerenciador->fila_comum.head;
    EFila* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados->rg, rg) == 0) {
            // Remove da fila comum
            if (anterior == NULL) {
                gerenciador->fila_comum.head = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            if (atual->proximo != NULL) {
                atual->proximo->anterior = anterior;
            }
            gerenciador->fila_comum.qtde--;

            // Adiciona ao heap prioritário
            inserir_heap(&gerenciador->fila_prioritaria, atual->dados);
            free(atual); // Libera o nó da fila comum
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Paciente com RG %s não encontrado na fila comum.\n", rg);
}

// Move um paciente da fila prioritária para a comum
void mover_para_fila_comum(Gerenciador* gerenciador, const char* rg) {
    // Busca o paciente no heap
        for (int i = 0; i < gerenciador->fila_prioritaria.qtde; i++) {
            if (strcmp(gerenciador->fila_prioritaria.dados[i]->rg, rg) == 0) {
                Registro* paciente = gerenciador->fila_prioritaria.dados[i];

                // Substitui o paciente pelo último elemento
                gerenciador->fila_prioritaria.dados[i] = gerenciador->fila_prioritaria.dados[gerenciador->fila_prioritaria.qtde - 1];
                gerenciador->fila_prioritaria.qtde--;

                // Reorganiza o heap a partir do nó alterado (usando peneirar)
                heapify(&gerenciador->fila_prioritaria, i);

                // Adiciona à fila comum
                enfileirar(&gerenciador->fila_comum, paciente);
                return;
            }
        }
        printf("Paciente não encontrado na fila prioritária.\n");
}
