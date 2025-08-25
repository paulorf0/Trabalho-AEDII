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
}infoAVL;

typedef struct nodeavl{
  int alt; // altura do nó
  
  infoAVL inf;
  struct nodeavl *left;
  struct nodeavl *right;
} nodeAVL;

nodeAVL *criarArvoreAVL();
infoAVL *buscarArvoreAVL(nodeAVL *raiz, char *palavra);
nodeAVL *inserirArvoreAVL(nodeAVL *raiz, infoAVL nova_info);
