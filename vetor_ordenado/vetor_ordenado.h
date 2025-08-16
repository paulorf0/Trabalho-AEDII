#ifndef VETOR_ORDENADO_H
#define VETOR_ORDENADO_H

#include <stdbool.h>

typedef struct {

    char *palavra;
    char *nome_musica;
    char *nome_cantor;
    char *estrofe;
    int freq_na_musica;
    int freq_total_repo;

} Entrada;


typedef struct {

    Entrada *dados; 
    int tamanho;       
    int capacidade;    

} VetorOrdenado;

VetorOrdenado* vetor_criar(int capacidade_inicial);
void vetor_inserir(VetorOrdenado *vetor, Entrada entrada);
Entrada* vetor_buscar(const VetorOrdenado *vetor, const char *palavra);
void vetor_liberar(VetorOrdenado *vetor);
void vetor_redimensionar(VetorOrdenado *vetor, int nova_capacidade);
bool vetor_vazio(const VetorOrdenado *vetor);
void vetor_imprimir(const VetorOrdenado *vetor);

#endif
