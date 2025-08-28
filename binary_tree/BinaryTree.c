#include "BinaryTree.h"
#include <stdlib.h>
#include <string.h>

node *criarArvore() { return NULL; }

inf *buscarArvore(node *raiz, char *palavra) {
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

node *inserirArvore(node *no, const inf *dado_novo) {

  if (no == NULL) {
    node *no = (node *)malloc(sizeof(node));
    if (!no) {
      perror("Falha ao alocar memória para novo nó");
      exit(1);
    }
    no->right = NULL;
    no->left = NULL;

    no->inf.palavra = strdup(dado_novo->palavra);
    no->inf.nome_musica = strdup(dado_novo->nome_musica);
    no->inf.nome_cantor = strdup(dado_novo->nome_cantor);
    no->inf.estrofe = strdup(dado_novo->estrofe);
    no->inf.freq = dado_novo->freq;
    no->inf.freq_total = dado_novo->freq;

    // Verificação de erro no strdup.
    if (!no->inf.palavra || !no->inf.nome_musica || !no->inf.nome_cantor ||
        !no->inf.estrofe) {
      free(no->inf.palavra);
      free(no->inf.nome_musica);
      free(no->inf.nome_cantor);
      free(no->inf.estrofe);
      free(no);
      return NULL;
    }

    return no;
  }

  int comparacao = strcmp(dado_novo->palavra, no->inf.palavra);

  if (comparacao < 0) {
    no->left = inserirArvore(no->left, dado_novo);
  } else if (comparacao > 0) {
    no->right = inserirArvore(no->right, dado_novo);
  } else {
    no->inf.freq_total += dado_novo->freq;

    if (dado_novo->freq > no->inf.freq) {
      free(no->inf.nome_musica);
      free(no->inf.nome_cantor);
      free(no->inf.estrofe);

      no->inf.nome_musica = strdup(dado_novo->nome_musica);
      no->inf.nome_cantor = strdup(dado_novo->nome_cantor);
      no->inf.estrofe = strdup(dado_novo->estrofe);
      no->inf.freq = dado_novo->freq;
    }
  }

  return no;
}
