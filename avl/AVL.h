#include <stdio.h>
#include <stdlib.h>

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "../general.h"

#endif

typedef struct nodeavl {
  int alt; // altura do nó

  inf inf;
  struct nodeavl *left;
  struct nodeavl *right;
} nodeAVL;

nodeAVL *criarArvoreAVL();
inf *buscarArvoreAVL(nodeAVL *raiz, char *palavra);
nodeAVL *inserirArvoreAVL(nodeAVL *raiz, const inf *nova_inf);
