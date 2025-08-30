
#ifndef BINARY_TREE_FREQ_H
#define BINARY_TREE_FREQ_H

#include "../general.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _nodefreq_ {
  inf inf;
  struct _nodefreq_ *left;
  struct _nodefreq_ *right;
} nodeFreq;

nodeFreq *criarArvoreFreq();
inf *buscarArvoreFreq(nodeFreq *raiz, int freq);
nodeFreq *inserirArvoreFreq(nodeFreq *raiz, const inf *nova_inf);
void percorrerArvoreFreq(nodeFreq *raiz);
void liberarArvoreFreq(nodeFreq *raiz);

#endif
