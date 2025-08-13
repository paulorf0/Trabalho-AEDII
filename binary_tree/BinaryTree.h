#include <stdio.h>
#include <stdlib.h>


typedef struct {
 char *palavra;

  // Dados da música
  char *nome_musica;
  char *nome_cantor;
  char *estrofe;
  int freq;

  // Frequência em todo o repo.
  int freq_total;
}info;

typedef struct node {
  info inf;
  struct node *left;
  struct node *right;
} node;

node *criarArvore();
info *buscarArvore(node *raiz, char *palavra);
node *inserirArvore(node *raiz, info nova_info);
