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
  inform->palavra = NULL;
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

  // Capturando estrofe
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
  if (count != NULL)
    *count = tokens;

  free(copy1);
  copy1 = NULL;

  if (tokens == 0)
    return NULL;

  char **split = malloc(sizeof(char *) * (tokens + 1));
  if (split == NULL)
    return NULL;

  char *copy2 = strdup(linha);
  token = strtok(copy2, delimitador);
  int i = 0;
  while (token != NULL) {
    split[i++] = strdup(token);
    token = strtok(NULL, delimitador);
  }
  split[i] = NULL;

  free(copy2);
  copy2 = NULL;

  return split;
}

int comparar(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

void liberar_split(char **split) {
  if (split == NULL) {
    return;
  }
  for (int i = 0; split[i] != NULL; i++) {
    free(split[i]); // Libera cada palavra (alocada com strdup)
  }
  free(split); // Libera o array de ponteiros
}

// Recebe o array de palavras da linha com split nos espaços.
int frequencia_palavra_linha(const char *palavra, char **linha) {
  if (palavra == NULL || linha == NULL)
    return 0;

  int i = 0;
  int count = 0;

  while (linha[i] != NULL)
    if (strcmp(linha[i++], palavra) == 0)
      count++;

  return count;
}

int frequencia_palavra_texto(const char *palavra, char **texto) {
  if (palavra == NULL || texto == NULL || *texto == NULL)
    return 0;

  int i = 0;
  int count = 0;
  while (texto[i] != NULL) {
    char **split_linha = capturar_palavras(texto[i], " ", NULL);

    if (split_linha != NULL) {
      count += frequencia_palavra_linha(palavra, split_linha);

      liberar_split(split_linha);
    }

    i++;
  }
  return count;
}

inf *criar_dados(char *palavra, char *nome_compositor, char *nome_musica,
                 char *estrofe) {
  inf *dado = (inf *)malloc(sizeof(inf));
  dado->nome_musica = strdup(nome_musica);
  dado->nome_cantor = strdup(nome_compositor);
  dado->palavra = strdup(palavra);
  dado->estrofe = strdup(estrofe);

  return dado;
}

// Funções Privadas //

void inserir_estruturas(nodeAVL *nodeAVL, node *nodeBT, VetorOrdenado *vec,
                        float *tAVL, float *tBT, float *tVec, char **musica) {

  inf *dados_base = capturar_dados_compositor(musica);

  clock_t inicio, fim;
  float periodo;
  // INSERÇÃO AVL //

  int i = 2; // Duas primeiras linhas é de dados do autor.
  int count_palavras = 0;
  inicio = clock();

  while (musica[i] != NULL) {
    char **palavras = capturar_palavras(musica[i], " ", &count_palavras);
    for (int i = 0; i < count_palavras; i++) {
      inf *dado = criar_dados(palavras[i], dados_base->nome_cantor,
                              dados_base->nome_musica, dados_base->estrofe);

      int freq = frequencia_palavra_texto(palavras[i], musica);
      dado->freq = freq;

      if (dado != NULL) {
        inserir_avl(nodeAVL, dado);
        free(dado->estrofe);
        free(dado->nome_cantor);
        free(dado->nome_musica);
        free(dado->palavra);
        free(dado);
      }
    }
  }

  fim = clock();
  periodo = ((float)(inicio - fim)) / CLOCKS_PER_SEC;
  *tAVL = periodo;
  // INSERÇÃO AVL //

  // INSERÇÃO BT //
  inicio = clock();

  while (musica[i] != NULL) {
    char **palavras = capturar_palavras(musica[i], " ", &count_palavras);
    for (int i = 0; i < count_palavras; i++) {
      inf *dado = criar_dados(palavras[i], dados_base->nome_cantor,
                              dados_base->nome_musica, dados_base->estrofe);
      int freq = frequencia_palavra_texto(palavras[i], musica);
      dado->freq = freq;
      if (dado != NULL) {
        inserirArvore(nodeBT, dado);
        free(dado->estrofe);
        free(dado->nome_cantor);
        free(dado->nome_musica);
        free(dado->palavra);
        free(dado);
      }
    }
  }

  fim = clock();
  periodo = ((float)(inicio - fim)) / CLOCKS_PER_SEC;
  *tBT = periodo;
  // INSERÇÃO BT //

  // INSERÇÃO VEC //
  inicio = clock();

  fim = clock();
  periodo = ((float)(inicio - fim)) / CLOCKS_PER_SEC;
  *tVec = periodo;
  // INSERÇÃO VEC //

  free(dados_base->palavra);
  free(dados_base->estrofe);
  free(dados_base->nome_cantor);
  free(dados_base->nome_musica);
  free(dados_base);
}

float inserir_avl(nodeAVL *node, inf *info) {
  clock_t inicio, fim;
  inicio = clock();

  fim = clock();
  float periodo = ((float)(inicio - fim)) / CLOCKS_PER_SEC;

  return periodo;
}

float inserir_bT(node *no, inf *info) {
  clock_t inicio, fim;
  inicio = clock();

  fim = clock();
  float periodo = ((float)(inicio - fim)) / CLOCKS_PER_SEC;

  return periodo;
}

// NÃO FEITO.
float inserir_vetor(VetorOrdenado *vec, char **texto);
