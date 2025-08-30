#ifndef GENERAL_H
#define GENERAL_H
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
} inf;

static void liberar_duplo(char **texto) {
  if (texto == NULL) {
    return;
  }
  for (int i = 0; texto[i] != NULL; i++) {
    free(texto[i]); // Libera cada palavra (alocada com strdup)
  }
  free(texto); // Libera o array de ponteiros
}

#endif
