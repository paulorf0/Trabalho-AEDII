#ifndef INSERCAO_H
#define INSERCAO_H

#include "../avl/AVL.h"
#include "../binary_tree/BinaryTree.h"
#include "../vetor_ordenado/vetor_ordenado.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void inserir_estruturas(nodeAVL **nodeavl, node **nodeBT, VetorOrdenado **vec,
                        float *tAVL, float *tBT, float *tVec, char **musica);

#endif
