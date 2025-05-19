#include "atendimento_prioritario.h"
#include <stdio.h>
#include <stdlib.h>

/* ========================
    Função: inicializar_heap
    Proposta: Inicializa a estrutura do heap prioritário com valores padrão.
    ======================== */
void inicializar_heap(Heap* heap) {
    heap->qtde = 0;
    for (int i = 0; i < CAPACIDADE_MAX; i++) {
        heap->dados[i] = NULL;
    }
}

/* ========================
    Função: indice_pai (static)
    Proposta: Calcula o índice do nó pai de um determinado nó filho no heap.
    ======================== */
static int indice_pai(int filho) {
    return (filho - 1) / 2;
}

/* ========================
    Função: indice_filho_esq (static)
    Proposta: Calcula o índice do filho esquerdo de um determinado nó pai no heap.
    ======================== */
static int indice_filho_esq(int pai) {
    return 2 * pai + 1;
}

/* ========================
    Função: indice_filho_dir (static)
    Proposta: Calcula o índice do filho direito de um determinado nó pai no heap.
    ======================== */
static int indice_filho_dir(int pai) {
    return 2 * pai + 2;
}

/* ========================
    Função: heapify
    Proposta: Mantém a propriedade de heap máximo em um subárvore com raiz no índice fornecido.
    ======================== */
void heapify(Heap* heap, int indice) {
    int maior = indice;
    int esq = indice_filho_esq(indice);
    int dir = indice_filho_dir(indice);

    if (esq < heap->qtde && heap->dados[esq]->idade > heap->dados[maior]->idade) {
        maior = esq;
    }
    if (dir < heap->qtde && heap->dados[dir]->idade > heap->dados[maior]->idade) {
        maior = dir;
    }

    if (maior != indice) {
        Registro* temp = heap->dados[indice];
        heap->dados[indice] = heap->dados[maior];
        heap->dados[maior] = temp;
        heapify(heap, maior);
    }
}

/* ========================
    Função: inserir_heap
    Proposta: Insere um novo paciente no heap prioritário, mantendo a propriedade de heap máximo.
    ======================== */
void inserir_heap(Heap* heap, Registro* paciente) {
    if (heap->qtde >= CAPACIDADE_MAX) {
        printf("Erro: Heap cheio! Capacidade máxima é %d.\n", CAPACIDADE_MAX);
        return;
    }

    heap->dados[heap->qtde] = paciente;
    int indice_atual = heap->qtde;
    heap->qtde++;

    while (indice_atual > 0 &&
           heap->dados[indice_atual]->idade > heap->dados[indice_pai(indice_atual)]->idade) {
        Registro* temp = heap->dados[indice_pai(indice_atual)];
        heap->dados[indice_pai(indice_atual)] = heap->dados[indice_atual];
        heap->dados[indice_atual] = temp;
        indice_atual = indice_pai(indice_atual);
    }
}

/* ========================
    Função: remover_heap
    Proposta: Remove e retorna o paciente com a maior prioridade (maior idade) do heap.
    ======================== */
Registro* remover_heap(Heap* heap) {
    if (heap->qtde == 0) {
        printf("Erro: Heap vazio!\n");
        return NULL;
    }

    Registro* removido = heap->dados[0];
    heap->dados[0] = heap->dados[heap->qtde - 1];
    heap->qtde--;
    heapify(heap, 0);

    return removido;
}

/* ========================
    Função: mostrar_heap
    Proposta: Exibe os pacientes presentes no heap prioritário (para fins de depuração ou visualização).
    ======================== */
void mostrar_heap(const Heap* heap) {
    printf("--- Pacientes no Atendimento Prioritário ---\n");
    for (int i = 0; i < heap->qtde; i++) {
        printf("- %s (Idade: %d)\n", heap->dados[i]->nome, heap->dados[i]->idade);
    }
    printf("--------------------------------------------\n");
}