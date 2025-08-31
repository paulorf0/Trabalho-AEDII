#include "menu.h"

// -- Funções Privada -- //
// https://stackoverflow.com/questions/38767967/clear-input-buffer-after-fgets-in-c
void flush_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void opcoes() {
  printf("\n-------------------\n");
  printf("1. Carregar arquivo\n");
  printf("2. Buscar palavra\n");
  printf("3. Buscar frequência\n");
  printf("0. Sair");
  printf("\n-------------------\n");
}

// Define o tamanho do buffer para captura de opção ou frequência.
int capturar_valor(const int p) {
  int n = 0;
  scanf("%d", &n);

  return n;
}

char *capturar_nome() {
  char buffer[150];
  char *nome = NULL;

  if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    if (strlen(buffer) == 1 && buffer[0] == '\n') {
      if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
      }
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
    }

    nome = strdup(buffer);
  }

  return nome;
}

// -- Funções Privada -- //

void menu(nodeAVL **nodeavl, node **nodeBT, VetorOrdenado **vec,
          nodeAVLFreq **nodeAvlF, nodeFreq **nodeF) {

  while (true) {
    opcoes();

    printf("Digite a opcao: ");
    int op = capturar_valor(2);
    flush_input_buffer();
    if (op > 3 || op < 0) {
      printf("A opcao nao e valida!\n");
      continue;
    }

    switch (op) {
    case 0:
      printf("\n-----Fechando o programa!-----\n");
      return;
      break;
    case 1:
      printf("Digite o nome do arquivo: ");
      char *nome = capturar_nome();
      char **musica = obter_musica(nome, NULL);

      if (musica == NULL) {
        continue;
      }

      char **minha_lista_processadas = NULL;
      int meu_contador_processado = 0;

      float tAVL = 0, tBT = 0, tVec = 0;
      inserir_estruturas(nodeavl, nodeAvlF, nodeBT, nodeF, vec, &tAVL, &tBT,
                         &tVec, musica, &minha_lista_processadas,
                         &meu_contador_processado);
      printf("\n--     MUSICA INSERIDA       --\n");
      printf("--      Tempo Vetor:     %f  -- \n", tVec);
      printf("--      Tempo  AVL:      %f  -- \n", tAVL);
      printf("-- Tempo Arvore Binaria: %f  -- \n", tBT);
      free(nome);
      liberar_duplo(musica);
      break;
    case 2:
      printf("\n-- BUSCAR POR PALAVRA -- \n");
      printf("Digite a palavra: ");
      char *palavra = capturar_nome();
      inf *info = buscar_informacao(nodeavl, nodeAvlF, nodeBT, nodeF, vec,
                                    &tAVL, &tBT, &tVec, palavra, NULL);
      if (info == NULL) {
        printf("\n-- PALAVRA NAO REGISTRADA --\n");
        continue;
      }

      printf("\n--          DADOS         --\n");
      printf("Nome Cantor: %s\nNome Musica: %s\n Frequencia: %d\n Frequencia "
             "no repositorio: %d\n\nEstrofe:\n%s",
             info->nome_cantor, info->nome_musica, info->freq, info->freq_total,
             info->estrofe);

      break;
    case 3:
      printf("\n-- BUSCAR POR FREQUENCIA -- \n");
      printf("Digite a palavra: ");
      int freq = capturar_valor(5); // Até 9999

      inf *infoFreq = buscar_informacao(nodeavl, nodeAvlF, nodeBT, nodeF, vec,
                                        &tAVL, &tBT, &tVec, NULL, &freq);
      if (infoFreq == NULL) {
        printf("\n-- SEM FREQUENCIA --\n");
        continue;
      }

      printf("\n--          DADOS         --\n");
      printf("Palavra: %s\nNome Cantor: %s\nNome Musica: %s\nFrequencia: "
             "%d\nFrequencia "
             "no repositorio: %d\n\n Estrofe:\n%s",
             infoFreq->palavra, infoFreq->nome_cantor, infoFreq->nome_musica,
             infoFreq->freq, infoFreq->freq_total, infoFreq->estrofe);
      break;
    default:
      continue;
    }
  }
}
