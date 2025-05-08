#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"
#include "atendimento.h"
#include "atendimento_prioritario.h"
#include "pesquisa.h"
#include "desfazer.h"
#include "arquivo.h"

// Definição das opções do menu
#define OPCAO_CADASTRAR 1
#define OPCAO_ATENDIMENTO 2
#define OPCAO_ATENDIMENTO_PRIORITARIO 3
#define OPCAO_PESQUISA 4
#define OPCAO_DESFAZER 5
#define OPCAO_CARREGAR 6
#define OPCAO_SALVAR 7
#define OPCAO_SOBRE 8
#define OPCAO_SAIR 9

// Protótipos de funções auxiliares
void menu_principal();
void menu_cadastrar(Lista* lista);
void menu_atendimento(Fila* fila, Lista* lista, Pilha* pilha);
void menu_atendimento_prioritario(Heap* heap, Lista* lista);
void menu_pesquisa(ABB* arvore, Lista* lista);
void menu_desfazer(Fila* fila, Pilha* pilha);
void menu_sobre();

int main() {
    // Inicialização das estruturas
    Lista lista_pacientes;
    criar_lista(&lista_pacientes);

    Fila fila_atendimento;
    fila_atendimento = *cria_fila();

    Heap heap_prioritario;
    inicializar_heap(&heap_prioritario);

    ABB arvore_pesquisa;
    arvore_pesquisa.raiz = NULL;
    arvore_pesquisa.qtde = 0;

    Pilha* pilha_operacoes = criar_pilha();

    int opcao;
    do {
        menu_principal();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case OPCAO_CADASTRAR:
                menu_cadastrar(&lista_pacientes);
                break;

            case OPCAO_ATENDIMENTO:
                menu_atendimento(&fila_atendimento, &lista_pacientes, pilha_operacoes);
                break;

            case OPCAO_ATENDIMENTO_PRIORITARIO:
                menu_atendimento_prioritario(&heap_prioritario, &lista_pacientes);
                break;

            case OPCAO_PESQUISA:
                menu_pesquisa(&arvore_pesquisa, &lista_pacientes);
                break;

            case OPCAO_DESFAZER:
                menu_desfazer(&fila_atendimento, pilha_operacoes);
                break;

            case OPCAO_CARREGAR: {
                char nome_arquivo[100];
                printf("Digite o nome do arquivo para carregar: ");
                scanf("%99s", nome_arquivo);
                if (carregar_pacientes(nome_arquivo, &lista_pacientes)) {
                    printf("Pacientes carregados com sucesso!\n");
                }
                break;
            }

            case OPCAO_SALVAR: {
                char nome_arquivo[100];
                printf("Digite o nome do arquivo para salvar: ");
                scanf("%99s", nome_arquivo);
                if (salvar_pacientes(nome_arquivo, &lista_pacientes)) {
                    printf("Pacientes salvos com sucesso!\n");
                }
                break;
            }

            case OPCAO_SOBRE:
                menu_sobre();
                break;

            case OPCAO_SAIR:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        printf("\nPressione Enter para continuar...");
        while (getchar() != '\n'); // Limpa o buffer
        getchar(); // Espera Enter

    } while (opcao != OPCAO_SAIR);

    // Liberação de memória
    liberar_lista(&lista_pacientes);
    // Adicionar liberação para outras estruturas...
    liberar_pilha(pilha_operacoes);

    return 0;
}

void menu_principal() {
    system("clear || cls"); // Limpa a tela (Linux/Windows)
    printf("=== GERENCIADOR DE ATENDIMENTO MÉDICO ===\n");
    printf("1. Cadastrar paciente\n");
    printf("2. Atendimento comum\n");
    printf("3. Atendimento prioritário\n");
    printf("4. Pesquisar pacientes\n");
    printf("5. Desfazer operação\n");
    printf("6. Carregar pacientes\n");
    printf("7. Salvar pacientes\n");
    printf("8. Sobre\n");
    printf("9. Sair\n");
}

void menu_cadastrar(Lista* lista) {
    system("clear || cls");
    printf("=== CADASTRO DE PACIENTES ===\n");

    Registro paciente;
    Data data;
    char buffer[100];

    printf("Nome: ");
    scanf(" %99[^\n]", paciente.nome);

    printf("Idade: ");
    scanf("%d", &paciente.idade);

    printf("RG: ");
    scanf(" %19s", paciente.rg);

    printf("Data de entrada (dia mês ano): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

    paciente.entrada = &data;
    cadastrar_paciente(lista, &paciente);

    printf("\nPaciente cadastrado com sucesso!\n");
}

void menu_atendimento(Fila* fila, Lista* lista, Pilha* pilha) {
    int opcao;
    do {
        system("clear || cls");
        printf("=== ATENDIMENTO COMUM ===\n");
        printf("1. Enfileirar paciente\n");
        printf("2. Desenfileirar paciente\n");
        printf("3. Mostrar fila\n");
        printf("4. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                char rg[20];
                printf("Digite o RG do paciente: ");
                scanf("%19s", rg);

                Registro* paciente = buscar_paciente(lista, rg);
                if (paciente) {
                    enfileirar(fila, paciente);

                    // Registra a operação na pilha de desfazer
                    Operacao op = {OPERACAO_ENFILEIRAR, paciente};
                    empilhar(pilha, op);

                    printf("Paciente enfileirado com sucesso!\n");
                } else {
                    printf("Paciente não encontrado!\n");
                }
                break;
            }

            case 2: {
                Registro* paciente = desenfileirar(fila);
                if (paciente) {
                    printf("Atendendo: %s\n", paciente->nome);

                    // Registra a operação na pilha de desfazer
                    Operacao op = {OPERACAO_DESENFILEIRAR, paciente};
                    empilhar(pilha, op);
                } else {
                    printf("Fila vazia!\n");
                }
                break;
            }

            case 3:
                printf("\n=== FILA DE ATENDIMENTO ===\n");
                mostrar_fila(fila);
                break;
        }

        if (opcao != 4) {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n');
            getchar();
        }
    } while (opcao != 4);
}

void menu_atendimento_prioritario(Heap* heap, Lista* lista) {
    int opcao;
    do {
        system("clear || cls");
        printf("=== ATENDIMENTO PRIORITÁRIO ===\n");
        printf("1. Adicionar paciente prioritário\n");
        printf("2. Atender próximo paciente\n");
        printf("3. Mostrar fila prioritária\n");
        printf("4. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                char rg[20];
                printf("Digite o RG do paciente: ");
                scanf("%19s", rg);

                Registro* paciente = buscar_paciente(lista, rg);
                if (paciente) {
                    inserir_heap(heap, paciente);
                    printf("Paciente adicionado à fila prioritária!\n");
                } else {
                    printf("Paciente não encontrado!\n");
                }
                break;
            }

            case 2: {
                Registro* paciente = remover_heap(heap);
                if (paciente) {
                    printf("Atendendo (prioritário): %s (Idade: %d)\n", paciente->nome, paciente->idade);
                } else {
                    printf("Fila prioritária vazia!\n");
                }
                break;
            }

            case 3:
                printf("\n=== FILA PRIORITÁRIA ===\n");
                mostrar_heap(heap);
                break;
        }

        if (opcao != 4) {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n');
            getchar();
        }
    } while (opcao != 4);
}

void menu_pesquisa(ABB* arvore, Lista* lista) {
    int opcao, criterio;
    do {
        system("clear || cls");
        printf("=== PESQUISA DE PACIENTES ===\n");
        printf("1. Mostrar por ano de registro\n");
        printf("2. Mostrar por mês de registro\n");
        printf("3. Mostrar por dia de registro\n");
        printf("4. Mostrar por idade\n");
        printf("5. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 4) {
            // Limpa a árvore atual
            if (arvore->raiz) {
                destruir_arvore(arvore);
                arvore->raiz = NULL;
                arvore->qtde = 0;
            }

            // Reconstrói a árvore com o novo critério
            criterio = opcao - 1;
            Elista* atual = lista->inicio;
            while (atual != NULL) {
                inserir_abb(arvore, atual->dados, criterio);
                atual = atual->proximo;
            }

            // Mostra de acordo com o critério
            switch(opcao) {
                case 1:
                    mostrar_por_ano(arvore);
                    break;
                case 2:
                    mostrar_por_mes(arvore);
                    break;
                case 3:
                    mostrar_por_dia(arvore);
                    break;
                case 4:
                    mostrar_por_idade(arvore);
                    break;
            }
        }

        if (opcao != 5) {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n');
            getchar();
        }
    } while (opcao != 5);
}

void menu_desfazer(Fila* fila, Pilha* pilha) {
    system("clear || cls");
    printf("=== DESFAZER OPERAÇÃO ===\n");

    mostrar_operacoes(pilha);

    if (pilha->qtde == 0) {
        printf("Nenhuma operação para desfazer.\n");
        return;
    }

    printf("Deseja desfazer a última operação? (S/N): ");
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        Operacao ultima = desempilhar(pilha);

        switch(ultima.tipo) {
            case OPERACAO_ENFILEIRAR:
                printf("Desfazendo ENFILEIRAMENTO de %s...\n", ultima.paciente->nome);
                desenfileirar(fila);
                break;

            case OPERACAO_DESENFILEIRAR:
                printf("Desfazendo DESENFILEIRAMENTO de %s...\n", ultima.paciente->nome);
                enfileirar(fila, ultima.paciente);
                break;
        }
    }
}

void menu_sobre() {
    system("clear || cls");
    printf("=== SOBRE O SISTEMA ===\n");
    printf("Gerenciador de Atendimento Médico\n");
    printf("Desenvolvido por: [Seu Nome]\n");
    printf("Curso: Ciência da Computação\n");
    printf("Disciplina: Estrutura de Dados\n");
    printf("Professor: Luciano Rossi\n");
    printf("Centro Universitário FEI\n");
    printf("1º Semestre de 2025\n");
}
