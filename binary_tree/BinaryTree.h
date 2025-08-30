
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "../general.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  inf inf;
  struct node *left;
  struct node *right;
} node;

node *criarArvore();
inf *buscarArvore(node *raiz, char *palavra);
node *inserirArvore(node *raiz, const inf *nova_inf);
void percorrerArvore(node *raiz);
void liberarArvore(node *raiz);

#endif
