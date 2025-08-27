#include "AVL.h"
#include <stdlib.h>
#include <string.h>

// Funções Privadas //
int max(int a, int b) { return (a > b) ? a : b; }

int altura_no(nodeAVL *n) {
  if (n == NULL)
    return -1;
  return n->alt;
}

int coeficiente_balanceamento(nodeAVL *node) {
  int left = node->left == NULL ? 0 : node->left->alt;
  int right = node->right == NULL ? 0 : node->right->alt;
  return left - right;
}

nodeAVL *LR(nodeAVL *x) {
  nodeAVL *y = x->right;
  nodeAVL *z = y->left;

  y->left = x;
  x->right = z;

  x->alt = 1 + max(altura_no(x->left), altura_no(x->right));
  y->alt = 1 + max(altura_no(y->left), altura_no(y->right));

  return y;
}

nodeAVL *RR(nodeAVL *y) {
  nodeAVL *x = y->left;
  nodeAVL *z = x->right;

  x->right = y;
  y->left = z;

  x->alt = 1 + max(altura_no(x->left), altura_no(x->right));
  y->alt = 1 + max(altura_no(y->left), altura_no(y->right));

  return x;
}
// Funções Privadas //

nodeAVL *criarArvoreAVL() { return NULL; }

inf *buscarArvoreAVL(nodeAVL *raiz, char *palavra) {
  if (raiz == NULL)
    return NULL;

  int comparacao = strcmp(palavra, raiz->inf.palavra);

  if (comparacao < 0) {
    return buscarArvore(raiz->left, palavra);
  } else if (comparacao > 0) {
    return buscarArvore(raiz->right, palavra);
  } else {
    return &(raiz->inf);
  }
}

/*

*/

nodeAVL *inserirArvoreAVL(nodeAVL *raiz, inf inf) {
  if (raiz == NULL) {
    nodeAVL *no = (nodeAVL *)malloc(sizeof(nodeAVL));
    if (!no) {
      perror("Falha ao alocar memória para novo nó");
      exit(1);
    }
    no->right = NULL;
    no->left = NULL;

    no->alt = 0;
    no->inf = inf;
    no->inf.freq_total = inf.freq;

    return no;
  }

  int comparacao = strcmp(inf.palavra, raiz->inf.palavra);

  if (comparacao < 0) {
    raiz->left = inserirArvore(raiz->left, inf);
  } else if (comparacao > 0) {
    raiz->right = inserirArvore(raiz->right, inf);
  } else {
    raiz->inf.freq_total += inf.freq;

    if (inf.freq > raiz->inf.freq) {
      free(raiz->inf.nome_musica);
      free(raiz->inf.nome_cantor);
      free(raiz->inf.estrofe);

      raiz->inf.nome_musica = inf.nome_musica;
      raiz->inf.nome_cantor = inf.nome_cantor;
      raiz->inf.estrofe = inf.estrofe;
      raiz->inf.freq = inf.freq;

      free(inf.palavra);
    } else {
      free(inf.palavra);
      free(inf.nome_musica);
      free(inf.nome_cantor);
      free(inf.estrofe);
    }
  }

  raiz->alt = 1 + max(altura_no(raiz->left), altura_no(raiz->right));
  int balanco = coeficiente_balanceamento(raiz);

  if (balanco > 1) {
    if (strcmp(inf.palavra, raiz->left->inf.palavra) <
        0) { // Caso Esquerda-Esquerda
      return RR(raiz);
    } else { // Caso Esquerda-Direita
      raiz->left = LR(raiz->left);
      return RR(raiz);
    }
  }
  if (balanco < -1) {
    if (strcmp(inf.palavra, raiz->right->inf.palavra) >
        0) { // Caso Direita-Direita
      return LR(raiz);
    } else { // Caso Direita-Esquerda
      raiz->right = RR(raiz->right);
      return LR(raiz);
    }
  }

  return raiz;
}
