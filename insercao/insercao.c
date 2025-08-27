#include "insercao.h"

// Funções Privadas //

// Texto da música já está normalizado.
inf *capturar_dados_compositor(char **text) {
  if (text == NULL || text[0] == NULL || text[1] == NULL || text[2] == NULL) {
    return NULL;
  }

  int i = 0;
  int caracteres = 0;

  inf *inform = (inf *)malloc(sizeof(inf));

  // COPIANDO NOME DA MÚSICA
  int nome_musicaLen = strlen(text[i]);
  inform->nome_musica = (char *)malloc(sizeof(char) * (nome_musicaLen + 1));
  strcpy(inform->nome_musica, text[i++]);

  // COPIANDO NOME DO CANTOR
  int nome_cantorLen = strlen(text[i]);
  inform->nome_cantor = (char *)malloc(sizeof(char) * (nome_musicaLen + 1));
  strcpy(inform->nome_cantor, text[i++]);

  // VERIFICANDO A PRIMEIRA LINHA DA MÚSICA
  char *linha1 = strdup(text[i]);
  caracteres += strlen(linha1);

  inform->estrofe = (char *)malloc(sizeof(char) * (caracteres + 1));
  strcpy(inform->estrofe, linha1);

  free(linha1);
  linha1 = NULL;

  if (caracteres < 100) {
    char *linha;
    while (text[i] != NULL) {

      linha = text[i++];
      caracteres += strlen(linha);

      if (caracteres < 100) {

        // USO INSEGURO DE REALLOC
        inform->estrofe = (char *)realloc(inform->estrofe, caracteres + 1);
        strcat(inform->estrofe, linha);

      } else {
        break;
      }
    }
  }

  return inform;
}

char **capturar_palavras(char *linha, char *delimitador, int *count) {
  char *copy1 = strdup(linha);
  int tokens = 0;
  char *token = strtok(copy1, delimitador);
  while (token != NULL) {
    tokens++;
    token = strtok(NULL, delimitador);
  }
  *count = tokens;
  free(copy1);
  copy1 = NULL;

  if (tokens == 0)
    return NULL;

  char **split = malloc(sizeof(char *) * tokens);
  if (split == NULL)
    return NULL;

  char *copy2 = strdup(linha);
  token = strtok(copy2, delimitador);
  int i = 0;
  while (token != NULL) {
    split[i++] = strdup(token);
    token = strtok(NULL, delimitador);
  }
  free(copy2);

  return split;
}

// Funções Privadas //

float inserir_avl(nodeAVL *node, char **texto) {
  clock_t inicio, fim;
  inicio = clock();

  fim = clock();
  float periodo = ((float)(inicio - fim)) / CLOCKS_PER_SEC;

  return periodo;
}

float inserir_bT(node *no, char **texto) {
  clock_t inicio, fim;
  inicio = clock();

  fim = clock();
  float periodo = ((float)(inicio - fim)) / CLOCKS_PER_SEC;

  return periodo;
}

float inserir_vetor(VetorOrdenado *vec, char **texto);
