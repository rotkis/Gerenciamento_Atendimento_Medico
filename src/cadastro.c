#include "cadastro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================
   Função: criar_lista
   Proposta: Cria uma nova lista vazia
   ======================== */
   void criar_lista(Lista* lista) {
       if (lista == NULL) return;

       lista->inicio = NULL;
       lista->qtde = 0;
   }

/* ========================
   Função: criar_Elista
   Proposta: Cria uma nova lista encadeada vazia
   ======================== */
Elista* criar_Elista(Registro *paciente) {
    Elista* elista = (Elista*)malloc(sizeof(Elista));
    if (elista == NULL) {
        printf("Erro ao criar lista\n");
        exit(1);
    }
    elista->proximo= NULL;
    elista->dados = paciente;
    return elista;
}

/* ========================
   Função: cadastrar_paciente
   Proposta: Cadastra um novo paciente na lista
   ======================== */
void cadastrar_paciente(Lista *lista, Registro *paciente) {
    if (!lista || !paciente) return;

    Elista* novo = criar_Elista(paciente);
    if (!novo) return;
    Elista* anterior = NULL;
    Elista* atual = lista->inicio;
    int cont = 0;
    while (atual != NULL && strcmp(atual->dados->rg, paciente->rg) < 0) {
        cont++;
        anterior = atual;
        atual = atual->proximo;
    }
    if (strcmp(atual->dados->rg, paciente->rg) == 0 && cont > 0) {
        printf("Paciente já cadastrado\n");
        free(novo);
        return;
    }
    if (anterior == NULL){
        lista->inicio = novo;
    } else {
        anterior->proximo = novo;
    }
    novo->proximo = atual;
    lista->qtde++;
}

/* ========================
   Função: remover_paciente
   Proposta: Remove um paciente da lista
   ======================== */
void remover_paciente(Lista *lista, const char *rg) {
    printf("Remoção de Paciente\n");
    if (lista->qtde == 0) {
      return;
    }
    Elista *anterior = NULL;
    Elista *atual = lista->inicio;
    while(atual != NULL && strcmp(atual->dados->rg, rg) != 0){
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
      return;
    }if (anterior == NULL) {
      lista->inicio = atual->proximo;
    } else if (strcmp(atual->dados->rg, rg) == 0){
      anterior->proximo = atual->proximo;
    }
    lista->qtde--;
    free(atual);
}


/* ========================
   Função: buscar_paciente
   Proposta: Busca um paciente na lista
   ======================== */
Registro *buscar_paciente(const Lista *lista, const char *rg) {
    Elista *anterior = NULL;
    Elista *atual = lista->inicio;
    while(atual != NULL && strcmp(atual->dados->rg, rg) != 0){
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Paciente não encontrado\n");
        return NULL;
    }
    return atual->dados;
}


/* ========================
   Função: editar_paciente
   Proposta: Edita um paciente na lista
   ======================== */
void editar_paciente(Lista *lista, const char *rg, Registro *novo) {
    if (lista->qtde == 0) {
      return;
    }
    if (novo == NULL) {
      return;
    }
    Elista *nova = criar_Elista(novo);
    Elista *anterior = NULL;
    Elista *atual = lista->inicio;
    while(atual != NULL && strcmp(atual->dados->rg, rg) != 0){
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
      return;
    }
    if (anterior == NULL) {
      lista->inicio = nova;
    } else {
      anterior->proximo = nova;
    }
    nova->proximo = atual->proximo;
    lista->qtde++;
    free(atual);
}

/* ========================
   Função: mostrar_paciente
   Proposta: Mostra todos os pacientes na lista
   ======================== */
void mostrar_paciente(const Lista *lista) {
    printf("Mostrar Pacientes\n");
    if (lista->qtde == 0) {
      return;
    }
    Elista *atual = lista->inicio;
    while(atual != NULL){
        printf("Nome: %s\n", atual->dados->nome);
        printf("RG: %s\n", atual->dados->rg);
        printf("Idade: %d\n", atual->dados->idade);
        printf("Entrada: %d/%d/%d\n", atual->dados->entrada->dia, atual->dados->entrada->mes, atual->dados->entrada->ano);
        atual = atual->proximo;
    }
}

void liberar_lista(Lista* lista) {
    if (lista == NULL) return;

    Elista* atual = lista->inicio;
    while (atual != NULL) {
        Elista* proximo = atual->proximo;

        // Libera a estrutura Data primeiro
        if (atual->dados != NULL && atual->dados->entrada != NULL) {
            free(atual->dados->entrada);
        }

        // Libera o Registro
        if (atual->dados != NULL) {
            free(atual->dados);
        }

        // Libera o nó da lista
        free(atual);

        atual = proximo;
    }

    // Reseta os valores da lista
    lista->inicio = NULL;
    lista->qtde = 0;
}
