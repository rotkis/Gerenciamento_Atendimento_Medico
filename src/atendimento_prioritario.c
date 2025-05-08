#include "atendimento_prioritario.h"
#include <stdio.h>
#include <stdlib.h>

// Inicializa o heap com valores padrão
void inicializar_heap(Heap* heap) {
    heap->qtde = 0;
    for (int i = 0; i < CAPACIDADE_MAX; i++) {
        heap->dados[i] = NULL;
    }
}

// Funções auxiliares para navegação no heap
static int indice_pai(int filho) {
    return (filho - 1) / 2;
}

static int indice_filho_esq(int pai) {
    return 2 * pai + 1;
}

static int indice_filho_dir(int pai) {
    return 2 * pai + 2;
}

// Mantém a propriedade de heap máximo
void heapify(Heap* heap, int indice) {
    int maior = indice;
    int esq = indice_filho_esq(indice);
    int dir = indice_filho_dir(indice);

    // Compara as idades dos pacientes
    if (esq < heap->qtde && heap->dados[esq]->idade > heap->dados[maior]->idade) {
        maior = esq;
    }
    if (dir < heap->qtde && heap->dados[dir]->idade > heap->dados[maior]->idade) {
        maior = dir;
    }

    // Troca e continua recursivamente
    if (maior != indice) {
        Registro* temp = heap->dados[indice];
        heap->dados[indice] = heap->dados[maior];
        heap->dados[maior] = temp;
        heapify(heap, maior);
    }
}

// Insere um paciente no heap
void inserir_heap(Heap* heap, Registro* paciente) {
    if (heap->qtde >= CAPACIDADE_MAX) {
        printf("Erro: Heap cheio! Capacidade máxima é %d.\n", CAPACIDADE_MAX);
        return;
    }

    // Adiciona no final e sobe no heap
    heap->dados[heap->qtde] = paciente;
    int indice_atual = heap->qtde;
    heap->qtde++;

    // Ajusta para cima enquanto necessário
    while (indice_atual > 0 &&
           heap->dados[indice_atual]->idade > heap->dados[indice_pai(indice_atual)]->idade) {
        // Troca com o pai
        Registro* temp = heap->dados[indice_pai(indice_atual)];
        heap->dados[indice_pai(indice_atual)] = heap->dados[indice_atual];
        heap->dados[indice_atual] = temp;
        indice_atual = indice_pai(indice_atual);
    }
}

// Remove e retorna o paciente mais prioritário (mais idoso)
Registro* remover_heap(Heap* heap) {
    if (heap->qtde == 0) {
        printf("Erro: Heap vazio!\n");
        return NULL;
    }

    Registro* removido = heap->dados[0]; // Paciente mais prioritário
    heap->dados[0] = heap->dados[heap->qtde - 1]; // Substitui pelo último
    heap->qtde--;
    heapify(heap, 0); // Reorganiza o heap

    return removido;
}

// Exibe os pacientes no heap (para debug)
void mostrar_heap(const Heap* heap) {
    printf("--- Pacientes no Atendimento Prioritário ---\n");
    for (int i = 0; i < heap->qtde; i++) {
        printf("- %s (Idade: %d)\n", heap->dados[i]->nome, heap->dados[i]->idade);
    }
    printf("--------------------------------------------\n");
}
