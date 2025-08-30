#ifndef AVLFREQ_H
#define AVLFREQ_H

#include "../general.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _nodeavlfreq_ {
  int alt; // altura do nó

  inf inf;
  struct _nodeavlfreq_ *left;
  struct _nodeavlfreq_ *right;
} nodeAVLFreq;

nodeAVLFreq *criarArvoreAVLFreq();
inf *buscarArvoreAVLFreq(nodeAVLFreq *raiz, int freq);
nodeAVLFreq *inserirArvoreAVLFreq(nodeAVLFreq *raiz, const inf *nova_inf);
void percorrerArvoreAVLFreq(nodeAVLFreq *raiz);
void liberarArvoreAVLFreq(nodeAVLFreq *raiz);

#endif
