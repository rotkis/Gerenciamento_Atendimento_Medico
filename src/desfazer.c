#include "desfazer.h"
#include <stdio.h>
#include <stdlib.h>

/* ========================
    Função: criar_pilha
    Proposta: Cria e inicializa uma nova pilha vazia para armazenar operações.
    ======================== */
Pilha* criar_pilha() {
    Pilha* nova = malloc(sizeof(Pilha));
    nova->topo = NULL;
    nova->qtde = 0;
    return nova;
}

/* ========================
    Função: empilhar
    Proposta: Adiciona uma nova operação ao topo da pilha.
    ======================== */
void empilhar(Pilha* pilha, Operacao operacao) {
    EPilha* novo = malloc(sizeof(EPilha));
    novo->dados = operacao;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->qtde++;
}

/* ========================
    Função: desempilhar
    Proposta: Remove e retorna a operação do topo da pilha.
    ======================== */
Operacao desempilhar(Pilha* pilha) {
    if (pilha->topo == NULL) {
        Operacao vazia = {0};
        return vazia;
    }

    EPilha* removido = pilha->topo;
    Operacao operacao = removido->dados;
    pilha->topo = removido->proximo;
    free(removido);
    pilha->qtde--;

    return operacao;
}

/* ========================
    Função: mostrar_operacoes
    Proposta: Exibe todas as operações presentes na pilha, do topo para a base.
    ======================== */
void mostrar_operacoes(Pilha* pilha) {
    printf("\n--- Histórico de Operações (%d) ---\n", pilha->qtde);

    EPilha* atual = pilha->topo;
    int contador = 1;

    while (atual != NULL) {
        printf("%d. ", contador++);
        switch(atual->dados.tipo) {
            case OPERACAO_ENFILEIRAR:
                printf("ENFILEIRAR: %s (RG: %s)\n",
                       atual->dados.paciente->nome,
                       atual->dados.paciente->rg);
                break;
            case OPERACAO_DESENFILEIRAR:
                printf("DESENFILEIRAR: %s (RG: %s)\n",
                       atual->dados.paciente->nome,
                       atual->dados.paciente->rg);
                break;
        }
        atual = atual->proximo;
    }
    printf("-----------------------------\n");
}

/* ========================
    Função: liberar_pilha
    Proposta: Libera toda a memória alocada para a pilha e seus nós.
    ======================== */
void liberar_pilha(Pilha* pilha) {
    while (pilha->topo != NULL) {
        desempilhar(pilha);
    }
    free(pilha);
}