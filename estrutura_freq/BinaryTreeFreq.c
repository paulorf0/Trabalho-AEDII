
#include "BinaryTreeFreq.h"

nodeFreq *criarArvoreFreq() { return NULL; }

inf *buscarArvoreFreq(nodeFreq *raiz, int freq) {
  if (raiz == NULL)
    return NULL;

  int comparacao = freq - raiz->inf.freq;

  if (comparacao < 0) {
    return buscarArvoreFreq(raiz->left, freq);
  } else if (comparacao > 0) {
    return buscarArvoreFreq(raiz->right, freq);
  } else {
    return &(raiz->inf);
  }
}

nodeFreq *inserirArvoreFreq(nodeFreq *no, const inf *dado_novo) {

  if (no == NULL) {
    nodeFreq *no = (nodeFreq *)malloc(sizeof(nodeFreq));
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

  int comparacao = dado_novo->freq - no->inf.freq;

  if (comparacao < 0) {
    no->left = inserirArvoreFreq(no->left, dado_novo);
  } else if (comparacao > 0) {
    no->right = inserirArvoreFreq(no->right, dado_novo);
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

void percorrerArvoreFreq(nodeFreq *raiz) {
  if (raiz == NULL)
    return;

  percorrerArvoreFreq(raiz->left);
  printf("  - Palavra: %s (Freq: %d)\n", raiz->inf.palavra,
         raiz->inf.freq_total);
  percorrerArvoreFreq(raiz->right);
}

void liberarArvoreFreq(nodeFreq *raiz) {
  if (raiz == NULL)
    return;

  liberarArvoreFreq(raiz->left);
  liberarArvoreFreq(raiz->right);

  free(raiz->inf.palavra);
  free(raiz->inf.nome_musica);
  free(raiz->inf.nome_cantor);
  free(raiz->inf.estrofe);
  free(raiz);
}
