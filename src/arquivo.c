#include "arquivo.h"
#include "cadastro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================
    Função: carregar_pacientes
    Proposta: Carrega os dados dos pacientes de um arquivo para a lista de pacientes.
    ======================== */
int carregar_pacientes(const char* dados, Lista* lista) {
    FILE* arquivo = fopen(dados, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para leitura.\n", dados);
        return 0; // Retorna 0 em caso de falha
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Registro* paciente = (Registro*)malloc(sizeof(Registro));
        Data* data = (Data*)malloc(sizeof(Data));

        if (!paciente || !data) {
            printf("Erro de alocação de memória.\n");
            fclose(arquivo);
            return 0;
        }

        int campos_lidos = sscanf(linha, "%99[^;];%d;%19[^;];%d;%d;%d",
                                paciente->nome,
                                &paciente->idade,
                                paciente->rg,
                                &data->dia,
                                &data->mes,
                                &data->ano);

        if (campos_lidos != 6) {
            free(paciente);
            free(data);
            continue; // Pula linhas mal formatadas
        }

        paciente->entrada = data;
        cadastrar_paciente(lista, paciente);
    }

    fclose(arquivo);
    return 1; // Retorna 1 em caso de sucesso
}

/* ========================
    Função: salvar_pacientes
    Proposta: Salva os dados da lista de pacientes em um arquivo.
    ======================== */
int salvar_pacientes(const char* dados, Lista* lista) {
    FILE* arquivo = fopen(dados, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", dados);
        return 0;
    }

    Elista* atual = lista->inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%s;%d;%s;%d;%d;%d\n",
                atual->dados->nome,
                atual->dados->idade,
                atual->dados->rg,
                atual->dados->entrada->dia,
                atual->dados->entrada->mes,
                atual->dados->entrada->ano);

        atual = atual->proximo;
    }

    fclose(arquivo);
    return 1;
}