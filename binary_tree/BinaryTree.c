#include "BinaryTree.h"
#include <string.h>
#include <stdlib.h>

// Funções Privadas //
int trocar_no_igual(info inf1, info inf2) {}
// Funções Privadas //

node *criarArvore() { return NULL; }

info *buscarArvore(node *raiz, char *palavra)
{
  if (raiz == NULL)
    return NULL;

  int comparacao = strcmp(palavra, raiz->inf.palavra);

  if (comparacao < 0)
  {
    return buscarArvore(raiz->left, palavra);
  }
  else if (comparacao > 0)
  {
    return buscarArvore(raiz->right, palavra);
  }
  else
  {
    return &(raiz->inf);
  }
}

/*

*/

node *inserirArvore(node *raiz, info inf)
{
  if (raiz == NULL)
  {
    node *no = (node *)malloc(sizeof(node));
    if (!no)
    {
      perror("Falha ao alocar memória para novo nó");
      exit(1);
    }
    no->right = NULL;
    no->left = NULL;

    no->inf = inf;
    no->inf.freq_total = inf.freq;

    return no;
  }

  int comparacao = strcmp(inf.palavra, raiz->inf.palavra);

  if (comparacao < 0)
  {
    raiz->left = inserirArvore(raiz->left, inf);
  }
  else if (comparacao > 0)
  {
    raiz->right = inserirArvore(raiz->right, inf);
  }
  else
  {
    raiz->inf.freq_total += inf.freq;

    if (inf.freq > raiz->inf.freq)
    {
      free(raiz->inf.nome_musica);
      free(raiz->inf.nome_cantor);
      free(raiz->inf.estrofe);

      raiz->inf.nome_musica = inf.nome_musica;
      raiz->inf.nome_cantor = inf.nome_cantor;
      raiz->inf.estrofe = inf.estrofe;
      raiz->inf.freq = inf.freq;

      free(inf.palavra);
    }
    else
    {
      free(inf.palavra);
      free(inf.nome_musica);
      free(inf.nome_cantor);
      free(inf.estrofe);
    }
  }

  return raiz;
}
