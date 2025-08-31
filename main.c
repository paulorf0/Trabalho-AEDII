#include "avl/AVL.h"
#include "binary_tree/BinaryTree.h"
#include "menu/menu.h"
#include "vetor_ordenado/vetor_ordenado.h"
#include <locale.h>
int main() {
  setlocale(LC_ALL, "");

  nodeAVL *raizAVL = criarArvoreAVL();  // Retorna NULL
  node *raizBT = criarArvore();         // Retorna NULL
  VetorOrdenado *vec = vetor_criar(20); // Não será usado no teste
  nodeAVLFreq *raizAVLF = criarArvoreAVLFreq();
  nodeFreq *raizBTF = criarArvoreFreq();

  menu(&raizAVL, &raizBT, &vec, &raizAVLF, &raizBTF);
  liberarArvoreAVL(raizAVL);
  liberarArvore(raizBT);
  vetor_liberar(vec);
  liberarArvoreAVLFreq(raizAVLF);
  liberarArvoreFreq(raizBTF);
  return 0;
}
