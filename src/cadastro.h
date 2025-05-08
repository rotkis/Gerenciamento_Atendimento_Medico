#ifndef CADASTRO_H
#define CADASTRO_H

// Definição da estrutura Data
#include <stdatomic.h>
typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

// Definição da estrutura Registro (paciente)
typedef struct Registro {
    char nome[100];
    char rg[20];
    int idade;
    Data* entrada; // Ponteiro para Data (alocado dinamicamente)
} Registro;

// Nó da lista encadeada
typedef struct Elista {
    Registro* dados;      // Ponteiro para Registro (alocado dinamicamente)
    struct Elista* proximo; // Ponteiro para o próximo nó
} Elista;

// Estrutura da lista encadeada
typedef struct Lista {
    Elista* inicio; // Ponteiro para o primeiro nó
    int qtde;       // Quantidade de pacientes na lista
} Lista;

// Declarações das funções
Elista* criar_Elista(Registro* paciente);
void criar_lista(Lista* lista); // Cria uma lista vazia
void cadastrar_paciente(Lista* lista, Registro* paciente); // Passagem por ponteiro (evita cópia desnecessária)
void remover_paciente(Lista* lista, const char* rg); // 'const' protege o RG de modificações acidentais
Registro* buscar_paciente(const Lista* lista, const char* rg); // 'const' na lista garante que ela não será modificada
void editar_paciente(Lista* lista, const char* rg, Registro* novo); // 'const' protege o RG de modificações acidentais
void mostrar_paciente(const Lista* lista); // 'const' protege o paciente de modificações acidentais
// Adicione este protótipo
void liberar_lista(Lista* lista);
#endif
