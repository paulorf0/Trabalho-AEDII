#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../avl/AVL.h"
#include "../binary_tree/BinaryTree.h"
#include "../vetor_ordenado/vetor_ordenado.h"

// Retorna o tempo para inserção na avl
float inserir_avl(nodeAVL *node, inf *info);
// Retorna o tempo para inserção na árvore binária.
float inserir_bT(node *no, inf *info);
// Retorna o tempo para inserção no vetor ordenado.
float inserir_vetor(VetorOrdenado *vec, inf *info);
