
#include "vetor_ordenado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

VetorOrdenado *vetor_criar(int capacidade_inicial) {
  VetorOrdenado *vetor = malloc(sizeof(VetorOrdenado));

  if (!vetor)
    return NULL;

  vetor->dados = malloc(capacidade_inicial * sizeof(inf));

  if (!vetor->dados) {

    free(vetor);
    return NULL;
  }

  vetor->tamanho = 0;
  vetor->capacidade = capacidade_inicial;
  return vetor;
}

void vetor_redimensionar(VetorOrdenado *vetor, int nova_capacidade) {
  inf *novos_dados = realloc(vetor->dados, nova_capacidade * sizeof(inf));

  if (!novos_dados)
    return;

  vetor->dados = novos_dados;
  vetor->capacidade = nova_capacidade;
}

VetorOrdenado *vetor_inserir(VetorOrdenado *vetor, const inf *entrada) {
  if (vetor->tamanho >= vetor->capacidade) {

    vetor_redimensionar(vetor, vetor->capacidade * 2);
  }

  int inicio = 0, fim = vetor->tamanho - 1;

  int pos = vetor->tamanho;

  while (inicio <= fim) {

    int meio = (inicio + fim) / 2;

    int cmp = strcmp(entrada->palavra, vetor->dados[meio].palavra);

    if (cmp < 0) {

      fim = meio - 1;
      pos = meio;

    } else if (cmp > 0) {

      inicio = meio + 1;
      pos = meio + 1;

    } else {

      if (entrada->freq > vetor->dados[meio].freq) {
        free(vetor->dados[meio].palavra);
        free(vetor->dados[meio].nome_musica);
        free(vetor->dados[meio].nome_cantor);
        free(vetor->dados[meio].estrofe);

        vetor->dados[meio].palavra = strdup(entrada->palavra);
        vetor->dados[meio].nome_musica = strdup(entrada->nome_musica);
        vetor->dados[meio].nome_cantor = strdup(entrada->nome_cantor);
        vetor->dados[meio].estrofe = strdup(entrada->estrofe);
        vetor->dados[meio].freq = entrada->freq;
      }

      vetor->dados[meio].freq_total += entrada->freq;
      return vetor;
    }
  }

  for (int i = vetor->tamanho; i > pos; i--) {

    vetor->dados[i] = vetor->dados[i - 1];
  }

  vetor->dados[pos].palavra = strdup(entrada->palavra);
  vetor->dados[pos].nome_musica = strdup(entrada->nome_musica);
  vetor->dados[pos].nome_cantor = strdup(entrada->nome_cantor);
  vetor->dados[pos].estrofe = strdup(entrada->estrofe);
  vetor->dados[pos].freq = entrada->freq;
  vetor->dados[pos].freq_total = entrada->freq;
  vetor->tamanho++;
  return vetor;
}

inf *vetor_buscar(const VetorOrdenado *vetor, const char *palavra) {

  int inicio = 0, fim = vetor->tamanho - 1;

  while (inicio <= fim) {

    int meio = (inicio + fim) / 2;

    int cmp = strcmp(palavra, vetor->dados[meio].palavra);

    if (cmp < 0) {

      fim = meio - 1;

    } else if (cmp > 0) {

      inicio = meio + 1;

    } else {

      return &vetor->dados[meio];
    }
  }

  return NULL;
}

inf *vetor_buscar_freq(const VetorOrdenado *vetor, int freq) {
  inf *dados = NULL;
  for (int i = 0; i < vetor->tamanho; i++) {
    if (vetor->dados->freq == freq) {
      dados = vetor->dados;
      break;
    }
  }

  return dados;
}

void vetor_liberar(VetorOrdenado *vetor) {

  if (!vetor)
    return;

  for (int i = 0; i < vetor->tamanho; i++) {

    free(vetor->dados[i].palavra);
    free(vetor->dados[i].nome_musica);
    free(vetor->dados[i].nome_cantor);
    free(vetor->dados[i].estrofe);
  }

  free(vetor->dados);
  free(vetor);
}

void vetor_imprimir(const VetorOrdenado *vetor) {

  printf("Vetor Ordenado (%d/%d):\n", vetor->tamanho, vetor->capacidade);

  for (int i = 0; i < vetor->tamanho; i++) {

    printf("[%d] %s (Música: %s, Freq: %d/%d)\n", i, vetor->dados[i].palavra,
           vetor->dados[i].nome_musica, vetor->dados[i].freq,
           vetor->dados[i].freq_total);
  }
}
