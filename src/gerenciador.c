#include "gerenciador.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ========================
    Função: inicializar_gerenciador
    Proposta: Inicializa a estrutura do gerenciador, criando a lista de pacientes, a fila comum e o heap prioritário.
    ======================== */
void inicializar_gerenciador(Gerenciador* gerenciador) {
    criar_lista(&gerenciador->lista_pacientes);
    gerenciador->fila_comum = *cria_fila();
    inicializar_heap(&gerenciador->fila_prioritaria);
}

/* ========================
    Função: mover_para_fila_prioritaria
    Proposta: Move um paciente da fila de atendimento comum para a fila de atendimento prioritário, buscando-o pelo RG.
    ======================== */
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

/* ========================
    Função: mover_para_fila_comum
    Proposta: Move um paciente da fila de atendimento prioritário para a fila de atendimento comum, buscando-o pelo RG.
    ======================== */
void mover_para_fila_comum(Gerenciador* gerenciador, const char* rg) {
    // Busca o paciente no heap prioritário
    for (int i = 0; i < gerenciador->fila_prioritaria.qtde; i++) {
        if (strcmp(gerenciador->fila_prioritaria.dados[i]->rg, rg) == 0) {
            Registro* paciente = gerenciador->fila_prioritaria.dados[i];

            // Remove o paciente do heap prioritário substituindo-o pelo último elemento e reorganizando o heap
            gerenciador->fila_prioritaria.dados[i] = gerenciador->fila_prioritaria.dados[gerenciador->fila_prioritaria.qtde - 1];
            gerenciador->fila_prioritaria.qtde--;
            heapify(&gerenciador->fila_prioritaria, i);

            // Adiciona o paciente à fila comum
            enfileirar(&gerenciador->fila_comum, paciente);
            return;
        }
    }
    printf("Paciente não encontrado na fila prioritária.\n");
}