
#ifndef AVL_H
#define AVL_H

#include "../general.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _nodeavl_ {
  int alt; // altura do nó

  inf inf;
  struct _nodeavl_ *left;
  struct _nodeavl_ *right;
} nodeAVL;

nodeAVL *criarArvoreAVL();
inf *buscarArvoreAVL(nodeAVL *raiz, char *palavra);
nodeAVL *inserirArvoreAVL(nodeAVL *raiz, const inf *nova_inf);
void percorrerArvoreAVL(nodeAVL *raiz);
void liberarArvoreAVL(nodeAVL *raiz);

#endif
