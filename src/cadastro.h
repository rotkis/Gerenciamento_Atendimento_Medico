#ifndef CADASTRO_H
#define CADASTRO_H

// Definição da estrutura Data
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
void cadastrar_paciente(Lista* lista, const Registro* paciente); // Passagem por ponteiro (evita cópia desnecessária)
void remover_paciente(Lista* lista, const char* rg); // 'const' protege o RG de modificações acidentais
Registro* buscar_paciente(const Lista* lista, const char* rg); // 'const' na lista garante que ela não será modificada

#endif
