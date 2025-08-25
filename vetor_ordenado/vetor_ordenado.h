#ifndef VETOR_ORDENADO_H
#define VETOR_ORDENADO_H

#include <stdbool.h>
#include <time.h>

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
    double tempo_total_insercao;

} VetorOrdenado;

VetorOrdenado* vetor_criar(int capacidade_inicial);
void vetor_inserir(VetorOrdenado *vetor, Entrada entrada);
Entrada* vetor_buscar(const VetorOrdenado *vetor, const char *palavra);
void vetor_liberar(VetorOrdenado *vetor);
void vetor_redimensionar(VetorOrdenado *vetor, int nova_capacidade);
bool vetor_vazio(const VetorOrdenado *vetor);
void vetor_imprimir(const VetorOrdenado *vetor);
void vetor_ordenar_por_frequencia(VetorOrdenado *vetor);
void processar_palavras_musica(VetorOrdenado *vetor, char **letra, const char *nome_musica, const char *nome_cantor);

double vetor_get_tempo_total(const VetorOrdenado *vetor);

void vetor_reset_tempo(VetorOrdenado *vetor);

double processar_palavras_musica_com_tempo(VetorOrdenado *vetor, char **letra, const char *nome_musica, const char *nome_cantor);

double get_real_time();
double elapsed_time(double start, double end);

#endif