#include "avl/AVL.h"
#include "binary_tree/BinaryTree.h"
#include "insercao/insercao.h"
#include "tratamento_musica/tratamento_musica.h"
#include "vetor_ordenado/vetor_ordenado.h"
#include <locale.h>
#include <stdio.h>
// A função `main` agora inclui a declaração da música de teste,
// a inicialização das estruturas, a chamada da função de inserção,
// a impressão dos resultados e a liberação da memória.
void liberar_musica(char **musica) {
  if (musica == NULL) {
    return;
  }
  for (int i = 0; musica[i] != NULL; i++) {
    free(musica[i]); // Libera cada linha
  }
  free(musica); // Libera o array de ponteiros
}
int main() {
  setlocale(LC_ALL, "");
  //   char *musica_teste[] = {
  //       "Bohemian Rhapsody",
  //       "Queen",
  //       "is this the real life",
  //       "is this just fantasy",
  //       "caught in a landslide",
  //       "no escape from reality",
  //       NULL // O terminador NULL é crucial para os loops no seu código
  //   };

  char **musica_teste = obter_musica("16.txt", NULL);

  // 2. Inicialização das raízes das árvores
  nodeAVL *raizAVL = criarArvoreAVL();  // Retorna NULL
  node *raizBT = criarArvore();         // Retorna NULL
  VetorOrdenado *vec = vetor_criar(20); // Não será usado no teste

  // Variáveis para armazenar os tempos de execução
  float tAVL = 0.0f, tBT = 0.0f, tVec = 0.0f;

  printf("Iniciando inserção de dados nas árvores...\n\n");

  inserir_estruturas(&raizAVL, &raizBT, &vec, &tAVL, &tBT, &tVec, musica_teste);

  printf("--- Conteúdo da Árvore Binária de Busca (em ordem) ---\n");
  percorrerArvore(raizBT);
  printf("\n-----------------------------------------------------\n\n");

  printf("--- Conteúdo da Árvore AVL (em ordem) ---\n");
  percorrerArvoreAVL(raizAVL);
  printf("\n-----------------------------------------\n\n");

  printf("--- Conteúdo do Vetor --\n");
  vetor_imprimir(vec);
  printf("\n-----------------------------------------\n\n");

  printf("-> Tempos de inserção registrados:\n");
  printf("   - Árvore Binária: %f segundos\n", tBT);
  printf("   - Árvore AVL:     %f segundos\n", tAVL);
  printf("   - Vetor Ordenado: %f segundos\n", tVec);

  // 4. Liberação da memória alocada para as árvores
  liberarArvore(raizBT);
  liberarArvoreAVL(raizAVL);
  vetor_liberar(vec);
  printf("\nMemória das árvores liberada com sucesso.\n");

  liberar_musica(musica_teste);
  printf("Memória da música liberada com sucesso.\n");
  return 0;
}
