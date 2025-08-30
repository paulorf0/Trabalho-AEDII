#ifndef VETOR_ORDENADO_H
#define VETOR_ORDENADO_H

#include "../general.h"
#include <stdbool.h>

typedef struct {

  inf *dados;
  int tamanho;
  int capacidade;

} VetorOrdenado;

VetorOrdenado *vetor_criar(int capacidade_inicial);
VetorOrdenado *vetor_inserir(VetorOrdenado *vetor, const inf *entrada);
inf *vetor_buscar(const VetorOrdenado *vetor, const char *palavra);
void vetor_liberar(VetorOrdenado *vetor);
void vetor_redimensionar(VetorOrdenado *vetor, int nova_capacidade);
bool vetor_vazio(const VetorOrdenado *vetor);
void vetor_imprimir(const VetorOrdenado *vetor);

#endif
