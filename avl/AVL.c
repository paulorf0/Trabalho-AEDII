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
  if (node == NULL) {
    return 0;
  }
  return altura_no(node->left) - altura_no(node->right);
}

nodeAVL *RR(nodeAVL *y) {
  nodeAVL *x = y->left;
  nodeAVL *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->alt = max(altura_no(y->left), altura_no(y->right)) + 1;
  x->alt = max(altura_no(x->left), altura_no(x->right)) + 1;

  return x;
}

nodeAVL *LR(nodeAVL *x) {
  nodeAVL *y = x->right;
  nodeAVL *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->alt = max(altura_no(x->left), altura_no(x->right)) + 1;
  y->alt = max(altura_no(y->left), altura_no(y->right)) + 1;

  return y;
}
// Funções Privadas //

nodeAVL *criarArvoreAVL() { return NULL; }

inf *buscarArvoreAVL(nodeAVL *raiz, char *palavra) {
  if (raiz == NULL)
    return NULL;

  int comparacao = strcmp(palavra, raiz->inf.palavra);

  if (comparacao < 0) {
    return buscarArvoreAVL(raiz->left, palavra);
  } else if (comparacao > 0) {
    return buscarArvoreAVL(raiz->right, palavra);
  } else {
    return &(raiz->inf);
  }
}

/*

*/

nodeAVL *inserirArvoreAVL(nodeAVL *raiz, const inf *dado_novo) {
  if (raiz == NULL) {
    nodeAVL *no = (nodeAVL *)malloc(sizeof(nodeAVL));
    if (!no) {
      printf("\n--ERRO DE ALOCACAO | AVL\n");
      exit(1);
    }
    no->right = NULL;
    no->left = NULL;
    no->alt = 0;

    no->inf.palavra = strdup(dado_novo->palavra);
    no->inf.nome_musica = strdup(dado_novo->nome_musica);
    no->inf.nome_cantor = strdup(dado_novo->nome_cantor);
    no->inf.estrofe = strdup(dado_novo->estrofe);
    no->inf.freq = dado_novo->freq;
    no->inf.freq_total = dado_novo->freq;

    // Verifique se strdup falhou
    if (!no->inf.palavra || !no->inf.nome_musica || !no->inf.nome_cantor ||
        !no->inf.estrofe) {
      printf("\n--ERRO NO STRDUP | AVL--\n");
      free(no->inf.palavra);
      free(no->inf.nome_musica);
      free(no->inf.nome_cantor);
      free(no->inf.estrofe);
      free(no);
      return NULL; // Indica falha na inserção
    }

    return no;
  }

  int comparacao = strcmp(dado_novo->palavra, raiz->inf.palavra);

  if (comparacao < 0) {
    raiz->left = inserirArvoreAVL(raiz->left, dado_novo);
  } else if (comparacao > 0) {
    raiz->right = inserirArvoreAVL(raiz->right, dado_novo);
  } else {
    raiz->inf.freq_total += dado_novo->freq;

    if (dado_novo->freq > raiz->inf.freq) {
      free(raiz->inf.nome_musica);
      free(raiz->inf.nome_cantor);
      free(raiz->inf.estrofe);

      raiz->inf.nome_musica = strdup(dado_novo->nome_musica);
      raiz->inf.nome_cantor = strdup(dado_novo->nome_cantor);
      raiz->inf.estrofe = strdup(dado_novo->estrofe);
      raiz->inf.freq = dado_novo->freq;
    }
  }
  raiz->alt = 1 + max(altura_no(raiz->left), altura_no(raiz->right));
  int balanco = coeficiente_balanceamento(raiz);

  if (balanco > 1) {
    if (strcmp(dado_novo->palavra, raiz->left->inf.palavra) <
        0) { // Caso Esquerda-Esquerda
      return RR(raiz);
    } else { // Caso Esquerda-Direita
      raiz->left = LR(raiz->left);
      return RR(raiz);
    }
  }
  if (balanco < -1) {
    if (strcmp(dado_novo->palavra, raiz->right->inf.palavra) >
        0) { // Caso Direita-Direita
      return LR(raiz);
    } else { // Caso Direita-Esquerda
      raiz->right = RR(raiz->right);
      return LR(raiz);
    }
  }
  return raiz;
}

void percorrerArvoreAVL(nodeAVL *raiz) {
  if (raiz == NULL)
    return;

  percorrerArvoreAVL(raiz->left);
  printf("  - Palavra: %s (Freq: %d, Alt: %d)\n", raiz->inf.palavra,
         raiz->inf.freq_total, raiz->alt);
  percorrerArvoreAVL(raiz->right);
}

void liberarArvoreAVL(nodeAVL *raiz) {
  if (raiz == NULL)
    return;

  liberarArvoreAVL(raiz->left);
  liberarArvoreAVL(raiz->right);

  free(raiz->inf.palavra);
  free(raiz->inf.nome_musica);
  free(raiz->inf.nome_cantor);
  free(raiz->inf.estrofe);
  free(raiz);
}
