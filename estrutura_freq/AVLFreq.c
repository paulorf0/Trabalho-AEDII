
#include "AVLFreq.h"
#include <stdlib.h>
#include <string.h>

// Funções Privadas //
static int max(int a, int b) { return (a > b) ? a : b; }

static int altura_no(nodeAVLFreq *n) {
  if (n == NULL)
    return -1;
  return n->alt;
}

static int coeficiente_balanceamento(nodeAVLFreq *node) {
  if (node == NULL) {
    return 0;
  }
  return altura_no(node->left) - altura_no(node->right);
}

nodeAVLFreq *right_rotate(nodeAVLFreq *y) {
  nodeAVLFreq *x = y->left;
  nodeAVLFreq *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->alt = max(altura_no(y->left), altura_no(y->right)) + 1;
  x->alt = max(altura_no(x->left), altura_no(x->right)) + 1;

  return x;
}

nodeAVLFreq *left_rotate(nodeAVLFreq *x) {
  nodeAVLFreq *y = x->right;
  nodeAVLFreq *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->alt = max(altura_no(x->left), altura_no(x->right)) + 1;
  y->alt = max(altura_no(y->left), altura_no(y->right)) + 1;

  return y;
}
// Funções Privadas //

nodeAVLFreq *criarArvoreAVLFreq() { return NULL; }

inf *buscarArvoreAVLFreq(nodeAVLFreq *raiz, int freq) {
  if (raiz == NULL)
    return NULL;

  int comparacao = freq - raiz->inf.freq;

  if (comparacao < 0) {
    return buscarArvoreAVLFreq(raiz->left, freq);
  } else if (comparacao > 0) {
    return buscarArvoreAVLFreq(raiz->right, freq);
  } else {
    return &(raiz->inf);
  }
}

nodeAVLFreq *inserirArvoreAVLFreq(nodeAVLFreq *raiz, const inf *dado_novo) {
  if (raiz == NULL) {
    nodeAVLFreq *no = (nodeAVLFreq *)malloc(sizeof(nodeAVLFreq));
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

  int comparacao = dado_novo->freq - raiz->inf.freq;

  if (comparacao < 0) {
    raiz->left = inserirArvoreAVLFreq(raiz->left, dado_novo);
  } else if (comparacao > 0) {
    raiz->right = inserirArvoreAVLFreq(raiz->right, dado_novo);
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
    if (dado_novo->freq < raiz->left->inf.freq) { // Caso Esquerda-Esquerda
      return right_rotate(raiz);
    } else { // Caso Esquerda-Direita
      raiz->left = left_rotate(raiz->left);
      return right_rotate(raiz);
    }
  }
  if (balanco < -1) {
    if (dado_novo->freq > raiz->right->inf.freq) { // Caso Direita-Direita
      return left_rotate(raiz);
    } else { // Caso Direita-Esquerda
      raiz->right = right_rotate(raiz->right);
      return left_rotate(raiz);
    }
  }
  return raiz;
}

void percorrerArvoreAVLFreq(nodeAVLFreq *raiz) {
  if (raiz == NULL)
    return;

  percorrerArvoreAVLFreq(raiz->left);
  printf("  - Palavra: %s (Freq: %d, Alt: %d)\n", raiz->inf.palavra,
         raiz->inf.freq_total, raiz->alt);
  percorrerArvoreAVLFreq(raiz->right);
}

void liberarArvoreAVLFreq(nodeAVLFreq *raiz) {
  if (raiz == NULL)
    return;

  liberarArvoreAVLFreq(raiz->left);
  liberarArvoreAVLFreq(raiz->right);

  free(raiz->inf.palavra);
  free(raiz->inf.nome_musica);
  free(raiz->inf.nome_cantor);
  free(raiz->inf.estrofe);
  free(raiz);
}
