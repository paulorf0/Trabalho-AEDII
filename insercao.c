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
  inform->nome_cantor = (char *)malloc(sizeof(char) * (nome_cantorLen + 1));
  strcpy(inform->nome_cantor, text[i++]);

  // VERIFICANDO A PRIMEIRA LINHA DA MÚSICA
  char *linha1 = strdup(text[i]);
  caracteres += strlen(linha1) + 1;

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
        inform->estrofe = (char *)realloc(inform->estrofe, caracteres + 1);
        strcat(inform->estrofe, " ");
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
  free(copy1);
  copy1 = NULL;

  if (count != NULL)
    *count = tokens;

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

// Recebe o array de palavras da linha com split nos espaços.
int frequencia_palavra_linha(const char *palavra, char **linha) {
  if (palavra == NULL || linha == NULL)
    return 0;

  int i = 0;
  int count = 0;

  while (linha[i] != NULL) {
    if (strlen(linha[i]) > 3 && strcmp(linha[i], palavra) == 0)
      count++;
    i++;
  }
  return count;
}

int frequencia_palavra_texto(const char *palavra, char **texto) {
  if (palavra == NULL || texto == NULL || *texto == NULL)
    return 0;

  int i = 2;
  int count = 0;
  while (texto[i] != NULL) {

    char **split_linha = capturar_palavras(texto[i], " ", NULL);

    if (split_linha != NULL) {
      count += frequencia_palavra_linha(palavra, split_linha);

      liberar_duplo(split_linha);
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

/*
 * Essa função não é eficiente.
 * frequencia_palavra_texto precisa iterar sobre toda a música, e isso é feito
 * em cada palavra
 */

void inserir_estruturas(nodeAVL **nodeavl, nodeAVLFreq **nodeAvlFreq,
                        node **nodeBT, nodeFreq **nodeBTFreq,
                        VetorOrdenado **vec, float *tAVL, float *tBT,
                        float *tVec, char **musica, char ***processadas_ptr,
                        int *count_processado_ptr)

{

  inf *dados_base = capturar_dados_compositor(musica);
  if (dados_base == NULL) {
    return;
  }

  clock_t inicio, fim;
  float periodo;
  // INSERÇÃO AVL //

  int count_palavras = 0;
  inicio = clock();

  char ***processadas = processadas_ptr;
  int *count_processado = count_processado_ptr;

  *processadas = (char **)realloc(*processadas,
                                  sizeof(char *) * ((*count_processado) + 1));

  for (int i = 2; musica[i] != NULL; i++) {

    char **palavras = capturar_palavras(musica[i], " ", &count_palavras);
    if (palavras) {
      for (int j = 0; palavras[j] != NULL; j++) {
        if (strlen(palavras[j]) < 3)
          continue;

        int existe = 0;
        for (int k = 0; k < *count_processado; k++)
          if (strcmp((*processadas)[k], palavras[j]) == 0) {
            existe = 1;
            break;
          }
        if (existe)
          continue;

        inf *dado = criar_dados(palavras[j], dados_base->nome_cantor,
                                dados_base->nome_musica, dados_base->estrofe);
        dado->freq = frequencia_palavra_texto(palavras[j], musica);

        *nodeavl = inserirArvoreAVL(*nodeavl, dado);

        (*processadas)[*count_processado] = strdup(palavras[j]);
        (*count_processado)++;

        free(dado->estrofe);
        free(dado->nome_cantor);
        free(dado->nome_musica);
        free(dado->palavra);
        free(dado);
      }
      liberar_duplo(palavras);
    }
  }

  fim = clock();
  periodo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
  if (tAVL != NULL)
    *tAVL = periodo;
  // INSERÇÃO AVL //

  count_processado = 0;
  // INSERINDO POR FREQUENCIA EM AVL //
  for (int i = 2; musica[i] != NULL; i++) {
    char **palavras = capturar_palavras(musica[i], " ", &count_palavras);
    if (palavras) {
      for (int j = 0; palavras[j] != NULL; j++) {
        if (strlen(palavras[j]) < 3)
          continue;

        int existe = 0;
        for (int k = 0; k < count_processado; k++)
          if (strcmp(processadas[k], palavras[j]) == 0) {
            existe = 1;
            break;
          }
        if (existe)
          continue;

        inf *dado = criar_dados(palavras[j], dados_base->nome_cantor,
                                dados_base->nome_musica, dados_base->estrofe);
        dado->freq = frequencia_palavra_texto(palavras[j], musica);

        *nodeAvlFreq = inserirArvoreAVLFreq(*nodeAvlFreq, dado);
        count_processado++;

        free(dado->estrofe);
        free(dado->nome_cantor);
        free(dado->nome_musica);
        free(dado->palavra);
        free(dado);
      }
      liberar_duplo(palavras);
    }
  }
  // INSERINDO POR FREQUENCIA EM AVL //

  // INSERÇÃO BT //

  inicio = clock();
  count_processado = 0;
  for (int i = 2; musica[i] != NULL; i++) {
    char **palavras = capturar_palavras(musica[i], " ", &count_palavras);
    for (int j = 0; j < count_palavras; j++) {
      if (strlen(palavras[j]) < 3)
        continue;

      int existe = 0;

      for (int k = 0; k < count_processado; k++)
        if (strcmp(processadas[k], palavras[j]) == 0) {
          existe = 1;
          break;
        }
      if (existe)
        continue;

      inf *dado = criar_dados(palavras[j], dados_base->nome_cantor,
                              dados_base->nome_musica, dados_base->estrofe);
      int freq = frequencia_palavra_texto(palavras[j], musica);
      dado->freq = freq;

      *nodeBT = inserirArvore(*nodeBT, dado);
      count_processado++;

      free(dado->estrofe);
      free(dado->nome_cantor);
      free(dado->nome_musica);
      free(dado->palavra);
      free(dado);
    }
    liberar_duplo(palavras);
  }

  fim = clock();
  periodo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
  if (tBT != NULL)
    *tBT = periodo;
  // INSERÇÃO BT //

  // INSERÇÃO BT FREQ //
  count_processado = 0;
  for (int i = 2; musica[i] != NULL; i++) {
    char **palavras = capturar_palavras(musica[i], " ", &count_palavras);
    for (int j = 0; j < count_palavras; j++) {
      if (strlen(palavras[j]) < 3)
        continue;
      int existe = 0;
      for (int k = 0; k < count_processado; k++)
        if (strcmp(processadas[k], palavras[j]) == 0) {
          existe = 1;
          break;
        }
      if (existe)
        continue;

      inf *dado = criar_dados(palavras[j], dados_base->nome_cantor,
                              dados_base->nome_musica, dados_base->estrofe);
      int freq = frequencia_palavra_texto(palavras[j], musica);
      dado->freq = freq;

      *nodeBTFreq = inserirArvoreFreq(*nodeBTFreq, dado);

      count_processado++;
      free(dado->estrofe);
      free(dado->nome_cantor);
      free(dado->nome_musica);
      free(dado->palavra);
      free(dado);
    }
    liberar_duplo(palavras);
  }

  // INSERÇÃO VEC //
  inicio = clock();
  count_processado = 0;
  for (int i = 2; musica[i] != NULL; i++) {
    char **palavras = capturar_palavras(musica[i], " ", &count_palavras);
    for (int j = 0; j < count_palavras; j++) {
      if (strlen(palavras[j]) < 3)
        continue;

      int existe = 0;
      for (int k = 0; k < count_processado; k++)
        if (strcmp(processadas[k], palavras[j]) == 0) {
          existe = 1;
          break;
        }
      if (existe)
        continue;
      inf *dado = criar_dados(palavras[j], dados_base->nome_cantor,
                              dados_base->nome_musica, dados_base->estrofe);
      int freq = frequencia_palavra_texto(palavras[j], musica);
      dado->freq = freq;

      *vec = vetor_inserir(*vec, dado);
      count_processado++;
      free(dado->estrofe);
      free(dado->nome_cantor);
      free(dado->nome_musica);
      free(dado->palavra);
      free(dado);
    }
    liberar_duplo(palavras);
  }

  fim = clock();
  periodo = ((float)(fim - inicio)) / CLOCKS_PER_SEC;
  if (tVec != NULL)
    *tVec = periodo;
  // INSERÇÃO VEC //

  liberar_duplo(processadas);
  free(dados_base->palavra);
  free(dados_base->estrofe);
  free(dados_base->nome_cantor);
  free(dados_base->nome_musica);
  free(dados_base);
}

inf *buscar_informacao(nodeAVL **nodeavl, nodeAVLFreq **nodeAvlFreq,
                       node **nodeBT, nodeFreq **nodeBTFreq,
                       VetorOrdenado **vec, float *tAVL, float *tBT,
                       float *tVec, char *palavra, int *freq) {

  clock_t inicio, fim;
  float periodo;
  if (palavra != NULL) {
    inicio = clock();
    inf *dados_encontrados_vec = vetor_buscar(*vec, palavra);
    fim = clock();
    periodo = ((float)(fim - inicio)) / CLOCKS_PER_SEC;
    if (tVec != NULL) {
      *tVec = periodo;
    }

    inicio = clock();
    inf *dados_encontrados_bt = buscarArvore(*nodeBT, palavra);
    fim = clock();
    periodo = ((float)(fim - inicio)) / CLOCKS_PER_SEC;
    if (tBT != NULL) {
      *tBT = periodo;
    }

    // -- AVL --
    inicio = clock();
    inf *dados_encontrados_avl = buscarArvoreAVL(*nodeavl, palavra);
    fim = clock();
    periodo = ((float)(fim - inicio)) / CLOCKS_PER_SEC;
    if (tAVL != NULL) {
      *tAVL = periodo;
    }
    // -- AVL -- //

    return dados_encontrados_avl;
  } else if (freq != NULL) {
    // -- AVL -- //
    inicio = clock();
    inf *dados_encontrados_vec_freq = vetor_buscar_freq(*vec, *freq);
    fim = clock();
    periodo = ((float)(fim - inicio)) / CLOCKS_PER_SEC;
    if (tVec != NULL) {
      *tVec = periodo;
    }
    // -- AVL --//

    // -- BINARY TREE -- //
    inicio = clock();
    inf *dados_encontrados_bt_freq = buscarArvoreFreq(*nodeBTFreq, *freq);
    fim = clock();
    periodo = ((float)(fim - inicio)) / CLOCKS_PER_SEC;
    if (tBT != NULL) {
      *tBT = periodo;
    }

    inicio = clock();
    inf *dados_encontrados_avl_freq = buscarArvoreAVLFreq(*nodeAvlFreq, *freq);
    fim = clock();
    periodo = ((float)(fim - inicio)) / CLOCKS_PER_SEC;
    if (tAVL != NULL) {
      *tAVL = periodo;
    }
    // BINARY TREE //
    return dados_encontrados_bt_freq;
  }

  return NULL;
}
